#if !defined(BEACH_SERIALIZATION_TEST_CONFIG_FILE)
#define      BEACH_SERIALIZATION_TEST_CONFIG_FILE
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_config_file.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace serialization
{
        
//--------------------------------------

/// unit test for config_file

class test_config_file
    : public CppUnit::TestCase
{
public:

    test_config_file();

    void register_tests( CppUnit::TestSuite * );

    void test_construction();
    void test_usage();

    /// @name TestCase overrides        
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}

}; // end of class test_config_file

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEST_CONFIG_FILE
