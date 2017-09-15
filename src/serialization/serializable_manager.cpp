//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serializable_manager.hpp> // this header

#include <atoms/destroyer.hpp>
#include <atoms/stream_string.hpp>
#include <collection/ref_list.hpp>
#include <collection/ref_vector.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/logger.hpp>
#include <serialization/serializable.hpp>
#include <serialization/serializable_factory.hpp>
#include <serialization/serializable_spec.hpp>
#include <serialization/text_stream_writer.hpp>

#include <typeinfo>

namespace serialization
{
    using namespace atoms;
    using lifecycle::class_catalog;
    using lifecycle::logger;
    using invocation::command;

//--------------------------------------
//  internal definitions
//--------------------------------------

/// internal implementation subclass

class serializable_manager_imp
    : public serializable_manager
{
friend class invocation::command_kill<serializable_manager>;
friend class lifecycle::object_catalog_utility<serializable_manager,serializable_manager>;
public:

    serializable_manager_imp();
    virtual ~serializable_manager_imp();

    virtual void add_factory(       serializable_factory & );
    virtual void remove_factory(    serializable_factory & );

    /// @name operations delegated to factories
    //@{
    virtual serializable *  acquire(
        context &               in_context,
        serializable_spec &     inout_spec, ///< @note might resolve undefined values
        reader *                in_state_reader );
    
    virtual serializable *  acquire(
        context &               in_context,
        reader &                in_spec_reader,
        reader *                in_state_reader,
        boolean                 in_do_log_error = true );

    virtual void            ignore_class(
        class_identifier        in_class_id,
        const text *            in_class_name ); 

    virtual boolean         import_file(
        const text *            in_file_spec );

    virtual boolean         read_file(
        const text *            in_file_spec,
        boolean                 in_do_change_to_file_directory  = false,
        boolean                 in_is_importing                 = false );
    //@}

private:

    typedef collection::ref_vector<serializable_factory> factories;
    typedef collection::ref_list<serializable_spec> specs;

    boolean ignoring_class( const serializable_spec & );

    factories   _factories;
    specs       _classes_ignored;

}; // end of class serializable_manager

//--------------------------------------

static const text this_class_name[]
    = "serializable_manager";

static const text log_inclusion_name[]
    = "serializable";

static serializable_manager * singleton_cached = 0;
    
//--------------------------------------
//  internal public methods
//--------------------------------------

serializable_manager_imp::serializable_manager_imp()
  :
    _classes_ignored( destroyer<serializable_spec>() )
{}

//--------------------------------------

// virtual
serializable_manager_imp::~serializable_manager_imp()
{}

//--------------------------------------

void
serializable_manager_imp::add_factory(
    serializable_factory & in_factory )
{
    static const text this_method_name[]
        = "add_factory(...)";

    if ( _factories.contains( in_factory ) )
    {
        return;
    }
    _factories.add( in_factory );
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) ) 
    {
        stream_string_o sso;
        sso << "added factory @ " << std::hex << whole64(&in_factory)
            << " of type " << typeid(in_factory).name();
        log.log_trace( this_class_name, this_method_name, sso.str().c_str() );
    }
}

//--------------------------------------

void
serializable_manager_imp::remove_factory(
    serializable_factory & in_factory )
{
    static const text this_method_name[]
        = "remove_factory( ... )";

    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) ) 
    {
        stream_string_o sso;
        sso << "removing factory @ " << std::hex << whole64(&in_factory)
            << " of type " << typeid(in_factory).name();
        log.log_trace( this_class_name, this_method_name, sso.str().c_str() );
    }
    _factories.erase_first( in_factory );
}

//--------------------------------------

serializable *
serializable_manager_imp::acquire(
    context &           in_context,
    serializable_spec & inout_spec,
    reader *            in_state_reader )
{
    static const text this_method_name[]
        = "acquire( serializable_spec &, reader * )";

    serializable * ser = 0;
    if (   (  inout_spec._class_id == 0)
        && (! inout_spec._class_name.is_empty()) )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        inout_spec._class_id = catalog.resolve_class_id_by_name(
            inout_spec._class_name, true ); // can fail, will log error
    }
    if ( inout_spec._class_id != 0 )
    {
        for ( factories::iterator
              factiter(   _factories.begin() );
              factiter != _factories.end();
              factiter++ )
        {
            ser = factiter->acquire( in_context, inout_spec, in_state_reader );
            if ( ser != 0 )
            {
                break;
            }
        }
    }
    logger & log = logger::get_singleton();
    if ( ser != 0 )
    {
        stringex logname = log_inclusion_name;
        logname += '/';
        logname += inout_spec._class_name;
        if (   log.is_including( log_inclusion_name ) 
            || log.is_including( logname            ) )
        {
            stringex logmsg( "Acquired:\n" );
            logmsg += text_stream_writer::write_to_string( *ser, 0 );
            logmsg += '.';
            log.log_trace( this_class_name, this_method_name, logmsg );
        }
    }
    else // ser == 0
    {
        if ( ignoring_class( inout_spec ) )
        {
            return 0;
        }
        stream_string_o sso;
        sso << "Cannot acquire object '"
            << inout_spec.to_string() << "'";
        if ( inout_spec._class_id == 0 )
        {
            if ( inout_spec._class_name.is_empty() )
            {
                sso << " without specifiying its class by id or name";
            }
            else
            {
                sso << " because the specified class is not registered";
            }
        }             
        sso << '.';
        log.log_error( this_class_name, this_method_name,
            sso.str().c_str() );
    }
    return ser;
}
    
