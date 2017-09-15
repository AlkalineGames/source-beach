//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       initialization_coordinator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/initialization_coordinator.hpp> // this header

#include <lifecycle/execution_coordinator.hpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <invocation/command_kill.tpp>

//--------------------------------------

namespace lifecycle
{

//--------------------------------------
//  private members
//--------------------------------------

static const text global_catalog_name[]
    = "initialization_coordinator_global";

//--------------------------------------
//  public methods
//--------------------------------------

// static
execution_coordinator & 
initialization_coordinator::get_global_instance()
{
    return lifecycle::object_catalog_utility<execution_coordinator,execution_coordinator>
            ::acquire_object( global_catalog_name );
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<lifecycle::execution_coordinator>;

//----------------------------------------------------------
// $Log: initialization_coordinator.cpp,v $
// Revision 1.7  2007/12/14 23:21:56  cat
// moved template instantiations outside of the namespace for GCC 4.1 compatability
//
// Revision 1.6  2007/01/23 08:15:41  cat
// refactored singleton to use object_catalog_utility
//
// Revision 1.5  2005/08/30 05:11:03  cat
// renamed sanddune to beach
//
// Revision 1.4  2004/12/28 20:17:11  cat
// corrected template instantiation syntax
//
// Revision 1.3  2004/01/06 20:41:23  cat
// renamed and moved all command classes from SandDune notification to invocation
//
// Revision 1.2  2003/09/05 06:08:21  cat
// instantiate template
//
// Revision 1.1  2003/08/19 03:00:42  cat
// creation
//----------------------------------------------------------

// (end of file)
