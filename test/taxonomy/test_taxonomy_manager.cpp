//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_taxonomy_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_taxonomy_manager.hpp"

#include <taxonomy/taxonomy_manager.hpp>

#include <cstring>

namespace taxonomy
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

test_taxonomy_manager::test_taxonomy_manager()
  :
    CppUnit::TestCase( "test_taxonomy_manager" )
{}

//--------------------------------------

void
test_taxonomy_manager::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_taxonomy_manager>(
        "test_acquire_label", &test_taxonomy_manager::test_acquire_label, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_taxonomy_manager>(
        "test_acquire_property_set", &test_taxonomy_manager::test_acquire_property_set, *this ) );
}

//--------------------------------------

void
test_taxonomy_manager::test_acquire_label()
{   
    static const text textf[] = "foxtrot";
    static const text textg[] = "golf";
    static const text texth[] = "hotel";
   
    const stringex & labelf = taxonomy_manager::acquire_singleton()
        .acquire_label( textf ); 
    CPPUNIT_ASSERT( labelf == textf );
    const stringex & labelg = taxonomy_manager::acquire_singleton()
        .acquire_label( textg ); 
    CPPUNIT_ASSERT( labelg == textg );
    taxonomy_manager * taxman =
        taxonomy_manager::find_singleton();
    CPPUNIT_ASSERT( taxman != 0 );
    if ( taxman != 0 )
    {
        const stringex & labelh = taxman->acquire_label( texth ); 
        CPPUNIT_ASSERT( labelh == texth );
    }
}

//--------------------------------------

void
test_taxonomy_manager::test_acquire_property_set()
{   
    const property_set & propsetref1 =
        taxonomy_manager::acquire_singleton()
            .acquire_property_set( "india" );
    const property_set & propsetref2 =
        taxonomy_manager::acquire_singleton()
            .acquire_property_set( "india" );
    CPPUNIT_ASSERT( &propsetref1 == &propsetref2 );
}

//--------------------------------------

// virtual
int
test_taxonomy_manager::countTestCases() const
{
    return 2;
}

//--------------------------------------

// virtual
void
test_taxonomy_manager::setUp()
{ 
    // nothing to do 
}

//--------------------------------------

// virtual
void
test_taxonomy_manager::tearDown()
{ 
    // nothing to do 
}
   
//--------------------------------------

}; // end of namespace taxonomy

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<taxonomy::test_taxonomy_manager>;

//----------------------------------------------------------
// (end of file)
