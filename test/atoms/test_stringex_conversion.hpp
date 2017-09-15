#if !defined(BEACH_ATOMS_TEST_STRINGEX_CONVERSION)
#define      BEACH_ATOMS_TEST_STRINGEX_CONVERSION
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_stringex_conversion.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace atoms
{

//--------------------------------------

/// unit test for stringex_conversion
        
class test_stringex_conversion
    : public CppUnit::TestCase
{
public:

    test_stringex_conversion();

    void register_tests( CppUnit::TestSuite * );

    void test_conversions_1();
    void test_conversions_2();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

private:


}; // end of class test_stringex_conversion

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_TEST_STRINGEX_CONVERSION
