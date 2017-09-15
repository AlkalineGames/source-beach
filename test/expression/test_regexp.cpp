//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_regexp.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_regexp.hpp"

#include <expression/regular_expression.hpp>
#include <expression/splash.h>

#include <cppunit/TestCaller.h>

namespace expression
{
	using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text sample_text_1[] =
    "123 456 789 AA AB AC AD";

static regular_expression sample_regexp_1(
    "^123", regular_expression::nocase );

static regular_expression command_expression_help_on(
    "^[ \t]*(help)[ \t]+([^ \t]+)[ \t]*$", regular_expression::nocase );

static regular_expression command_expression_add_technique(
    "^[ \t]*(addtech|at)[ \t]+([^ \t]+)[ \t]*$", regular_expression::nocase );

static regular_expression command_expression_adj(
    "^[ \t]*(adjust|adj)[ \t]*$", regular_expression::nocase );

//--------------------------------------
//  public methods
//--------------------------------------

test_regexp::test_regexp()
  :
    CppUnit::TestCase( "test_regexp" )
{}

//--------------------------------------

void
test_regexp::register_tests(
    CppUnit::TestSuite * suite )
{

    suite->addTest( new CppUnit::TestCaller<test_regexp>(
        "test_1", &test_regexp::test_1, *this ) );
}

//--------------------------------------

void
test_regexp::test_1()
{

   SPString     unparsed( sample_text_1 ); // EXPRESSION
   SPStringList parsed;
   unparsed.m( sample_regexp_1, parsed );

   SPString sp( sample_text_1 );

/*
    if ( parsed.count() > 1 )
    {
        display_help( out.get_real_stream() );
        return true;
    }
*/
  //  stringex * s = new stringex( sample_text_1 );
  //  CPPUNIT_ASSERT( std::string( s->get_text()) == sample_text_1 );

   // CPPUNIT_ASSERT( parsed.count() > 1 );
}

//--------------------------------------

// virtual
int
test_regexp::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_regexp::setUp()
{
}

//--------------------------------------

// virtual
void
test_regexp::tearDown()
{}

//--------------------------------------

}; // end of namespace atoms

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<expression::test_regexp>;

//----------------------------------------------------------
// (end of file)
