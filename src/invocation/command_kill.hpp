#if !defined(BEACH_INVOCATION_COMMAND_KILL)
#define      BEACH_INVOCATION_COMMAND_KILL
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_kill.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// class template for destroying objects indirectly
/**
 *  A kill command is used to cause the deferred
 *  or indirect destruction of some target object.
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
class command_kill
    : public command_abstract
{
public:

    command_kill( const command_kill & );
    command_kill( T & in_target );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    /// assignment operator disabled
    command_kill & operator=( const command_kill & ) { return *this; }

    T &                     _target;

}; // end of class template command_kill

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_KILL
