//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include "test_event.hpp" // this header

#include <notification/event.hpp>

namespace serialization
{
    using namespace atoms;
    using notification::event;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "test_event";

//--------------------------------------
//  public methods
//--------------------------------------

test_event::test_event(
    const text * in_name )
  :
    _name( in_name ),
    _world_event( 0 )
{}

//--------------------------------------

// virtual
test_event::~test_event()
{}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