//--------------------------------------

serializable *
serializable_manager_imp::acquire(
    context &   in_context,
    reader &    in_spec_reader,
    reader *    in_state_reader,
    boolean     in_do_log_error )
{
    static const text this_method_name[]
        = "acquire( reader &, reader * )";

    serializable * ser = 0;
    for ( factories::iterator
          factiter(   _factories.begin() );
          factiter != _factories.end();
          factiter++ )
    {
        ser = factiter->acquire( in_context, in_spec_reader, in_state_reader );
        if ( ser != 0 )
        {
            break;
        }
    }
    if ( (ser == 0) && (in_do_log_error) )
    {
        logger::get_singleton().log_error(
            this_class_name, this_method_name,
            "None of the serializable factories could acquire" );
    }
    return ser;
}

//--------------------------------------

void
serializable_manager_imp::ignore_class(
    class_identifier    in_class_id,
    const text *        in_class_name )
{
    serializable_spec & newspec
        = *(new serializable_spec( in_class_id, in_class_name ));
    _classes_ignored.add( newspec );
    stringex logmsg( "Ignoring serialization of class <" );
    logmsg += newspec.to_string();
    logmsg += ">.";
    logger::get_singleton().log_information( 0, 0, logmsg );
}

//--------------------------------------

boolean
serializable_manager_imp::import_file(
    const text * in_file_spec )
{
    stringex filespec( in_file_spec );
    filespec.erase_leading_whitespace();
    filespec.erase_trailing_whitespace();
    if ( filespec.is_empty() )
    {
        return false;
    }
    logger & log = logger::get_singleton();
    stringex logmsg( ">>> Started importing file: " );
    logmsg += filespec;
    log.log_information( 0, 0, logmsg );

    boolean succeeded = read_file(
        filespec.get_text(),
        true, true ); // change to file directory, is importing
    if ( ! succeeded )
    {
        logmsg = "Failed to import file: ";
        logmsg += filespec;
        log.log_error( 0, 0, logmsg );
    }
    logmsg = "<<< Finished importing file: ";
    logmsg += filespec;
    log.log_information( 0, 0, logmsg );
    return succeeded;
}

//--------------------------------------

boolean
serializable_manager_imp::read_file(
    const text *    in_file_spec,
    boolean         in_do_change_to_file_directory,
    boolean         in_is_importing )
{
    for ( factories::iterator
          factiter(   _factories.begin() );
          factiter != _factories.end();
          factiter++ )
    {
        if ( factiter->read_file( in_file_spec,
                in_do_change_to_file_directory, in_is_importing ) )
        {
            return true;
        }
    }
    return false;
}

//--------------------------------------
//  private methods
//--------------------------------------

boolean
serializable_manager_imp::ignoring_class(
    const serializable_spec & in_spec )
{
    for ( specs::iterator
          speciter(   _classes_ignored.begin() );
          speciter != _classes_ignored.end();
          speciter++ )
    {
        serializable_spec & spec = *speciter;
        if (   (  spec._class_id == 0)
            && (! spec._class_name.is_empty()) )
        {
            class_catalog & catalog = class_catalog::get_singleton();
            spec._class_id = catalog.resolve_class_id_by_name(
                spec._class_name, true ); // can fail, will log error
        }
        if (   (in_spec._class_id   == spec._class_id)
            || (in_spec._class_name == spec._class_name) )
        {
            return true;
        }  
    }
    return false;
}

//--------------------------------------
//  public methods
//--------------------------------------

// static
serializable_manager &
serializable_manager::acquire_singleton()
{
    return lifecycle::object_catalog_utility<serializable_manager,serializable_manager_imp>
            ::acquire_object( this_class_name, &singleton_cached );
}

//--------------------------------------

// virtual
serializable_manager::~serializable_manager()
{}

//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<serialization::serializable_manager>;
template class atoms::destroyer_typed<serialization::serializable_spec>;
template class atoms::destroyer<serialization::serializable_spec>;

//----------------------------------------------------------
// (end of file)
