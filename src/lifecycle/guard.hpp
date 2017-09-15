#if !defined(BEACH_LIFECYCLE_GUARD)
#define      BEACH_LIFECYCLE_GUARD

//----------------------------------------------------------
//  Copyright 2007-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       guard.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/lock.hpp>

//--------------------------------------

namespace lifecycle
{

//--------------------------------------

/// synchronization guard for scoped locking
/**
 *  @note   Passing a null object lock will effectively turn
 *          this guard into a benign null object that does nothing.
 *
 *  @note   design patterns applied:
 *              - Null Object       [PLoP3]
 *              - Scoped Locking    [POSA2]
 */
class guard
{
public:

    guard( lock & in_lock )
      :
        _lock( in_lock )
    {
        _lock.acquire();
    }
    ~guard()
    {
        _lock.release();
    }

private:

    /// @name copy operations not implemented
    //@{
    guard(              const guard & );
    guard & operator =( const guard & );
    //@}

    lock & _lock;

}; // end of class guard

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: guard.hpp,v $
// Revision 1.1  2007/01/19 14:07:50  cat
// creation
//
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_GUARD
