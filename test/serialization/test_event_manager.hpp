#if !defined(BEACH_SERIALIZATION_TEST_EVENT_MANAGER)
#define      BEACH_SERIALIZATION_TEST_EVENT_MANAGER
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event_manager.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace serialization
{

//--------------------------------------

/// unit test for event_manager

class test_event_manager
    : public CppUnit::TestCase
{
public:

    test_event_manager();

    void register_tests( CppUnit::TestSuite * );

    void test_register_event_channels();
    void test_register_events();
    void test_post_event();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

}; // end of class test_event_manager

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEST_EVENT_MANAGER
