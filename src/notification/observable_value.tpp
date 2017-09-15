//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_value.hpp> // this interface

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
observable_value<T>::observable_value()
{}

//--------------------------------------

template <class T>
observable_value<T>::observable_value(
    const T & inValue )
  :
    _value( inValue )
{}

//--------------------------------------

template <class T>
observable_value<T>::observable_value( 
    const observable_value<T> & rhs )
  :
    _value( rhs._value )
{}

//--------------------------------------

template <class T>
observable_value<T>::~observable_value()
{}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
