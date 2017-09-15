//----------------------------------------------------------
//  Copyright 2007-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lock.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/lock.hpp> // this header

namespace lifecycle
{

//--------------------------------------
//  public methods
//--------------------------------------

// virtual 
lock::~lock()
{}

//--------------------------------------

// virtual
boolean
lock::acquire()
{
    return false;
}

//--------------------------------------

// virtual
boolean
lock::release()
{
    return false;
}

//--------------------------------------

// virtual
boolean
lock::is_locked()
{
    return false;
}

//--------------------------------------
//  protected methods
//--------------------------------------

lock::lock()
{}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: lock.cpp,v $
// Revision 1.1  2007/01/16 01:18:13  cat
// creation
//
//----------------------------------------------------------

// (end of file)
