//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_arg_pass.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call_arg_pass.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
command_call_arg_pass<T>::command_call_arg_pass( 
    const command_call_arg_pass<T> & rhs )
  :
    _object(            rhs._object ),
    _method(            rhs._method )
{}

//--------------------------------------

template <class T>
command_call_arg_pass<T>::command_call_arg_pass(
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
command_call_arg_pass<T>::clone() const
{
	return new command_call_arg_pass<T>( *this );
}

//--------------------------------------

// virtual
template <class T>
void
command_call_arg_pass<T>::execute()
{
    (_object.*_method)( 0 );
}

//--------------------------------------

// virtual
template <class T>
void
command_call_arg_pass<T>::execute(
    void * in_arg )
{
    (_object.*_method)( in_arg );
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
