//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_command.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/text_command.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
text_command::~text_command()
{}

//--------------------------------------
//  protected methods
//--------------------------------------

text_command::text_command(
    const text * in_name,
    const text * in_help )
  :
    _name( in_name ),
    _help( in_help )
{}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
