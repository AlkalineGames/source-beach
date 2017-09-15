//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_arg_setter_pass.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_call_arg_setter_pass.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T, class A>
command_call_arg_setter_pass<T,A>::command_call_arg_setter_pass( 
    const command_call_arg_setter_pass<T,A> & rhs )
  :
    _object(            rhs._object ),
    _method(            rhs._method ),
    _arg(               rhs._arg )
{}

//--------------------------------------

template <class T, class A>
command_call_arg_setter_pass<T,A>::command_call_arg_setter_pass(
    T &                 in_object,
    type_method_pointer in_method,
    A                   in_arg )
  :
    _object(            in_object ),
    _method(            in_method ),
    _arg(               in_arg )
{}

//--------------------------------------

// virtual
template <class T, class A>
command *
command_call_arg_setter_pass<T,A>::clone() const
{
	return new command_call_arg_setter_pass<T,A>( *this );
}

//--------------------------------------

// virtual
template <class T, class A>
void
command_call_arg_setter_pass<T,A>::execute()
{
    (_object.*_method)( _arg, 0 );
}

//--------------------------------------

// virtual
template <class T, class A>
void
command_call_arg_setter_pass<T,A>::execute(
    void * in_arg )
{
    (_object.*_method)( _arg, in_arg );
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
