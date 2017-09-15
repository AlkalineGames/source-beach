//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_static.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call_static.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

command_call_static::command_call_static( 
    const command_call_static & rhs )
  :
    _method( rhs._method )
{}

//--------------------------------------

command_call_static::command_call_static(
    type_method_pointer in_method )
  :
    _method( in_method )
{}

//--------------------------------------

// virtual
command *
command_call_static::clone() const
{
	return new command_call_static( *this );
}

//--------------------------------------

// virtual
void command_call_static::execute()
{
    (*_method)();
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
