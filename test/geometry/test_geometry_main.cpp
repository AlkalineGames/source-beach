//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_geometry_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_cuboid_aligned.hpp"

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
    geometry::test_cuboid_aligned test1;
    test1.register_tests( &suite );
    CppUnit::TextTestResult res;
    suite.run( &res );
    std::cout << res << std::endl;
    return 0;
}

//----------------------------------------------------------
// (end of file)
