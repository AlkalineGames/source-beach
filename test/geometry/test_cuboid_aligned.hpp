#if !defined(BEACH_GEOMETRY_TEST_CUBOID_ALIGNED)
#define      BEACH_GEOMETRY_TEST_CUBOID_ALIGNED
//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_cuboid_aligned.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace geometry
{

//--------------------------------------

/// unit test for cuboid_aligned

class test_cuboid_aligned
    : public CppUnit::TestCase
{
public:

    test_cuboid_aligned();

    void register_tests( CppUnit::TestSuite * );

    void test_side_of_plane();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

}; // end of class test_cuboid_aligned

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_TEST_CUBOID_ALIGNED
