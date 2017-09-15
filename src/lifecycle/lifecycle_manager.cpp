//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lifecycle_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/lifecycle_manager.hpp> // this header

#include <atoms/primitives.hpp>
#include <lifecycle/allocation_center.hpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/lock_factory.hpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog.hpp>

#define BEACH_HAS_STATIC_OBJECTS

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static lifecycle_manager * singleton_cached = 0;

static byte lifecycle_manager_placement[sizeof(lifecycle_manager)];

//--------------------------------------
//  public methods
//--------------------------------------

// static
lifecycle_manager &
lifecycle_manager::acquire_singleton()
{
    if ( singleton_cached == 0 )
    {
        // !!! allocated into local static data to prevent
        // !!! infinite recursion through allocation center
        singleton_cached = new( lifecycle_manager_placement ) lifecycle_manager;
        singleton_cached->init();
    }
    return *singleton_cached;
}

//--------------------------------------

// static
void
lifecycle_manager::destroy_singleton()
{
    if ( singleton_cached != 0 )
    {
#ifdef BEACH_HAS_STATIC_OBJECTS
        // @@@ MUST KEEP allocation_center AROUND
        // @@@ UNTIL ALL STATIC OBJECTS ARE REMOVED
        object_catalog::destroy( *singleton_cached->_object_catalog );
#else
        // !!! don't delete because it was allocated using placement new
        //delete singleton_cached;
        singleton_cached->~lifecycle_manager();
        singleton_cached = 0;
#endif
    }
}

//--------------------------------------

void
lifecycle_manager::set_singleton(
    lifecycle_manager * in_singleton )
{
    singleton_cached = in_singleton;
}

//--------------------------------------
//  private methods
//--------------------------------------

lifecycle_manager::lifecycle_manager()
{}

//--------------------------------------

lifecycle_manager::~lifecycle_manager()
{
    object_catalog      ::destroy( *_object_catalog );
    logger              ::destroy( *_logger );
    lock_factory        ::destroy( *_lock_factory );
    class_catalog       ::destroy( *_class_catalog );
    allocation_center   ::destroy( *_allocation_center );
}

//--------------------------------------

void
lifecycle_manager::init()
{
    _allocation_center  = &(allocation_center   ::create());
    _class_catalog      = &(class_catalog       ::create());
    _lock_factory       = &(lock_factory        ::create());
    _logger             = &(logger              ::create());
    _object_catalog     = &(object_catalog      ::create());
}

//--------------------------------------

void
lifecycle_manager::set_lock_factory(
    lock_factory & in_lock_factory )
{
    lock_factory::destroy( *_lock_factory );
    _lock_factory = &in_lock_factory;
}

//--------------------------------------

void
lifecycle_manager::set_logger(
    logger & in_logger )
{
    logger::destroy( *_logger );
    _logger = &in_logger;
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  public C API
//--------------------------------------

extern "C" {

  void lifecycle_lifecycle_manager_acquire_singleton() {
      lifecycle::lifecycle_manager::acquire_singleton();      
  }
  void lifecycle_lifecycle_manager_destroy_singleton() {
      lifecycle::lifecycle_manager::destroy_singleton();      
  }

}; // end of extern "C"

//----------------------------------------------------------
// (end of file)
