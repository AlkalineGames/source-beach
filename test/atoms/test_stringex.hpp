#if !defined(BEACH_ATOMS_TEST_STRINGEX)
#define      BEACH_ATOMS_TEST_STRINGEX
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_stringex.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace atoms
{

//--------------------------------------

/// unit test for stringex

class test_stringex
    : public CppUnit::TestCase
{
public:

    test_stringex();

    void register_tests( CppUnit::TestSuite * );

    void test_create_empty_string();
    void test_create_on_heap();
    void test_create_on_stack();
    void test_create_copy_on_heap();
    void test_create_copy_on_stack();
    void test_create_copy_on_return();
    void test_construct_from_zero_character();
    void test_construct_from_zero_character_with_count();
    void test_construct_from_zero_literal();
    void test_construct_from_zero_literal_with_count();
    void test_construct_from_zero_pointer();
    void test_construct_from_zero_pointer_with_count();
    void test_assign_zero_character();
    void test_assign_zero_pointer();
    void test_construct_fill_char();
    void test_case_conversion();
    void test_erase_white_space();
    void test_less_than_greater_than();
    void test_resize();
    void test_compare_case_insensitive();
    void test_find();
    void test_rfind();
    void test_find_first_of();
    void test_find_last_of();
    void test_substring();
    void test_replace();
    void test_insert();
    void test_is_empty();
    void test_compare();
    void test_starts_with();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

private:

    stringex make_copy_of_sample_text_1();

}; // end of class test_stringex

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_TEST_STRINGEX
