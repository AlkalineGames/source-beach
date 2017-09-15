//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_kill_and_zero.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_kill_and_zero.hpp> // this header

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
command_kill_and_zero<T>::command_kill_and_zero( 
    const command_kill_and_zero<T> & rhs )
  :
    _target_pointer( rhs._target_pointer )
{}

//--------------------------------------

template <class T>
command_kill_and_zero<T>::command_kill_and_zero(
	T * & in_target_pointer )
  :
    _target_pointer( in_target_pointer )
{}

//--------------------------------------

// virtual
template <class T>
command *
command_kill_and_zero<T>::clone() const
{
	return new command_kill_and_zero<T>( *this );
}

//--------------------------------------

// virtual
template <class T>
void command_kill_and_zero<T>::execute()
{
    if ( _target_pointer != 0 )
    {            
		delete _target_pointer;
    }        
	_target_pointer = 0;
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
