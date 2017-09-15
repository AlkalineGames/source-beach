//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_stlport_issues.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

#include <sstream>
#include <string>

//----------------------------------------------------------

static
void
test_stlport_issues()
{
    std::string strtest( "test" );

// ### WITH (), oss WILL NOT BE VALID, NOR GENERATE AN EXTERNAL REFERENCE
//    std::ostringstream oss();
    std::ostringstream oss;
    oss << strtest;
    oss << "another test";
    strtest = oss.str();

// ### WITH (), iss WILL NOT BE VALID, NOR GENERATE AN EXTERNAL REFERENCE
//    std::istringstream iss();
    std::istringstream iss;
    iss >> strtest;
}

//----------------------------------------------------------
// (end of file)
