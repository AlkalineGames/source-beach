#if !defined(BEACH_INVOCATION_COMMAND_KILL_AND_ZERO)
#define      BEACH_INVOCATION_COMMAND_KILL_AND_ZERO
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_kill_and_zero.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// class template for destroying objects indirectly and zeroing the pointer
/**
 *  A kill command is used to cause the deferred
 *  or indirect destruction of some target object.
 *
 *  This kill command is constructed with a reference to a
 *  pointer to the target object so that the kill command
 *  resets the pointer to 0 after destroying the target.
 *
 *  A kill command is useful when some target object 
 *  needs to be destroyed outside of its context of
 *  execution (i.e. not while executing its methods).
 *
 *  For example, an object that has fulfilled its
 *  purpose notifies its creator that it is ready to
 *  be destroyed using the Observer design pattern.
 *  The creator-observer cannot destroy the object
 *  when it receives the notification because it
 *  is still executing within the context of the
 *  subject's notify() method. So instead, the 
 *  creator-observer creates a kill command that
 *  it can execute later after returning control
 *  to the subject that notified it.
 *
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T>
class command_kill_and_zero
    : public command_abstract
{
public:

    command_kill_and_zero( const command_kill_and_zero & );
    command_kill_and_zero( T * & in_target_pointer );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    /// assignment operator disabled
    command_kill_and_zero & operator=( const command_kill_and_zero & ) { return *this; }

    T * &                   _target_pointer;

}; // end of class template command_kill_and_zero

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_KILL_AND_ZERO
