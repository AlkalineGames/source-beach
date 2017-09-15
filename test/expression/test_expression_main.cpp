//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_expression_main.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_regexp.hpp"

#include <cppunit/TextTestResult.h>
#include <cppunit/TestSuite.h>

#include <iostream>

//--------------------------------------

int
main(
    int argc, char ** argv )
{
    CppUnit::TestSuite suite;
    expression::test_regexp test01;
    test01.register_tests( &suite );
    CppUnit::TextTestResult res;
    suite.run( &res );
    std::cout << res << std::endl;
    return 0;
}

//----------------------------------------------------------
// (end of file)
