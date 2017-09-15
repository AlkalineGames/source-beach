//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_ref_vector.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_ref_vector.hpp"

#include <atoms/stringex.hpp>
#include <collection/ref_vector.hpp>

#include <cppunit/TestCaller.h>

//--------------------------------------

namespace collection
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

test_ref_vector::test_ref_vector()
  :
    CppUnit::TestCase( "test_ref_vector" )
{}

//--------------------------------------

// virtual
test_ref_vector::~test_ref_vector()
{}

//--------------------------------------

void
test_ref_vector::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_ref_vector>(
        "test_wrapped_iterator_index", &test_ref_vector::test_wrapped_iterator_index, *this ) );
}

//--------------------------------------

void
test_ref_vector::test_wrapped_iterator_index()
{
    typedef ref_vector<stringex> collection;
    
    collection collect;
    collection::wrapped_iterator i( collect ); 

    whole indexatbegin = i.index();
    CPPUNIT_ASSERT( indexatbegin == 0 );

    stringex * item1 = new stringex( "item1" ); 

    i.add( *item1 );
    int indexafteradd1 = i.index();
    CPPUNIT_ASSERT( indexafteradd1 == 0 );

    i.first();
    int indexafterfirst = i.index();
    CPPUNIT_ASSERT( indexafterfirst == 0 );

    i.next();
    int indexafternext1 = i.index();
    CPPUNIT_ASSERT( indexafternext1 == 1 );

    i.prev();
    int indexafterprev = i.index();
    CPPUNIT_ASSERT( indexafterprev == 0 );

    stringex * item2 = new stringex( "item2" ); 

    i.add( *item2 );
    int indexafteradd2 = i.index();
    CPPUNIT_ASSERT( indexafteradd2 == 1 );

    i.next();
    int indexafternext2 = i.index();
    CPPUNIT_ASSERT( indexafternext2 == 2 );

    i.prev();
    int indexafterprev2 = i.index();
    CPPUNIT_ASSERT( indexafterprev2 == 1 );

    i.remove();
    int indexafterremove2 = i.index();
    CPPUNIT_ASSERT( indexafterremove2 == 1 );
    delete item2;
    
    i.first();
    int indexafterfirst2 = i.index();
    CPPUNIT_ASSERT( indexafterfirst2 == 0 );
    
    i.remove();
    int indexafterremove1 = i.index();
    CPPUNIT_ASSERT( indexafterremove1 == 0 );
    delete item1;
}

//--------------------------------------

// virtual
int
test_ref_vector::countTestCases() const
{
    return 1;
}

//--------------------------------------

}; // end of namespace collection

//--------------------------------------
//  template instantiations
//--------------------------------------

//template class collection::ref_vector<atoms::stringex>;

//----------------------------------------------------------
// (end of file)
