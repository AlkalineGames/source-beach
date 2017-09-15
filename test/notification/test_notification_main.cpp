//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_notification_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_observable.hpp"

#include <lifecycle/lifecycle_manager.hpp>

#include <cppunit/TextTestResult.h>
#include <cppunit/TestSuite.h>

#include <iostream>

//--------------------------------------

int 
main(
    int     argc,
    char ** argv )
{
    lifecycle::lifecycle_manager::acquire_singleton();
    {
        CppUnit::TestSuite suite;
        notification::test_observable test01;
        test01.registerTests( &suite );
        CppUnit::TextTestResult res;
        suite.run( &res );
        std::cout << res << std::endl;
    }
    lifecycle::lifecycle_manager::destroy_singleton();
    return 0;
}

//----------------------------------------------------------
// (end of file)
