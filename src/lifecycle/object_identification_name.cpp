//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_name.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification_name.hpp>

//--------------------------------------

namespace lifecycle
{
        
//--------------------------------------
//  public methods
//--------------------------------------

object_identification_name::object_identification_name(
    const text * in_name )
  :
    _name( in_name )
{}

//--------------------------------------

object_identification_name::object_identification_name(
    const object_identification_name & rhs )
  :
    _name( rhs._name )
{}

//--------------------------------------

// virtual 
object_identification_name::~object_identification_name()
{}

//--------------------------------------

// virtual
const object_identification_name::name &
object_identification_name::get_name() const
{
    return _name;
}

//--------------------------------------

// virtual
boolean
object_identification_name::has_name() const
{
    return true;
}
    
//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
object_identification_name::set_name(
    const name & in_name )
{
    _name = in_name;
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identification_name.cpp,v $
// Revision 1.1  2006/12/06 23:39:23  cat
// creation; refactored from portions of old named_object
//
//----------------------------------------------------------

// (end of file)
