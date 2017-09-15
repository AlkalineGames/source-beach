//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_taxonomy_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_taxonomy_manager.hpp"

#include <cppunit/TextTestResult.h>
#include <cppunit/TestSuite.h>

#include <iostream>

//--------------------------------------

int
main(
    int     argc,
    char ** argv )
{
    CppUnit::TestSuite suite;
    taxonomy::test_taxonomy_manager test0001;
    test0001.register_tests( &suite );
    CppUnit::TextTestResult res;
    suite.run( &res );
    std::cout << res << std::endl;
    return 0;
}

//----------------------------------------------------------
// (end of file)
