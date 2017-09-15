//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_ref_set_of_string.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_ref_set_of_string.hpp"

#include <atoms/stringex.hpp>
#include <collection/ref_set_of_string.hpp>

#include <cppunit/TestCaller.h>

namespace collection
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

test_ref_set_of_string::test_ref_set_of_string()
  :
    CppUnit::TestCase( "test_ref_set_of_string" )
{}

//--------------------------------------

// virtual
test_ref_set_of_string::~test_ref_set_of_string()
{}

//--------------------------------------

void
test_ref_set_of_string::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_ref_set_of_string>(
        "test_insertions", &test_ref_set_of_string::test_insertions, *this ) );
}

//--------------------------------------

void
test_ref_set_of_string::test_insertions()
{
    typedef ref_set_of_string collection;

    // !!! out of alphabetical order so that sorting by
    // !!! address/pointer values will not produce alphabetical order    
    stringex stringb( "beta" );
    stringex stringa( "alpha" );
    stringex stringd( "delta" );
    stringex stringc( "charlie" );
    stringex stringe( "echo" );

    collection collect;

    collect.insert( stringd );
    CPPUNIT_ASSERT( collect.size() == 1 );
    collect.insert( stringb );
    CPPUNIT_ASSERT( collect.size() == 2 );
    collect.insert( stringe );
    CPPUNIT_ASSERT( collect.size() == 3 );
    collect.insert( stringa );
    CPPUNIT_ASSERT( collect.size() == 4 );
    collect.insert( stringc );
    CPPUNIT_ASSERT( collect.size() == 5 );

    collection::const_iterator iter( collect.begin() );
    const stringex & member1 = *iter;
    CPPUNIT_ASSERT(  member1 ==  stringa );
    CPPUNIT_ASSERT( &member1 == &stringa );
    iter++;
    const stringex & member2 = *iter;
    CPPUNIT_ASSERT(  member2 ==  stringb );
    CPPUNIT_ASSERT( &member2 == &stringb );
    iter++;
    const stringex & member3 = *iter;
    CPPUNIT_ASSERT(  member3 ==  stringc );
    CPPUNIT_ASSERT( &member3 == &stringc );
    iter++;
    const stringex & member4 = *iter;
    CPPUNIT_ASSERT(  member4 ==  stringd );
    CPPUNIT_ASSERT( &member4 == &stringd );
    iter++;
    const stringex & member5 = *iter;
    CPPUNIT_ASSERT(  member5 ==  stringe );
    CPPUNIT_ASSERT( &member5 == &stringe );
    iter++;
    CPPUNIT_ASSERT( iter == collect.end() );
}

//--------------------------------------

// virtual
int
test_ref_set_of_string::countTestCases() const
{
    return 1;
}

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
// (end of file)
