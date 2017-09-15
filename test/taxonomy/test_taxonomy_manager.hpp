#if !defined(BEACH_TAXONOMY_TEST_TAXONOMY_MANAGER)
#define      BEACH_TAXONOMY_TEST_TAXONOMY_MANAGER
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_taxonomy_manager.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace taxonomy
{
    class label;
        
//--------------------------------------

class test_taxonomy_manager
    : public CppUnit::TestCase
{
public:

    test_taxonomy_manager();

    void register_tests( CppUnit::TestSuite * );

    void test_acquire_label();
    void test_acquire_property_set();

    /// @name TestCase overrides        
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}
   
}; // end of class test_taxonomy_manager

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_TEST_TAXONOMY_MANAGER
