//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_observable.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_observable.hpp"

#include <notification/observable_imp.hpp>

#include <cppunit/TestCaller.h>

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

test_observable::test_observable()
  :
    CppUnit::TestCase( "test_observable" )
{}

//--------------------------------------

void
test_observable::registerTests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_observable>(
        "test_attach_observer", &test_observable::test_attach_observer, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_observable>(
        "test_insert_observer", &test_observable::test_insert_observer, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_observable>(
        "test_detach_observer", &test_observable::test_detach_observer, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_observable>(
        "test_notify_observers_with_flags", &test_observable::test_notify_observers_with_flags, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_observable>(
        "test_notify_observers_without_flags", &test_observable::test_notify_observers_without_flags, *this ) );
}

//--------------------------------------

void
test_observable::test_attach_observer()
{ 
    // ### COMPLETE THIS

    CPPUNIT_ASSERT( true );
}

//--------------------------------------

void
test_observable::test_insert_observer()
{ 
    // ### COMPLETE THIS

    CPPUNIT_ASSERT( true );
}

//--------------------------------------

void
test_observable::test_detach_observer() 
{ 
    // ### COMPLETE THIS

    CPPUNIT_ASSERT( true );
}

//--------------------------------------

void
test_observable::test_notify_observers_with_flags() 
{ 
    // ### COMPLETE THIS

    CPPUNIT_ASSERT( true );
}

//--------------------------------------

void
test_observable::test_notify_observers_without_flags() 
{ 
    // ### COMPLETE THIS

    CPPUNIT_ASSERT( true );
}

//--------------------------------------

// virtual
int
test_observable::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_observable::setUp()
{ 
    _observable = new observable_imp; 
}

//--------------------------------------

// virtual
void
test_observable::tearDown()
{ 
    delete _observable; 
}
   
//--------------------------------------

}; // end of namespace notification

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<notification::test_observable>;

//----------------------------------------------------------
// (end of file)
