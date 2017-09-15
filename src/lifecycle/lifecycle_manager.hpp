#if !defined(BEACH_LIFECYCLE_LIFECYCLE_MANAGER)
#define      BEACH_LIFECYCLE_LIFECYCLE_MANAGER
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lifecycle_manager.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

/// Beach Lifecycle Framework
namespace lifecycle
{
    class allocation_center;
    class class_catalog;
    class lock_factory;
    class logger;
    class object_catalog;

//--------------------------------------

/// manager of all lifecycle singletons
/**
 *  Special notes regarding this Singleton:
 *
 *  In order to ensure that there is only one singleton of
 *  the lifecycle manager across multiple components within a
 *  process, the following must be enforced:
 *
 *  1. The primary component (first non-automatic execution)
 *      should call get_singleton() causing an automatic
 *      creation of the singleton instance in the primary
 *      component's C++ static data area.
 *
 *  2. All secondary components should call set_singleton(...)
 *      with the address of the singleton instance passed
 *      explicitly from the primary component, before any of
 *      its code ever calls get_singleton().
 *
 *  This is necessary because separate components within a
 *  process (i.e. main program versus dynamic/shared libraries),
 *  each have their own copy of C++ static data.
 *
 *  @note   design patterns applied:
 *              - Mediator  [GoF]
 *              - Singleton [GoF]
 */      
class lifecycle_manager
{
friend class lock_factory;
friend class logger;
public:

    /// @name lifecycle
    /** creation should happen once per process for all components
        secondary components must call set_singleton(...)
        prior to any call of get_singleton to ensure this. */
    //@{
    static lifecycle_manager &  acquire_singleton(); ///< call immediately after process starts
    static void                 destroy_singleton(); ///< only call immediately before process ends
    static void                 set_singleton( lifecycle_manager * );
    //@}

    allocation_center & get_allocation_center() { return *_allocation_center; }
    class_catalog &     get_class_catalog()     { return *_class_catalog; }
    lock_factory &      get_lock_factory()      { return *_lock_factory; }
    logger &            get_logger()            { return *_logger; }
    object_catalog &    get_object_catalog()    { return *_object_catalog; }

private:

    /// @name copy operations not implemented
    //@{
    lifecycle_manager(              const lifecycle_manager & );
    lifecycle_manager & operator =( const lifecycle_manager & );
    //@}

    lifecycle_manager();
    ~lifecycle_manager();

    void init();
    void set_lock_factory(  lock_factory & );
    void set_logger(        logger & );

    allocation_center * _allocation_center;
    class_catalog *     _class_catalog;
    lock_factory *      _lock_factory;
    logger *            _logger;
    object_catalog *    _object_catalog;

}; // end of class lifecycle_manager

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_LIFECYCLE_MANAGER
