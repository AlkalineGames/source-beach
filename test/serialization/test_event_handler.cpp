//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event_handler.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include "test_event_handler.hpp" // this header

#include <invocation/command.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <notification/event.hpp>
#include <notification/event_handler.hpp>

namespace serialization
{
    using namespace atoms;
    using invocation::command;
    using invocation::command_kill;
    using lifecycle::logger;
    using lifecycle::object_catalog;
    using notification::event;
    using notification::event_handler;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "test_event_handler";

//--------------------------------------
//  public methods
//--------------------------------------

// static
test_event_handler &
test_event_handler::acquire_singleton()
{
    return lifecycle::object_catalog_utility<test_event_handler,test_event_handler>
            ::acquire_object( this_class_name );
}

//--------------------------------------

test_event_handler::test_event_handler()
  :
    event_handler(this_class_name)
{}

//--------------------------------------

test_event_handler::~test_event_handler()
{}

//--------------------------------------

// virtual
boolean
test_event_handler::handle_event(
    const event & in_event )
{
    static const text this_method_name[]
        = "handle_event(...)";

    // ACT ON EVENT
    logger::get_singleton().log_information(
      this_class_name, this_method_name,
      in_event.get_name());
}

//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<serialization::test_event_handler>;

//----------------------------------------------------------
// (end of file)
