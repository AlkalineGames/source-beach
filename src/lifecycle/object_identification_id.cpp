//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_id.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification_id.hpp>

//--------------------------------------

namespace lifecycle
{
        
//--------------------------------------
//  public methods
//--------------------------------------

object_identification_id::object_identification_id(
    id_value in_id )
  :
    _id( in_id )
{}

//--------------------------------------

object_identification_id::object_identification_id(
    const object_identification_id & rhs )
  :
    _id( rhs._id )
{}

//--------------------------------------

// virtual 
object_identification_id::~object_identification_id()
{}

//--------------------------------------

// virtual
object_identification_id::id_value
object_identification_id::get_id() const
{
    return _id;
}

//--------------------------------------

// virtual
boolean
object_identification_id::has_id() const
{
    return true;
}
    
//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
object_identification_id::set_id(
    id_value in_id )
{
    _id = in_id;
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identification_id.cpp,v $
// Revision 1.1  2006/12/06 23:39:23  cat
// creation; refactored from portions of old named_object
//
//----------------------------------------------------------

// (end of file)
