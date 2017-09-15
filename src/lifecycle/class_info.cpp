//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_info.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/class_info.hpp> // this header

#include <atoms/destroyer.hpp>
#include <atoms/stream_string.hpp>
#include <chain/extension_typed.tpp>
#include <lifecycle/logger.hpp>

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions    
//--------------------------------------

static const text name_this_class[]
    = "class_info";

//--------------------------------------
//  public methods    
//--------------------------------------

class_info_extension::class_info_extension(
    class_identifier    in_class_id,
    class_info &        in_owner )
  :
    chain::extension_typed<class_info>( 
        in_class_id, in_owner )
{}

//--------------------------------------

class_info::class_info(
    class_identifier    in_class_id,
    const text *        in_class_name,
    object_identifier   in_last_object_id,
    class_identifier *  in_static_class_id )
  :
    _class_id(          in_class_id ),
    _class_name(        in_class_name ),
    _last_object_id(    in_last_object_id ),
    _static_class_id(   in_static_class_id ),
    _extension(         0 )
{
    if ( _static_class_id != 0 )
    {
        *_static_class_id = _class_id;
    }
}

//--------------------------------------

class_info::~class_info()
{
    delete _extension;
}

//--------------------------------------

object_identifier
class_info::acquire_next_object_id()
{
    static const text name_this_method[]
        = "acquire_next_object_id()";

    object_identifier nextoid
        = ++_last_object_id;
    if ( _extension != 0 )
    {
        _extension->update_owner_changed();
    }
    logger & log = logger::get_singleton();
    if ( log.is_including( name_this_class ) ) // $$$ WILL THIS SCALE?
    {
        stream_string_o sso;
        sso << "class '" << get_class_name() << "', oid==" << nextoid;
        log.log_trace( name_this_class, name_this_method, sso.str().c_str() );
    }            
    return nextoid;
}

//--------------------------------------

void
class_info::set_class_id(
    class_identifier in_cid )
{
    static const text name_this_method[]
        = "set_class_id(...)";

    if ( _class_id != in_cid )
    {
        logger & log = logger::get_singleton();
        if ( log.is_including( name_this_class ) )
        {
            stream_string_o sso;
            sso << "changed id from " << _class_id << " to " << in_cid;
            log.log_trace( name_this_class, name_this_method, sso.str().c_str() );
        }            
        _class_id = in_cid;
        if ( _static_class_id != 0 )
        {
            *_static_class_id = _class_id;
        }
        if ( _extension != 0 )
        {
            _extension->update_owner_changed();
        }   
    }
}

//--------------------------------------

void
class_info::set_class_name(
    const text * in_name )
{
    boolean is_different;
    if ( in_name == 0 )
    {
        is_different = (! _class_name.is_empty());
    }
    else // in_name != 0
    {
        is_different = (_class_name != in_name);
    }
    if ( is_different )
    {
        _class_name = in_name;
        if ( _extension != 0 )
        {
            _extension->update_owner_changed();
        }   
    }
}

//--------------------------------------

void
class_info::set_last_object_id(
    object_identifier in_oid )
{
    if ( _last_object_id != in_oid )
    {
        _last_object_id = in_oid;
        if ( _extension != 0 )
        {
            _extension->update_owner_changed();
        }   
    }
}

//--------------------------------------

void
class_info::set_static_class_id(
    class_identifier * in_static_class_id )
{
    if ( _static_class_id != in_static_class_id )
    {
        _static_class_id = in_static_class_id;
        if ( _static_class_id != 0 )
        {
            *_static_class_id = _class_id;
        }
    }
}

//--------------------------------------

void
class_info::set_extension(
    class_info_extension * in_extension )
{
    if ( _extension != 0 )
    {
        delete _extension;
    }
    _extension = in_extension;
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  template instantiations
//--------------------------------------

template class atoms::destroyer_typed<lifecycle::class_info>;
template class atoms::destroyer<lifecycle::class_info>;
template class chain::extension_typed<lifecycle::class_info>;

//----------------------------------------------------------
// (end of file)
