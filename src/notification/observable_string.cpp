//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_string.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_string.hpp>

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

observable_string::observable_string()
{}

//--------------------------------------

observable_string::observable_string(
    const text * in_value )
  :
    _value( in_value )
{} 

//--------------------------------------

observable_string::observable_string(
    const stringex & in_value )
  :
    _value( in_value )
{}

//--------------------------------------

observable_string::observable_string(
    const observable_string & rhs )
  :
    _value( rhs._value )
{}

//--------------------------------------

observable_string::~observable_string()
{}

//--------------------------------------

void
observable_string::set_value(
    const text *        in_value,
    observer_flags *    inout_observer_flags )
{
    if ( in_value == 0 )
    {
        if ( _value.get_size() == 0 )
        {
            return;
        }
        _value.erase();      
    }                
    else
    {
        if ( _value == in_value )
        {                
            return;
        }            
        _value = in_value;
    }
    notify_observers_or_set_flags(
        inout_observer_flags,
        observe_value_changed );
}

//--------------------------------------

void
observable_string::set_value(
    const stringex &    in_value,
    observer_flags *    inout_observer_flags )
{
    if ( _value.compare( in_value ) != 0 )
    {
        _value = in_value;
        notify_observers_or_set_flags(
            inout_observer_flags,
            observe_value_changed );
    }
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
