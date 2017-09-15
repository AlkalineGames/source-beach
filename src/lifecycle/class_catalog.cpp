//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_catalog.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/class_catalog.hpp> // this header

#include <atoms/stream_string.hpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "class_catalog";

static const text text_name_null_class_name[]
    = "beach::lifecycle::class_catalog::null_class_name";

static stringex * null_class_name_cached = 0;

//--------------------------------------
//  public methods
//--------------------------------------

const class_info *
class_catalog::find_class_by_id(
    class_identifier in_class_id )
{
    for ( entries::const_iterator 
          i( _entries.begin() ); i != _entries.end(); i++ )
    {
        const class_info & entry = *i;
        if ( entry.get_class_id() == in_class_id )
        {
            return &entry;
        }
    }
    return 0;
}

//--------------------------------------

const class_info *
class_catalog::find_class_by_name(
    const text * in_class_name )
{
    for ( entries::const_iterator 
          i( _entries.begin() ); i != _entries.end(); i++ )
    {
        const class_info & entry = *i;
        if ( entry.get_class_name().compare( in_class_name ) == 0 )
        {
            return &entry;
        }
    }
    return 0;
}

//--------------------------------------

const stringex &
class_catalog::find_class_name(
    class_identifier in_class_id )
{
    const class_info * entry = find_class_by_id( in_class_id );
    if ( entry != 0 )
    {
        return entry->get_class_name();
    }
    return lifecycle::object_catalog_utility<stringex,stringex>
            ::acquire_object( text_name_null_class_name, &null_class_name_cached );
}

//--------------------------------------

const class_info &
class_catalog::register_class(
    class_identifier    in_class_id,    
    const text *        in_class_name,
    object_identifier   in_last_object_id )
{
    const class_info * entry = find_class_by_id( in_class_id );
    if ( entry != 0 )
    {
        class_info & ncentry = const_cast<class_info&>(*entry);
        class_info info( in_class_id, in_class_name, in_last_object_id, 0 );
        ncentry = info;
        return *entry;
    }
    return add_new_entry( in_class_id,
        in_class_name, in_last_object_id, 0 );
}

//--------------------------------------

const class_info *
class_catalog::resolve_class_by_id_or_name(
    class_identifier    in_class_id,
    const text *        in_class_name,
	boolean             in_can_fail,
	class_identifier *  inout_static_class_id )
{
    static const text this_method_name[]
        = "resolve_class_id_or_name";

    const class_info * entry = find_class_by_id( in_class_id );
    if ( (entry == 0) && (in_class_name != 0) )
    {
        entry = find_class_by_name( in_class_name );
    }
    if ( entry != 0 )
    {
        if ( inout_static_class_id != 0 )
        {
            const_cast<class_info*>(entry)
                ->set_static_class_id( inout_static_class_id );
        }
    }
    else // entry == 0
    {
        if ( ! in_can_fail )
        {
            entry = &(add_new_entry(
                in_class_id, in_class_name,
                0, inout_static_class_id ));
        }
	    else // failed, log an error message.
    	{
            stream_string_o ss;
            ss  << "No class is registered with with id=="
                << in_class_id;
            if ( in_class_name == 0 )
            {
    	    	ss << " or name '" << in_class_name << "'.";
            }
            ss << std::flush;
    		logger::get_singleton().log_error(
	    		this_class_name, this_method_name, ss.str().c_str() );
        }
	}
    return entry;
}        

//--------------------------------------

const class_info *
class_catalog::resolve_class_by_name(
    const text *        in_class_name,
	boolean             in_can_fail,
	class_identifier *  inout_static_class_id )
{
    static const text this_method_name[]
        = "resolve_class_id";

    const class_info * entry = find_class_by_name( in_class_name );
    if ( entry != 0 )
    {
        if ( inout_static_class_id != 0 )
        {
            const_cast<class_info*>(entry)
                ->set_static_class_id( inout_static_class_id );
        }
    }
    else // entry == 0
    {
        if ( ! in_can_fail )
        {
            _last_generated_class_id += 
                class_identifier_generation_increment;
            entry = &(add_new_entry(
                _last_generated_class_id,
                in_class_name, 0, inout_static_class_id ));
        }
	    else // failed, log an error message.
    	{
	    	stringex msg( "No class is registered with name '" );
    		msg += in_class_name;
	    	msg += "'.";
		    logger::get_singleton().log_error(
			    this_class_name, this_method_name, msg );
    	}
    }
    return entry;
}        

//--------------------------------------

class_identifier
class_catalog::resolve_class_id_by_name(
    const text *        in_class_name,
	boolean             in_can_fail )
{
    const class_info * entry =
        resolve_class_by_name(
            in_class_name, in_can_fail );
    if ( entry != 0 )
    {
        return entry->get_class_id();
    }
    return 0;
}        

//--------------------------------------

object_identifier
class_catalog::acquire_next_object_id(
    class_identifier in_class_id )
{
    const class_info * entry = find_class_by_id( in_class_id );
    if ( entry != 0 )
    {
        class_info & ncentry = const_cast<class_info&>(*entry);
        return ncentry.acquire_next_object_id();
    }
    return 0;
}

//--------------------------------------
//  private methods
//--------------------------------------

// static
class_catalog &
class_catalog::create()
{
    return *(new class_catalog);
}

//--------------------------------------

// static
void
class_catalog::destroy(
    class_catalog & in_singleton )
{
    delete &in_singleton;
}

//--------------------------------------

class_catalog::class_catalog()
  :
    _last_generated_class_id( class_identifier_generation_offset ),
    _entries( atoms::destroyer<class_info>() )
{} 

//--------------------------------------

class_catalog::~class_catalog()
{}

//--------------------------------------

class_info &
class_catalog::add_new_entry(
    class_identifier    in_class_id,
    const text *        in_class_name,
    object_identifier   in_last_object_id,
	class_identifier *  inout_static_class_id )
{
    static const text this_method_name[]
        = "add_new_entry(...)";

    class_info & entry = *(new class_info(
        in_class_id, in_class_name, in_last_object_id,
        inout_static_class_id ));
    _entries.add( entry );
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        stream_string_o sso;
        sso << "class id=="             << entry.get_class_id()
            << ", class name=="         << entry.get_class_name()
            << ", last object id=="     << entry.get_last_object_id()
            << ", static class id &=="  << std::hex << entry.get_static_class_id();
        log.log_trace( this_class_name, this_method_name,
            sso.str().c_str() );
    }
    return entry;
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
