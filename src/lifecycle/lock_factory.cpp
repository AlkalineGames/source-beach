//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lock_factory.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/lock_factory.hpp> // this header

#include <lifecycle/lock.hpp>

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

/// null object subclass of lock_factory
class lock_factory_null
    : public lock_factory
{};

//--------------------------------------

static const text this_class_name[]
    = "lock_factory";

static lock_factory * cached_singleton = 0;
    
//--------------------------------------
//  public methods
//--------------------------------------

// virtual 
lock & 
lock_factory::create_lock()
{
    // intended for override, so create null object
    return *(new lock());
}

//--------------------------------------

// virtual 
void
lock_factory::destroy_lock(
    lock & in_lock )
{
    delete &in_lock;
}

//--------------------------------------
//  protected methods
//--------------------------------------

lock_factory::lock_factory()
{}

//--------------------------------------

// virtual 
lock_factory::~lock_factory()
{}

//--------------------------------------
//  private methods
//--------------------------------------

// static
lock_factory &
lock_factory::create()
{
    return *(new lock_factory);
}

//--------------------------------------

// static
void
lock_factory::destroy(
    lock_factory & in_singleton )
{
    delete &static_cast<lock_factory&>(in_singleton);
}

//--------------------------------------

}; // end of namespace settings

//----------------------------------------------------------
// (end of file)
