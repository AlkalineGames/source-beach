//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       execution_coordinator.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/execution_coordinator.hpp>  // this header

#include <lifecycle/logger.hpp>
#include <invocation/command.hpp>

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[] =
    "execution_coordinator";

//--------------------------------------
//  public methods
//--------------------------------------

execution_coordinator::execution_coordinator()
  :
    _commands( atoms::destroyer<command>() )
{}

//--------------------------------------

execution_coordinator::~execution_coordinator()
{}

//--------------------------------------

void
execution_coordinator::submit_command(
    command & in_command )
{
    static const text this_method_name[] =
        "submit_command(...)";

    if ( _commands.contains( in_command ) )
    {
        logger::get_singleton().log_error(
            this_class_name, this_method_name,
            "command already registered" );
    }
    else
    {
        _commands.add( in_command );
    }
}

//--------------------------------------

void
execution_coordinator::execute_once()
{
    for ( commands::iterator
          i( _commands.begin() ); i != _commands.end(); )
    {
        command & cmd = *i;
        cmd.execute();
        i = _commands.erase( i );
    }
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
