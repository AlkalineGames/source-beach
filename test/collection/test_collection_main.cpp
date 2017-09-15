//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_collection_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include "test_ref_set_of_string.hpp"
#include "test_ref_vector.hpp"
#include "test_std_map.hpp"

#include <cppunit/TestSuite.h>
#include <cppunit/TextTestResult.h>

#include <iostream>

//--------------------------------------

int
main(
    int     argc,
    char ** argv )
{
    CppUnit::TestSuite suite;
    collection::test_ref_set_of_string test0001;
    collection::test_ref_vector        test0002;
    collection::test_std_map           test0003;
    test0001.register_tests( &suite );
    test0002.register_tests( &suite );
    CppUnit::TextTestResult res;
    suite.run( &res );
    std::cout << res << std::endl;
}

//----------------------------------------------------------
// (end of file)
