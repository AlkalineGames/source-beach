#if !defined(BEACH_TAXONOMY_PROPERTY_CATALOG)
#define      BEACH_TAXONOMY_PROPERTY_CATALOG
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_catalog.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <taxonomy/property_group.hpp>
#include <notification/observable_imp.hpp>

namespace taxonomy
{
    using atoms::stringex;
    using atoms::text;
    using notification::observable_imp;
        
//--------------------------------------

/// catalog of registered properties
/**
 *  @note   design patterns applied:
 *              - Observer  [GoF]
 *              - Singleton [GoF]
 */
class property_catalog
    : public virtual observable_imp
{
public:

    enum observer_flag ///< bitwise values can be combined
    { 
        observe_destructing     = observable_imp::next_observer_flag    << 1,
        observe_group_added     = observe_destructing               << 1,
        observe_group_removing  = observe_group_added               << 1,
        observe_group_read      = observe_group_removing            << 1,
        observe_group_written   = observe_group_read                << 1
    };
    typedef property_groups groups; ///< @deprecated

    BEACH_ALLOCATION_OPERATORS

    static const property_catalog & get_global_instance_const() { return get_global_instance(); }
    static       property_catalog & get_global_instance();
    static boolean                  has_global_instance();

    property_catalog(); ///< doesn't have to be a singleton
    virtual ~property_catalog();

    const property_groups & get_groups_const() const { return _groups; }
          property_groups & get_groups()             { return _groups; }

    void add_group(    const text * in_name, property_group & );
    void remove_group( const text * in_name );
    void remove_group( property_group & );

    void read_group_from_external_file( const text * in_name );
    void write_group_to_external_file(  const text * in_name );
    void write_all_groups_to_external_file();

    const stringex &    get_external_file_spec() const { return _external_file_spec; }
    void                set_external_file_spec( const text * in_file_spec ) ///< null will disable the external file
    {
        _external_file_spec = in_file_spec;
    }
    const property_group * find_group_const( const text * in_name ) const
    {
        return _groups.find_ref_const( in_name );
    }
          property_group * find_group(       const text * in_name )
    {
        return _groups.find_ref( in_name );
    }
    const property_surrogate find_property_const( const text * in_name ) const;
          property_surrogate find_property(       const text * in_name )
    {
        return find_property_const( in_name );
    }

private:

    stringex        _external_file_spec;
    property_groups _groups;

}; // end of class property_catalog

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_CATALOG
