//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_object_identification.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_object_identification.hpp"

#include <atoms/stringex.hpp>
#include <lifecycle/object_identification_id.hpp>
#include <lifecycle/object_identification_id_name.hpp>
#include <lifecycle/object_identification_name.hpp>

//--------------------------------------

namespace lifecycle
{

//--------------------------------------
//  public methods
//--------------------------------------

test_object_identification::test_object_identification()
  :
    CppUnit::TestCase( "test_object_identification" )
{}

//--------------------------------------

void
test_object_identification::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_object_identification>(
        "test_make_formatted_string", &test_object_identification::test_make_formatted_string, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_object_identification>(
        "test_parse_formatted_string", &test_object_identification::test_parse_formatted_string, *this ) );
}

//--------------------------------------

void
test_object_identification::test_make_formatted_string()
{
    object_identification_id_name idnamezeros( 0, 0 );
    stringex idnamezerosstrnoregex( idnamezeros.make_formatted_string() );
    stringex idnamezerosstrregex(   idnamezeros.make_formatted_string( true ) );

    CPPUNIT_ASSERT( idnamezerosstrnoregex == "0000000000-" );
    CPPUNIT_ASSERT( idnamezerosstrregex == "[0-9]+-.+" );
}

//--------------------------------------
void
test_object_identification::test_parse_formatted_string()
{
    object_identification_id_name idname1234test( 0, 0 );
    idname1234test.parse_formatted_string( "0000001234-test" );
    CPPUNIT_ASSERT( idname1234test.get_id() == 1234 );
    CPPUNIT_ASSERT( idname1234test.get_name() == "test" );
}

//--------------------------------------

// virtual
int
test_object_identification::countTestCases() const
{
    return 2;
}

//--------------------------------------

// virtual
void
test_object_identification::setUp()
{
}

//--------------------------------------

// virtual
void
test_object_identification::tearDown()
{
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<lifecycle::test_object_identification>;

//----------------------------------------------------------
// (end of file)
