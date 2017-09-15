#if !defined(BEACH_COLLECTION_TEST_STD_MAP)
#define      BEACH_COLLECTION_TEST_STD_MAP
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_std_map.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace collection
{
    using atoms::stringex;
    using atoms::whole16;
        
//--------------------------------------

/// unit test for Standard C++ map

class test_std_map
    : public CppUnit::TestCase
{
public:

    test_std_map();

    void register_tests( CppUnit::TestSuite * );

    void test_std_map_basic();
    void test_std_map_typedef();
    void test_std_map_ref();
    void test_std_map_owned();

    /// @name TestCase overrides        
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}
   
    class test_element
    {
    public:
        test_element( whole16 id, const char * text );
        ~test_element();
        whole16 get_id() const { return _id; }
        const char * get_text() const { return _text; }
    private:
        whole16  _id;
        stringex _text;
    };

}; // end of class test_std_map

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_TEST_STD_MAP
