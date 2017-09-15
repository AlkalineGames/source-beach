#if !defined(BEACH_LIFECYCLE_TEST_ALLOCATION_CENTER)
#define      BEACH_LIFECYCLE_TEST_ALLOCATION_CENTER
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_allocation_center.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace lifecycle
{

//--------------------------------------

/// unit test for allocation_center
        
class test_allocation_center
    : public CppUnit::TestCase
{
public:

    test_allocation_center();

    void register_tests( CppUnit::TestSuite * );

    void test_center_new_delete();
    void test_class_new_delete();
    void test_global_new_delete();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

}; // end of class test_allocation_center

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_TEST_ALLOCATION_CENTER
