//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_kill.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_kill.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
command_kill<T>::command_kill( 
    const command_kill<T> & rhs )
  :
    _target( rhs._target )
{}

//--------------------------------------

template <class T>
command_kill<T>::command_kill(
	T & in_target )
  :
    _target( in_target )
{}

//--------------------------------------

// virtual
template <class T>
command *
command_kill<T>::clone() const
{
	return new command_kill<T>( *this );
}

//--------------------------------------

// virtual
template <class T>
void command_kill<T>::execute()
{
    delete &_target;
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
