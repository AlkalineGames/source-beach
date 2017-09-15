#if !defined(BEACH_EXPRESSION_TEST_REGEXP)
#define      BEACH_EXPRESSION_TEST_REGEXP
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_regexp.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace expression
{

//--------------------------------------

// unit test for regexp
        
class test_regexp
    : public CppUnit::TestCase
{
public:

    test_regexp();

    void register_tests( CppUnit::TestSuite * );

    void test_1();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

}; // end of class test_regexp

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_EXPRESSION_TEST_REGEXP
