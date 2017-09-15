#if !defined(BEACH_NOTIFICATION_TEST_OBSERVABLE)
#define      BEACH_NOTIFICATION_TEST_OBSERVABLE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_observable.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

namespace notification
{
    class observable_imp;
        
//--------------------------------------

/// unit test for observable
      
class test_observable
    : public CppUnit::TestCase
{
public:

    test_observable();

    void registerTests( CppUnit::TestSuite * );

    void test_attach_observer();
    void test_insert_observer();
    void test_detach_observer();
    void test_notify_observers_with_flags(); 
    void test_notify_observers_without_flags();

    /// @name TestCase overrides
    //@{
    virtual int  countTestCases() const;
    virtual void setUp();
    virtual void tearDown();
    //@}
   
private:

    observable_imp * _observable;
    
}; // end of class test_observable

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_TEST_OBSERVABLE
