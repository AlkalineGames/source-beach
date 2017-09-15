//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serialized_object.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serialized_object.hpp> // this header

namespace serialization
{

//--------------------------------------
//  protected methods
//--------------------------------------

serialized_object::serialized_object(
    id_value        in_id,
    const text *    in_name )
  :
    _identification( in_id, in_name )
{}

//--------------------------------------

// virtual
serialized_object::~serialized_object()
{}

//--------------------------------------

// virtual
object_identification &
serialized_object::get_identification_nc()
{
    return _identification;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
