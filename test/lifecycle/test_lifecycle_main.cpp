//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_lifecycle_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_allocation_center.hpp"
#include "test_object_identification.hpp"

#include <atoms/stringex.hpp>
#include <lifecycle/lifecycle_manager.hpp>

#include <cppunit/TextTestResult.h>
#include <cppunit/TestSuite.h>

#include <iostream>

//----------------------------------------------------------

// !!! THIS SHOWS THAT WE CANNOT DECLARE static OBJECTS THAT
// !!! USE atoms_allocator FOR ALLOCATIONS (e.g. stringex)

static atoms::stringex string_static( "string_static" );
    // !!! DESTRUCTION WILL CRASH IF THE lifecycle_manager
    // !!! IS DESTROYED BELOW, AS IT NORMALLY SHOULD BE

//----------------------------------------------------------

int
main(
    int     argc,
    char ** argv )
{
    lifecycle::lifecycle_manager::acquire_singleton();
    {
        CppUnit::TestSuite suite;
        lifecycle::test_allocation_center       test0001;
        lifecycle::test_object_identification   test0002;
        test0001.register_tests( &suite );
        test0002.register_tests( &suite );
        CppUnit::TextTestResult res;
        suite.run( &res );
        std::cout << res << std::endl;
    }
//    lifecycle::lifecycle_manager::destroy_singleton();
    // !!! CANNOT DESTROY AS WE SHOULD BECAUSE
    // !!! DESTRUCTION OF string_static ABOVE WILL CRASH
    // !!! AS ITS DELETE OPERATION CALLS atoms_allocator
    // !!! WHICH CALLS THE DESTROYED allocation_center
    // !!! THROUGH THE DESTROYED lifecycle_manager
    return 0;
}

//----------------------------------------------------------
// (end of file)
