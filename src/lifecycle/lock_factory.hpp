#if !defined(BEACH_LIFECYCLE_LOCK_FACTORY)
#define      BEACH_LIFECYCLE_LOCK_FACTORY
//----------------------------------------------------------
//  Copyright 2007-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lock_factory.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <lifecycle/lifecycle_manager.hpp>

namespace lifecycle
{
    class lock;

//--------------------------------------

/// abstract factory of synchronization locks
/**
 *  It is intended that a subclass will be made
 *  as a Wrapper Facade around the actual platform
 *  implementation for synchronization locks.
 *
 *  If no subclass is installed (via set_singleton(...))
 *  then a null object factory instance will be created
 *  that in turn creates benign null object locks.
 *
 *  @note   design patterns applied:
 *              - Abstract Factory  [GoF]
 *              - Factory Method    [GoF]
 *              - Mediator          [GoF]
 *              - Null Object       [PLoP3]
 *              - Singleton         [GoF]
 *              - Wrapper Facade    [POSA2]
 */
class lock_factory
{
friend class lifecycle_manager;
public:

    BEACH_ALLOCATION_OPERATORS

    static lock_factory & get_singleton()
    {
        return lifecycle_manager::acquire_singleton()
            .get_lock_factory();
    }
    /// @name factory methods
    //@{
    virtual lock & create_lock(); ///< intended for override, this level creates a null lock
    virtual void   destroy_lock( lock & ); 
    //@}

protected:

    static void set_singleton( lock_factory & in_singleton )
    {
        lifecycle_manager::acquire_singleton().set_lock_factory(
            in_singleton );
    }
    lock_factory();
    virtual ~lock_factory();

private:

    /// @name copy operations not implemented
    //@{
    lock_factory(              const lock_factory & );
    lock_factory & operator =( const lock_factory & );
    //@}

    /// @name only by lifecycle_manager
    //@{
    static lock_factory &   create();
    static void             destroy( lock_factory & );
    //@}
    
}; // end of class lock_factory

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_LOCK_FACTORY
