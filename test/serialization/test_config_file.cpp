//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_config_file.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include "test_config_file.hpp" 

#include <atoms/stringex.hpp>
#include <serialization/config_file.hpp>

#include <cppunit/TestCaller.h>

namespace serialization
{

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text test_file_name[] =
    "cfg_file_unit_test.cfg";

//--------------------------------------
//  public methods
//--------------------------------------

test_config_file::test_config_file()
  :
    CppUnit::TestCase( "test_config_file" )
{}

//--------------------------------------

void
test_config_file::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_config_file>(
        "test_construction", &test_config_file::test_construction, *this ) );

    suite->addTest( new CppUnit::TestCaller<test_config_file>(
        "test_usage", &test_config_file::test_usage, *this ) );
}

//--------------------------------------

void 
test_config_file::test_construction()
{
    config_file * cf = new config_file( test_file_name );
    delete cf;
}

//--------------------------------------

void 
test_config_file::test_usage()
{
    config_file cf(test_file_name);

    stringex name1 = test_file_name;
    stringex name2 = cf.get_file_name();
    CPPUNIT_ASSERT( name1 == name2 );

    stringex default_text = "default text";
    stringex null_text = "";
    stringex text_section = "text_samples";
    stringex num_section  = "number_samples";
    stringex text1 = "Hello!";
    stringex text2 = "This is a test.";
    int num1 = 0;
    int num2 = -1;
    int num3 = 9999;

    cf.set_text(   text_section, "text_key_1", text1 );

    // return;

    cf.set_text(   text_section, "text_key_2", text2 );
    cf.set_number( num_section,  "num_key_1",  num1 );
    cf.set_number( num_section,  "num_key_2",  num2 );
    cf.set_number( num_section,  "num_key_3",  num3 );

    stringex td = cf.get_text( text_section, "text_key_d", default_text );
    stringex t0 = cf.get_text( text_section, "text_key_0" ); // defaults to null
    stringex t1 = cf.get_text( text_section, "text_key_1" );
    stringex t2 = cf.get_text( text_section, "text_key_2" );

    int nd = cf.get_number( num_section, "num_key_d", 7777 ); // defaults to 7777
    int n0 = cf.get_number( num_section, "num_key_0" ); // defaults to 0
    int n1 = cf.get_number( num_section, "num_key_1" );
    int n2 = cf.get_number( num_section, "num_key_2" );
    int n3 = cf.get_number( num_section, "num_key_3" );

    CPPUNIT_ASSERT( td == default_text );
    CPPUNIT_ASSERT( t0 == null_text );
    CPPUNIT_ASSERT( t1 == text1 );
    CPPUNIT_ASSERT( t2 == text2 );
    CPPUNIT_ASSERT( nd == 7777 );
    CPPUNIT_ASSERT( n0 == 0 );
    CPPUNIT_ASSERT( n1 == num1 );
    CPPUNIT_ASSERT( n2 == num2 );
    CPPUNIT_ASSERT( n3 == num3 );
}

//--------------------------------------

// virtual
int
test_config_file::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_config_file::setUp()
{}

//--------------------------------------

// virtual
void
test_config_file::tearDown()
{}

//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<serialization::test_config_file>;

//----------------------------------------------------------
// (end of file)
