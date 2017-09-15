//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_args_two.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call_args_two.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T, class A1, class A2>
command_call_args_two<T,A1,A2>::command_call_args_two( 
    const command_call_args_two<T,A1,A2> & rhs )
  :
    _object(            rhs._object ),
    _method(            rhs._method ),
    _arg1(              rhs._arg1 ),
    _arg2(              rhs._arg2 )
{}

//--------------------------------------

template <class T, class A1, class A2>
command_call_args_two<T,A1,A2>::command_call_args_two(
    T &                 in_object,
    type_method_pointer in_method,
    A1                  in_arg1,
    A2                  in_arg2 )
  :
    _object(            in_object ),
    _method(            in_method ),
    _arg1(              in_arg1 ),
    _arg2(              in_arg2 )
{}

//--------------------------------------

// virtual
template <class T, class A1, class A2>
command *
command_call_args_two<T,A1,A2>::clone() const
{
	return new command_call_args_two<T,A1,A2>( *this );
}

//--------------------------------------

// virtual
template <class T, class A1, class A2>
void command_call_args_two<T,A1,A2>::execute()
{
    (_object.*_method)( _arg1, _arg2 );
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
