//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_id_name.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification_id_name.hpp>

//--------------------------------------

namespace lifecycle
{
        
//--------------------------------------
//  public methods
//--------------------------------------

object_identification_id_name::object_identification_id_name(
    id_value        in_id,
    const text *    in_name )
  :
    _id(            in_id ),
    _name(          in_name )
{}

//--------------------------------------

object_identification_id_name::object_identification_id_name(
    const object_identification_id_name & rhs )
  :
    _id(    rhs._id ),
    _name(  rhs._name )
{}

//--------------------------------------

// virtual 
object_identification_id_name::~object_identification_id_name()
{}

//--------------------------------------

// virtual
object_identification_id_name::id_value
object_identification_id_name::get_id() const
{
    return _id;
}

//--------------------------------------

// virtual
const object_identification_id_name::name &
object_identification_id_name::get_name() const
{
    return _name;
}

//--------------------------------------

// virtual
boolean
object_identification_id_name::has_id() const
{
    return true;
}

//--------------------------------------

// virtual
boolean
object_identification_id_name::has_name() const
{
    return true;
}
    
//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
object_identification_id_name::set_id(
    id_value in_id )
{
    _id = in_id;
}

//--------------------------------------

// virtual
void
object_identification_id_name::set_id_name(
    id_value        in_id,
    const name &    in_name )
{
    _id   = in_id;
    _name = in_name;
}

//--------------------------------------

// virtual
void
object_identification_id_name::set_name(
    const name & in_name )
{
    _name = in_name;
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identification_id_name.cpp,v $
// Revision 1.1  2006/12/06 23:39:23  cat
// creation; refactored from portions of old named_object
//
//----------------------------------------------------------

// (end of file)
