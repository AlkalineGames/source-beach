#if !defined(BEACH_LIFECYCLE_TEST_OBJECT_IDENTIFICATION)
#define      BEACH_LIFECYCLE_TEST_OBJECT_IDENTIFICATION
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_object_identification.hpp
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

/// unit test for object_identification
        
class test_object_identification
    : public CppUnit::TestCase
{
public:

    test_object_identification();

    void register_tests( CppUnit::TestSuite * );

    void test_make_formatted_string();
    void test_parse_formatted_string();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

private:


}; // end of class test_object_identification

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_TEST_OBJECT_IDENTIFICATION
