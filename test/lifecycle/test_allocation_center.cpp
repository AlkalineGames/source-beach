//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_allocation_center.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_allocation_center.hpp"

#include <atoms/allocation.hpp>
#include <lifecycle/allocation_center.hpp>

namespace lifecycle
{

//--------------------------------------
//  public methods
//--------------------------------------

test_allocation_center::test_allocation_center()
  :
    CppUnit::TestCase( "test_allocation_center" )
{}

//--------------------------------------

void
test_allocation_center::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_allocation_center>(
        "test_center_new_delete", &test_allocation_center::test_center_new_delete, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_allocation_center>(
        "test_class_new_delete", &test_allocation_center::test_class_new_delete, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_allocation_center>(
        "test_global_new_delete", &test_allocation_center::test_global_new_delete, *this ) );
}

//--------------------------------------

void
test_allocation_center::test_center_new_delete()
{
    allocation_center & ac = allocation_center::get_singleton();

    void * singledata = 0;
    singledata = ac.allocate( 100, __FILE__, __LINE__ );
    CPPUNIT_ASSERT( singledata != 0 );

    ac.deallocate( singledata, __FILE__, __LINE__ );
}

//--------------------------------------

class class_sample
{
public:
    class_sample();
    ~class_sample();
    BEACH_ALLOCATION_OPERATORS
private:
    int a, b, c;
};
class_sample::class_sample()
  : a( 1 ), b( 1 ), c( 1 )
{}
class_sample::~class_sample()
{
    a = 0; b = 0; c = 0;
}

void
test_allocation_center::test_class_new_delete()
{
    // without placement we get the file and line of the class methods
    class_sample * singlesample1 = 0;
    singlesample1 = new class_sample;
    CPPUNIT_ASSERT( singlesample1 != 0 );

    class_sample * arraysample1 = 0;
    arraysample1 = new class_sample[5];
    CPPUNIT_ASSERT( arraysample1 != 0 );

    // using placement gives us the file and line of these statements
    class_sample * singlesample2 = 0;
    singlesample2 = new BEACH_ALLOCATION class_sample;
    CPPUNIT_ASSERT( singlesample2 != 0 );

    class_sample * arraysample2 = 0;
    arraysample2 = new BEACH_ALLOCATION class_sample[5];
    CPPUNIT_ASSERT( arraysample2 != 0 );

    delete [] arraysample2;
    delete singlesample2;
    delete [] arraysample1;
    delete singlesample1;
}

//--------------------------------------

class global_sample
{
public:
    global_sample();
    ~global_sample();
private:
    int a, b, c;
};
global_sample::global_sample()
  : a( 1 ), b( 1 ), c( 1 )
{}
global_sample::~global_sample()
{
    a = 0; b = 0; c = 0;
}

void
test_allocation_center::test_global_new_delete()
{
    global_sample * singlesample = 0;
    singlesample = new BEACH_ALLOCATION global_sample;
    CPPUNIT_ASSERT( singlesample != 0 );

    global_sample * arraysample = 0;
    arraysample = new BEACH_ALLOCATION global_sample[5];
    CPPUNIT_ASSERT( arraysample != 0 );

    // !!! YUCKY, but the only way
    BEACH_DELETE(global_sample,singlesample);
    //  expands to:
    //    singlesample->~global_sample(); 
    //    ::operator delete( singlesample, BEACH_ALLOCATION );

    // !!! THIS FAILS BECAUSE IT DOES NOT ITERATE THE DESTRUCTOR
    // LIFECYCLE_DELETE(global_sample,arraysample);

    /// ### this does not call the 'placement' delete
    delete [] arraysample;
}

//--------------------------------------

// virtual
int
test_allocation_center::countTestCases() const
{
    return 3;
}

//--------------------------------------

// virtual
void
test_allocation_center::setUp()
{
}

//--------------------------------------

// virtual
void
test_allocation_center::tearDown()
{
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<lifecycle::test_allocation_center>;

//----------------------------------------------------------
// (end of file)
