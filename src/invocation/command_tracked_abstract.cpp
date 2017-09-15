//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_abstract.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_tracked_abstract.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
command_tracked::~command_tracked() // = 0;
{}

//--------------------------------------

command_tracked_abstract::command_tracked_abstract(
    const text *    in_name,
    const text *    in_file_name,
    whole           in_line_number,
    boolean         in_immediately )
  :                 
    _name(          in_name ),
    _file_name(     in_file_name ),
    _line_number(   in_line_number ),
    _immediately(   in_immediately )
{}

//--------------------------------------

// virtual
const text *
command_tracked_abstract::get_name() const
{
    return _name;
}

//--------------------------------------

// virtual
const text *
command_tracked_abstract::get_file_name() const
{
    return _file_name;
}

//--------------------------------------

// virtual
whole
command_tracked_abstract::get_line_number() const
{
    return _line_number;
}

//--------------------------------------

// virtual
boolean
command_tracked_abstract::immediately() const
{
    return _immediately;
}

//--------------------------------------

// virtual
boolean
command_tracked_abstract::supersedes() const
{
    return false;
}

//--------------------------------------

// virtual
stringex
command_tracked_abstract::make_signature() const
{
    return get_name();
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
