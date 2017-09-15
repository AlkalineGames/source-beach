//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
command_call<T>::command_call( 
    const command_call<T> & rhs )
  :
    _object(            rhs._object ),
    _method(            rhs._method )
{}

//--------------------------------------

template <class T>
command_call<T>::command_call(
    T &                 in_object,
    type_method_pointer in_method )
  :
    _object(            in_object ),
    _method(            in_method )
{}

//--------------------------------------

// virtual
template <class T>
command *
command_call<T>::clone() const
{
	return new command_call<T>( *this );
}

//--------------------------------------

// virtual
template <class T>
void command_call<T>::execute()
{
    (_object.*_method)();
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
