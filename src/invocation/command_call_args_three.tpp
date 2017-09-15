//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_args_three.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call_args_three.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T, class A1, class A2, class A3>
command_call_args_three<T,A1,A2,A3>::command_call_args_three( 
    const command_call_args_three<T,A1,A2,A3> & rhs )
  :
    _object(            rhs._object ),
    _method(            rhs._method ),
    _arg1(              rhs._arg1 ),
    _arg2(              rhs._arg2 ),
    _arg3(              rhs._arg3 )
{}

//--------------------------------------

template <class T, class A1, class A2, class A3>
command_call_args_three<T,A1,A2,A3>::command_call_args_three(
    T &                 in_object,
    type_method_pointer in_method,
    A1                  in_arg1,
    A2                  in_arg2,
    A3                  in_arg3 )
  :
    _object(            in_object ),
    _method(            in_method ),
    _arg1(              in_arg1 ),
    _arg2(              in_arg2 ),
    _arg3(              in_arg3 )
{}

//--------------------------------------

// virtual
template <class T, class A1, class A2, class A3>
command *
command_call_args_three<T,A1,A2,A3>::clone() const
{
	return new command_call_args_three<T,A1,A2,A3>( *this );
}

//--------------------------------------

// virtual
template <class T, class A1, class A2, class A3>
void command_call_args_three<T,A1,A2,A3>::execute()
{
    (_object.*_method)( _arg1, _arg2, _arg3 );
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
