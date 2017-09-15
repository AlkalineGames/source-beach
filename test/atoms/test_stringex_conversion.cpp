//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_stringex_conversion.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include "test_stringex_conversion.hpp"

#include <atoms/stringex.hpp>
#include <atoms/stringex_conversion.hpp>

namespace atoms
{

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text sample_text_1[] =
    "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789";

static const text sample_text_2[] =
    "~!@#$%^&*()[]{}<>,./?'\";:\\`";

//--------------------------------------
//  public methods
//--------------------------------------

test_stringex_conversion::test_stringex_conversion()
  :
    CppUnit::TestCase( "test_stringex_conversion" )
{}

//--------------------------------------

void
test_stringex_conversion::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_stringex_conversion>(
        "test_conversions_1", &test_stringex_conversion::test_conversions_1, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex_conversion>(
        "test_conversions_2", &test_stringex_conversion::test_conversions_2, *this ) );
}

//--------------------------------------

void
test_stringex_conversion::test_conversions_1()
{
    long longVal=25;
    whole8  whole8Val=25;
    whole16 whole16Val=25;
    whole32 whole32Val=25;
    whole64 whole64Val=25;

    stringex strLongVal(      stringex_conversion::from( longVal ) );
    stringex strwhole8Val(    stringex_conversion::from( whole8Val ) );
    stringex strwhole16Val(   stringex_conversion::from( whole16Val ) );
    stringex strwhole32Val(   stringex_conversion::from( whole32Val ) );
    stringex strwhole64Val(   stringex_conversion::from( whole64Val ) );

    CPPUNIT_ASSERT( strLongVal == strwhole8Val  );
    CPPUNIT_ASSERT( strLongVal == strwhole16Val );
    CPPUNIT_ASSERT( strLongVal == strwhole32Val );
    CPPUNIT_ASSERT( strLongVal == strwhole64Val );
}

//--------------------------------------
void
test_stringex_conversion::test_conversions_2()
{
    whole8  whole8Val =25;
    whole16 whole16Val=25;
    whole32 whole32Val=25;
    whole64 whole64Val=25;

    whole8  result8Val =0;
    whole16 result16Val=0;
    whole32 result32Val=0;
    whole64 result64Val=0;

    stringex strwhole8Val(  stringex_conversion::from( whole8Val ) );
    stringex strwhole16Val( stringex_conversion::from( whole16Val ) );
    stringex strwhole32Val( stringex_conversion::from( whole32Val ) );
    stringex strwhole64Val( stringex_conversion::from( whole64Val ) );

    stringex_conversion::to( result8Val,  strwhole8Val  );
    stringex_conversion::to( result16Val, strwhole16Val );
    stringex_conversion::to( result32Val, strwhole32Val );
    stringex_conversion::to( result64Val, strwhole64Val );

    CPPUNIT_ASSERT( result8Val  == whole8Val );
    CPPUNIT_ASSERT( result16Val == whole16Val);
    CPPUNIT_ASSERT( result32Val == whole32Val);
    CPPUNIT_ASSERT( result64Val == whole64Val);
}

//--------------------------------------

// virtual
int
test_stringex_conversion::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_stringex_conversion::setUp()
{
}

//--------------------------------------

// virtual
void
test_stringex_conversion::tearDown()
{
}

//--------------------------------------

}; // end of namespace atoms

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<atoms::test_stringex_conversion>;

//----------------------------------------------------------
// (end of file)
