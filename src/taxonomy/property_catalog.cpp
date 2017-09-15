//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_catalog.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_catalog.hpp> // this header

#include <atoms/stringex.hpp>
#include <serialization/config_file.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace taxonomy
{
    using serialization::config_file;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "property_catalog";

static const text global_catalog_name[]
    = "property_catalog_global";
        
static property_catalog * cached_singleton = 0;
    
//--------------------------------------
//  public methods
//--------------------------------------

// static
property_catalog & 
property_catalog::get_global_instance()
{
    return lifecycle::object_catalog_utility<property_catalog,property_catalog>
            ::acquire_object( global_catalog_name, &cached_singleton );
}

//--------------------------------------

// static
boolean
property_catalog::has_global_instance()
{
    return lifecycle::object_catalog_utility<property_catalog,property_catalog>
            ::has_object( global_catalog_name, &cached_singleton );
}

//--------------------------------------

property_catalog::property_catalog()
{}

//--------------------------------------

// virtual 
property_catalog::~property_catalog()
{
    notify_observers( observe_destructing );
}

//--------------------------------------

void
property_catalog::add_group(
    const text *     in_name,
    property_group & in_group )
{
    static const text this_method_name[] =
        "add_group(...)";
        
    if ( _groups.find_ref( in_name ) == 0 )
    {
        _groups.insert( stringex( in_name ), in_group );
        notify_observers( observe_group_added, &in_group );
    }
    else
    {
        stringex message( "group already found with name: " );
        message += in_name;
        logger::get_singleton().log_error(
            this_class_name, this_method_name,
            message );
    }
}        

//--------------------------------------

void
property_catalog::remove_group(
    const text * in_name )
{
    static const text this_method_name[] =
        "remove_group( in_name )";
        
    property_group * group = _groups.find_ref( in_name );
    if ( group != 0 )
    {
        notify_observers( observe_group_removing, &group );
        _groups.erase( in_name ); // $$$ repeats find above
    }
    else
    {
        stringex message( "group not found with name: " );
        message += in_name;
        logger::get_singleton().log_error(
            this_class_name, this_method_name,
            message );
    }
}        

//--------------------------------------

void
property_catalog::remove_group(
    property_group & in_group )
{
    static const text this_method_name[] =
        "remove_group( in_group )";
    
    if ( _groups.contains( in_group ) )
    {
        notify_observers( observe_group_removing, &in_group );
        _groups.erase_first( in_group ); // $$$ repeats find above
    }
    else
    {
        logger::get_singleton().log_error(
            this_class_name, this_method_name,
            "group not found" );
    }
}        

//--------------------------------------

void
property_catalog::read_group_from_external_file(
    const text * in_group_name )
{
    static const text this_method_name[] =
        "read_group_from_external_file(...)";
        
    if ( _external_file_spec.is_empty() )
    {
        return;
    }
    property_group * group = find_group( in_group_name );
    if ( group == 0 )
    {
        return; // !!! not logging an error
    }
    whole propcount         = group->get_property_count();
    const text ** propnames = group->get_property_names();
    if ( (propcount == 0) || (propnames ==0) )
    {
        return;
    }
    // $$$ THIS IS NOT OPTIMAL SINCE THE ENTIRE CONFIG FILE
    // $$$ IS READ EACH TIME THIS METHOD IS CALLED
    config_file cf( _external_file_spec ); 
    cf.load_file();
    for ( whole i = 0; i < propcount; i++ )
    {
        const text * propname = propnames[i];
        if ( (propname != 0) && (propname[0] != '\0') )
        {
            property_surrogate ref(
                group->find_property( propname ) );
            if ( ref.is_valid() )
            {
                stringex valuetext;
                boolean found = cf.find_text(
                    in_group_name, propname, valuetext );
                if ( found )
                {
                    ref.set_value( valuetext, 0 );
                    logger & log = logger::get_singleton();
                    if ( log.is_including( this_class_name ) )
                    {
                        stringex msg( "found property '" );
                        msg += propname;
                        msg += "', value=='";
                        msg += valuetext;
                        msg += "'";
                        log.log_trace( this_class_name,
                            this_method_name, msg );
                    }
                }
            }
        }
    }
    notify_observers( observe_group_read, group );
}

//--------------------------------------

void 
property_catalog::write_group_to_external_file(
    const text * in_group_name )
{
    if ( _external_file_spec.is_empty() )
    {
        return;
    }
    property_group * group = find_group( in_group_name );
    if ( group == 0 )
    {
        return; // !!! not logging an error
    }
    whole propcount         = group->get_property_count();
    const text ** propnames = group->get_property_names();
    if ( (propcount == 0) || (propnames ==0) )
    {
        return;
    }
    config_file cf( _external_file_spec ); 
    for ( whole i = 0; i < propcount; i++ )
    {
        const text * propname = propnames[i];
        if ( (propname != 0) && (propname[0] != '\0') )
        {
            property_surrogate ref(
                group->find_property( propname ) );
            if ( ref.is_valid() )
            {
                cf.set_text( in_group_name,
                    propname, ref.get_value() );
            }
        }
    }
    // $$$ THIS IS NOT OPTIMAL SINCE THE ENTIRE CONFIG FILE
    // $$$ IS WRITTEN EACH TIME THIS METHOD IS CALLED
    cf.write_file(); 
    notify_observers( observe_group_written, group );
}

//--------------------------------------

void 
property_catalog::write_all_groups_to_external_file()
{
    if ( _external_file_spec.is_empty() )
    {
        return;
    }
    config_file cf( _external_file_spec ); 
    for ( property_groups::const_iterator
          groupiter(   _groups.begin() );
          groupiter != _groups.end();
          groupiter++ )
    {
        const property_group * group = groupiter.get_ptr();
        if ( group == 0 )
        {
            continue;
        }
        whole propcount         = group->get_property_count();
        const text ** propnames = group->get_property_names();
        if ( (propcount == 0) || (propnames ==0) )
        {
            return;
        }
        for ( whole propindex = 0; propindex < propcount; propindex++ )
        {
            const text * propname = propnames[propindex];
            if ( (propname != 0) && (propname[0] != '\0') )
            {
                property_surrogate ref(
                    group->find_property_const( propname ) );
                if ( ref.is_valid() )
                {
                    cf.set_text( groupiter.get_key(),
                        propname, ref.get_value() );
                }
            }
        }
    }
    cf.write_file(); 
    notify_observers( observe_group_written, 0 );
}

//--------------------------------------

const property_surrogate
property_catalog::find_property_const(
    const text * in_name ) const
{
    for ( property_groups::const_iterator
          i( _groups.begin() ); i != _groups.end(); i++ )
    {
        const property_group * group = i.get_ptr();
        const property_surrogate ref(
            group->find_property_const( in_name ) );
        if ( ref.is_valid() )
        {
            return ref;
        }
    }
    return property_surrogate();
}

//--------------------------------------

}; // end of namespace taxonomy

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<taxonomy::property_catalog>;

//----------------------------------------------------------
// (end of file)
