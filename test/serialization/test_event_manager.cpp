//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include "test_event_manager.hpp"

#include "test_event_handler.hpp"

#include <notification/event.hpp>
#include <notification/event_channel.hpp>
#include <serialization/event_manager.hpp>

#include <cppunit/TestCaller.h>

namespace serialization
{

//--------------------------------------
//  public methods
//--------------------------------------

test_event_manager::test_event_manager()
  :
    CppUnit::TestCase( "test_event_manager" )
{}

//--------------------------------------

void
test_event_manager::register_tests(
    CppUnit::TestSuite * suite )
{
    // ### THESE TESTS ARE ORDERED!!!! ###
    suite->addTest( new CppUnit::TestCaller<test_event_manager>(
        "test_register_event_channels", &test_event_manager::test_register_event_channels, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_event_manager>(
        "test_register_events", &test_event_manager::test_register_events, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_event_manager>(
        "test_post_event", &test_event_manager::test_post_event, *this ) );
}

//--------------------------------------

void
test_event_manager::test_register_event_channels()
{
    // register event channel
    event_manager::acquire_singleton().register_event_channel("sync_channel");

    event_channel * channel_sync_not_found =event_manager::acquire_singleton().find_event_channel_by_name("channel_not_found");

    CPPUNIT_ASSERT(channel_sync_not_found==0);

    // register event channel handlers
    event_channel * channel_sync =event_manager::acquire_singleton().find_event_channel_by_name("sync_channel");
    CPPUNIT_ASSERT(channel_sync!=0);
    channel_sync->attach_handler( test_event_handler::acquire_singleton() );
}

//--------------------------------------

void
test_event_manager::test_register_events()
{
    event_manager::acquire_singleton().register_event("sample_world_event1");
    event_manager::acquire_singleton().register_event("sample_world_event2");

    event * event_not_found =event_manager::acquire_singleton().find_event_by_name("not_found_event");
    CPPUNIT_ASSERT(event_not_found==0);

    event * event_found =event_manager::acquire_singleton().find_event_by_name("sample_world_event1");
    CPPUNIT_ASSERT(event_found!=0);

    event_channel * channel_sync =event_manager::acquire_singleton().find_event_channel_by_name("sync_channel");
    event_found->set_event_channel(*channel_sync);
}

//--------------------------------------

void
test_event_manager::test_post_event()
{
    // ### SHOULD RETURN TRUE THAT EVENT WAS HANDLED
    boolean retval1=event_manager::acquire_singleton().post_event("sample_world_event1");
    CPPUNIT_ASSERT(retval1);

    // ### SHOULD RETURN FALSE, EVENT NOT REGISTERED WITH ANY CHANNELS
    boolean retval2=event_manager::acquire_singleton().post_event("sample_world_event2");
    CPPUNIT_ASSERT(retval2==0);
}

//--------------------------------------

// virtual
int
test_event_manager::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_event_manager::setUp()
{
    event_manager::acquire_singleton().register_event_handler(test_event_handler   ::acquire_singleton());
}

//--------------------------------------

// virtual
void
test_event_manager::tearDown()
{}

//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<serialization::test_event_manager>;

//----------------------------------------------------------
// (end of file)
