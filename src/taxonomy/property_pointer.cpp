//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_pointer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_pointer.hpp> // this header

namespace taxonomy
{

//--------------------------------------
//  public methods
//--------------------------------------

property_pointer::property_pointer(
    const stringex &    in_name,
    pointer             in_default_value )
  :
    property_imp( in_name )
{
    _value = in_default_value;
}

//--------------------------------------

// virtual
property_pointer::~property_pointer()
{}

//--------------------------------------

// virtual
pointer
property_pointer::get_pointer(
    whole in_index ) const
{
    return _value;
}

//--------------------------------------

}; // end namespace taxonomy

//----------------------------------------------------------
// (end of file)
