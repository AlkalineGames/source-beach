//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <notification/event.hpp> // this header

#include <chain/extension_typed.tpp>
#include <lifecycle/logger.hpp>
#include <notification/event_channel.hpp>

namespace notification
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "event";

//--------------------------------------
//  public methods
//--------------------------------------

event_extension::event_extension(
    class_identity  in_class_id,
    event &         in_owner )
  :
    chain::extension_typed<event>( in_class_id, in_owner )
{}

//--------------------------------------

event::event(
    const text *        in_event_name,
    void *              in_affected_object )
  :
    _class_id(          0 ),
    _event_name(        in_event_name),
    _event_channel(     0 ),
    _affected_object(   in_affected_object),
    _extension(         0 )
{}

//--------------------------------------

event::~event()
{
    delete _extension;
}

//--------------------------------------

void
event::set_event_channel(
    event_channel & in_event_channel)
{
    _event_channel = &in_event_channel;
}

//--------------------------------------

void
event::set_extension(
    event_extension * in_extension )
{
    if ( _extension != 0 )
    {
        delete _extension;
    }
    _extension = in_extension;
}

//--------------------------------------

void
event::set_class_id(
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
event::set_class_name(
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

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
