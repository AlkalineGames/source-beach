//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_handler.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson, Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/event_handler.hpp> // this header

#include <notification/event.hpp>

namespace notification
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "event_handler";

//--------------------------------------
//  public methods
//--------------------------------------

event_handler::event_handler(
    const text * in_name )
  :
    _name( in_name )
{}

//--------------------------------------

// virtual
event_handler::~event_handler()
{}

//--------------------------------------

boolean
event_handler::handle_event(
    const event &       in_event,
    virtual_object *    in_subject )
{
    // !!! do nothing, intended for override
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
