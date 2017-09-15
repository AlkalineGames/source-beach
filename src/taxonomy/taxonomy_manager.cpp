//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       taxonomy_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <taxonomy/taxonomy_manager.hpp> // this header

#include <atoms/allocation.hpp>
#include <atoms/stream_string.hpp>
#include <atoms/stringex.hpp>
#include <collection/ref_set_of_string.hpp>
#include <serialization/reader.hpp>
#include <serialization/serializable_factory.hpp>
#include <serialization/serializable_manager.hpp>
#include <serialization/serializable_spec.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/lifecycle_manager.hpp>
#include <lifecycle/logger.hpp>
#include <taxonomy/property_imp.hpp>
#include <taxonomy/property_range.hpp>
#include <taxonomy/property_set.hpp>

namespace taxonomy
{
    using namespace atoms;
    using serialization::reader;
    using serialization::serializable;
    using serialization::serializable_factory;
    using serialization::serializable_manager;
    using serialization::serializable_spec;
    using lifecycle::lifecycle_manager;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

/// internal implementation subclass

class taxonomy_manager_imp
    : public taxonomy_manager,
      public serializable_factory
{
friend class invocation::command_kill<taxonomy_manager>;
friend class lifecycle::object_catalog_utility<taxonomy_manager,taxonomy_manager>;
public:

    BEACH_ALLOCATION_OPERATORS

    taxonomy_manager_imp();
    virtual ~taxonomy_manager_imp();

    void initialize();

    /// @name taxonomy_manager overrides required
    //@{
    virtual const stringex &        get_label_null()        const;
    virtual const property &        get_property_null()     const;
    virtual const property_set &    get_property_set_null() const;
    virtual const stringex &        acquire_label(          const text * in_name );
    virtual const property_set &    acquire_property_set(   const text * in_name );
    virtual const property_set *    find_property_set(      const text * in_name );
    virtual property_range &        create_property_range(
        const text *                    in_name,
        const real                      in_from = 0,
        const real                      in_to   = 0 );
    //@}

    /// @name serializable_factory overrides 
    //@{
    virtual serializable *          acquire(
        context &                       in_context,
        serializable_spec &             inout_spec,
        reader *                        in_state_reader );
                                 
    virtual serializable *          acquire(
        context &                       in_context,
        reader &                        in_spec_reader,
        reader *                        in_state_reader );
    //@}

private:

    typedef collection::ref_set_of_string                  labels;
    typedef collection::ref_map_by_string<property_set>    property_sets;

    stringex        _label_null;
    property_imp *  _property_null;
    property_set *  _property_set_null;
    labels          _labels;
    property_sets   _property_sets;

}; // end of class taxonomy_manager

//--------------------------------------

static const text this_class_name[]
    = "taxonomy_manager";

static taxonomy_manager_imp * singleton_cached = 0;

//--------------------------------------
//  internal public members
//--------------------------------------

taxonomy_manager_imp::taxonomy_manager_imp()
  :
    _label_null(        0 ),
    _property_null(     0 ),
    _property_set_null( 0 ),
    _labels(            atoms::destroyer<stringex>() ),
    _property_sets(     atoms::destroyer<property_set>() )
{}

//--------------------------------------

// virtual
taxonomy_manager_imp::~taxonomy_manager_imp()
{
    serializable_manager * serman = serializable_manager::find_singleton();
    if ( serman != 0 )
    {
        serman->remove_factory( *this );
    }
    delete _property_set_null;
    delete _property_null;
}

//--------------------------------------

void
taxonomy_manager_imp::initialize()
{
    // !!! creating property_imp in constructor recurses infinitely
    _property_null      = new property_imp();
    _property_set_null  = new property_set( 0 );
    serializable_manager::acquire_singleton().add_factory( *this );
}

//--------------------------------------

// virtual
const stringex &
taxonomy_manager_imp::get_label_null() const
{
    return _label_null;
}

//--------------------------------------

// virtual
const property &
taxonomy_manager_imp::get_property_null() const
{
    return *_property_null;
}

//--------------------------------------

// virtual
const property_set &
taxonomy_manager_imp::get_property_set_null() const
{
    return *_property_set_null;
}

//--------------------------------------

// virtual
const stringex &
taxonomy_manager_imp::acquire_label(
    const text * in_name )
{
    labels::const_iterator iter
        = _labels.find_match( in_name );
    if ( iter != _labels.end() )
    {
        return *iter;
    }
    stringex * lab = new stringex( in_name );
    _labels.insert( *lab );
    return *lab;
}

//--------------------------------------

// virtual
const property_set &
taxonomy_manager_imp::acquire_property_set(
    const text * in_name )
{
    property_set * propset = find_property_set_nc( in_name );
    if ( propset == 0 )
    {
        propset = new property_set( in_name );
        _property_sets.insert( in_name, *propset );
    }
    return *propset;
}

//--------------------------------------

// virtual
const property_set *
taxonomy_manager_imp::find_property_set(
    const text * in_name )
{
    stringex name( in_name );
    if ( ! name.empty() )
    {
        property_sets::const_iterator iter(
            _property_sets.find( name ) );
        if ( iter != _property_sets.end() )
        {
            return &(*iter);
        }
    }
    return 0;
}

//--------------------------------------

// virtual
property_range &
taxonomy_manager_imp::create_property_range(
    const text *    in_name,
    const real      in_from,
    const real      in_to )
{
    return *(new property_range(
        acquire_label( in_name ), in_from, in_to ));
}

//--------------------------------------

// virtual
serializable *
taxonomy_manager_imp::acquire(
    context &           in_context,
    serializable_spec & inout_spec,
    reader *            in_state_reader )
{
    serializable * ser = 0;
    if ( inout_spec._class_id == property_set::get_class_id() )
    {
        if ( ! inout_spec._object_name.empty() )
        {
            property_set & propset = acquire_property_set_nc(
                inout_spec._object_name );
            if ( in_state_reader != 0 )
            {
                propset.read_from( in_context, *in_state_reader );
            }
            ser = &propset;
        }
    }
    return ser;
}

//--------------------------------------

// virtual
serializable *
taxonomy_manager_imp::acquire(
    context &   in_context,
    reader &    in_spec_reader,
    reader *    in_state_reader )
{
    static const text this_method_name[]
        = "acquire( reader &, reader * );";

    serializable_spec spec;
    boolean succeeded =
        (   in_spec_reader.read_spec( // @@@ S/B serializable, not form
                &(property_set::get_selector( property_set::selector_identity )),
                0, spec ) );

    // there must be both valid class id and object name
    if ( (!succeeded) || (spec._class_id == 0) || spec._object_name.empty() )
    {
        logger & log = logger::get_singleton();
        if ( log.is_including( this_class_name ) )
        {
            stream_string_o sso;
            sso << "failed: serializable spec read is <" 
                << spec.to_string()
                << ">, property_set identity selector is <"
                << property_set::get_selector(
                    property_set::selector_identity ).get_value()
                << '>';
            log.log_trace( this_class_name, this_method_name,
                sso.str().c_str() );
        }
        return 0;
    }
    return acquire( in_context, spec, in_state_reader );
}

//--------------------------------------
//  public methods
//--------------------------------------

// static
taxonomy_manager &
taxonomy_manager::acquire_singleton()
{
    lifecycle_manager::acquire_singleton(); // !!! insurance
    taxonomy_manager * reflectman = find_singleton();
    if ( reflectman != 0 )
    {
        return *reflectman;
    }
    taxonomy_manager_imp & reflectmanimp =
        lifecycle::object_catalog_utility<taxonomy_manager_imp,taxonomy_manager_imp>
            ::acquire_object( this_class_name, &singleton_cached );
    reflectmanimp.initialize();
    return reflectmanimp;
}

//--------------------------------------
//  private methods
//--------------------------------------

// virtual
taxonomy_manager::~taxonomy_manager()
{}

//--------------------------------------

}; // end of namespace taxonomy

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<taxonomy::taxonomy_manager_imp>;

//----------------------------------------------------------
// (end of file)
