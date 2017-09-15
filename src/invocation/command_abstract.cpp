//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
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

#include <invocation/command_abstract.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
command::~command() // = 0
{}

//--------------------------------------

// virtual
command_abstract::~command_abstract()
{}

//--------------------------------------

// virtual
command *
command_abstract::clone() const
{
    // !!! superclass is abstract; this method should never be called.
    return 0;
}

//--------------------------------------

// virtual
void
command_abstract::execute(
    void * )
{
    execute(); // forget about the args
}

//--------------------------------------

// virtual
void
command_abstract::execute(
    command_arguments & )
{
    execute(); // forget about the args
}

//--------------------------------------

// virtual
const text *
command_abstract::get_name() const
{
    if ( _name_text == 0 )
    {
        _name_text = _name.c_str();
    }
    return _name_text;
}

//--------------------------------------

// virtual
void
command_abstract::set_name(
    const text * in_name )
{
    _name = in_name;
    _name_text = (in_name == 0 ? 0 : _name.c_str());
}

//--------------------------------------
//  protected methods
//--------------------------------------

command_abstract::command_abstract(
    const text * in_name )
  :
    _name_text( 0 )
{
    if ( in_name != 0 )
    {
        set_name( in_name );
    }
}

//--------------------------------------

command_abstract::command_abstract(
    const command_abstract & )
{}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
