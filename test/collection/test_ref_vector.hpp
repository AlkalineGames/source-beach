#if !defined(BEACH_COLLECTION_TEST_REF_VECTOR)
#define      BEACH_COLLECTION_TEST_REF_VECTOR
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_ref_vector.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace collection
{
        
//--------------------------------------

/// unit test for ptr_map

class test_ref_vector
    : public CppUnit::TestCase
{
public:

    test_ref_vector();
    virtual ~test_ref_vector();

    void register_tests( CppUnit::TestSuite * );

    void test_wrapped_iterator_index();

    /// @name TestCase overrides        
    //@{
    virtual int countTestCases() const;
    //@}
   
}; // end of class test_ref_vector

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_TEST_REF_VECTOR
