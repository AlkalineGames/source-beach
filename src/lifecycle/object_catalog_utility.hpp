#if !defined(BEACH_LIFECYCLE_OBJECT_CATALOG_UTILITY)
#define      BEACH_LIFECYCLE_OBJECT_CATALOG_UTILITY
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_catalog_utility.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <invocation/command_kill.hpp>
#include <lifecycle/object_catalog.hpp>

namespace lifecycle
{

//--------------------------------------

/// utility for using the object catalog with specific types
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Singleton [GoF]
 */
template <class abstract_type, class concrete_type>
class object_catalog_utility
{
public:

    /// determines if named object already exists
    static boolean has_object(
        const atoms::text * in_name,
        abstract_type **    in_cached_pointer = 0 )
    {
        if (   (in_cached_pointer  != 0)
            && (*in_cached_pointer != 0) )
        {
            return true; 
        }
        stringex name( in_name );
        boolean has = (object_catalog::get_singleton().resolve( name ) != 0);
        return has;
    }
    /// finds named object
    static abstract_type * find_object(
        const atoms::text * in_name,
        abstract_type **    inout_cached_pointer = 0 )
    {
        if (   (inout_cached_pointer  != 0)
            && (*inout_cached_pointer != 0) )
        {
            return *inout_cached_pointer;
        }
        stringex name( in_name );
        return reinterpret_cast<abstract_type*>(
            object_catalog::get_singleton().resolve( name,
                reinterpret_cast<object_catalog::object*>(
                    inout_cached_pointer) ) );
    }
    /// finds or creates the specified named object
    static abstract_type & acquire_object(
        const atoms::text * in_name,
        abstract_type **    inout_cached_pointer  = 0,
        boolean             in_do_create_killer = true )
    {
        abstract_type * object = find_object(
            in_name, inout_cached_pointer );
        if ( object == 0 )
        {
            object = new BEACH_ALLOCATION concrete_type;
            command * killer = in_do_create_killer
                ? new invocation::command_kill<abstract_type>( *object )
                : 0;
            stringex name( in_name );
            object_catalog::get_singleton().bind(
                name, object, killer, 
                reinterpret_cast<object_catalog::object*>(
                    inout_cached_pointer) );
        }
        return *object;
    }
    /// installs a new object, replacing any existing one
    static void install_object(
        const atoms::text * in_name,
        abstract_type &     in_object,
        abstract_type **    out_cached_pointer  = 0,
        boolean             in_do_create_killer = true )
    {
        stringex name( in_name );
        object_catalog::get_singleton().rebind(
            name, &in_object, in_do_create_killer
               ? new invocation::command_kill<abstract_type>( in_object )
               : 0,
            reinterpret_cast<object_catalog::object*>(out_cached_pointer) );
    }

}; // end of class template object_catalog_utility

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_OBJECT_CATALOG_UTILITY
