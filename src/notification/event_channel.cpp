//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_channel.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson, Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/event_channel.hpp> // this header

namespace notification
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

event_channel_extension::event_channel_extension(
    class_identity  in_class_id,
    event_channel & in_owner )
  :
    chain::extension_typed<event_channel>( in_class_id, in_owner )
{}

//--------------------------------------

event_channel::event_channel(
    const text *    in_name )
  :
    _name(          in_name ),
    _class_id(      0 ),
    _channel_type(  sync ),
    _extension(     0 )
{}

//--------------------------------------

event_channel::~event_channel()
{
    delete _extension;
}

//--------------------------------------

void
event_channel::attach_handler(
    event_handler & in_handler )
{
    if ( _handlers.contains( in_handler ) )
    {
        return;
    }
    _handlers.add( in_handler );
}

//--------------------------------------

void
event_channel::detach_handler(
    event_handler & in_handler )
{
    _handlers.erase_first( in_handler );
}

//--------------------------------------

void
event_channel::set_extension(
    event_channel_extension * in_extension )
{
    if ( _extension != 0 )
    {
        delete _extension;
    }
    _extension = in_extension;
}

//--------------------------------------

void
event_channel::set_class_id(
    extension::class_identity in_cid )
{
    if ( _class_id != in_cid )
    {
        _class_id = in_cid;

        if ( _extension != 0 )
        {
            _extension->update_owner_changed();
        }
    }
}

//--------------------------------------

void
event_channel::set_channel_type(
    const text * in_name )
{
    if ( in_name == 0 )
    {
        _channel_type=sync;
    }
    else // in_name != 0
    {
        if ( stringex( in_name ) != "async" )
        {
            _channel_type=async;
        }
    }
    if ( _extension != 0 )
    {
        _extension->update_owner_changed();
    }
}

//--------------------------------------

boolean
event_channel::post_event(
    const event &       in_event,
    virtual_object *    in_subject )
{
    boolean retval = false;
    for ( handlers::iterator
          i( _handlers.begin() ); i != _handlers.end(); i++ )
    {
        event_handler & handler = *i;

        // @@@ TODO - ASYNC
        // IF ASYNC, PUT EVENT ON QUEUE
        // ### assuming SYNC now
        if ( handler.handle_event( in_event,in_subject ) )
        {
            retval=true;
        }
    }
    return retval;
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
