#if !defined(BEACH_LIFECYCLE_LOCK)
#define      BEACH_LIFECYCLE_LOCK
//----------------------------------------------------------
//  Copyright 2007-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lock.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>

namespace lifecycle
{
    using atoms::boolean;

//--------------------------------------

/// lock superclass
/**
 *  @note   An unsubclassed instance of this class
 *          is a benign null object that does nothing.
 *
 *  @note   design patterns applied:
 *              - Null Object [PLoP3]
 */
class lock
{
friend class lock_factory;
public:

    BEACH_ALLOCATION_OPERATORS

    /// @name overrideables, these all return false at this level [null object]
    //@{
    virtual boolean acquire();
    virtual boolean release();
    virtual boolean is_locked();
    //@}

protected:

    lock();
    virtual ~lock();

private:

    /// @name copy operations not implemented
    //@{
    lock(              const lock & );
    lock & operator =( const lock & );
    //@}

}; // end of class lock

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_LOCK
