//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_serialization_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include "test_config_file.hpp"
#include "test_event_manager.hpp"

#include <lifecycle/lifecycle_manager.hpp>

#include <cppunit/TestSuite.h>
#include <cppunit/TextTestResult.h>

#include <deque>
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
        serialization::test_config_file   test0001;
        serialization::test_event_manager test0002;
        test0001.register_tests( &suite );
        test0002.register_tests( &suite );
        CppUnit::TextTestResult res;
        suite.run( &res );
        std::cout << res << std::endl;
    }
    lifecycle::lifecycle_manager::destroy_singleton();
    return 0;
}

//----------------------------------------------------------
// (end of file)
