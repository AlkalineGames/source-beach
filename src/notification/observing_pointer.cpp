//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observing_pointer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observing_pointer.hpp> // this header

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

observing_pointer::observing_pointer(
    const observable * ptr )
  :
    _subject( ptr )
{
    if (_subject != 0)
        _subject->attach_observer( *this );
}

//--------------------------------------

observing_pointer::observing_pointer( 
    const observing_pointer & rhs )
  :
    _subject( rhs._subject )
{
    if (_subject != 0)
        _subject->attach_observer( *this );
}

//--------------------------------------

// virtual
observing_pointer::~observing_pointer()
{
    if (_subject != 0)
        _subject->detach_observer( *this );
}

//--------------------------------------

void
observing_pointer::set(
    const observable * ptr )
{
    if (_subject == ptr )
        return;
    if (_subject != 0)
        _subject->detach_observer( *this );
    _subject = ptr;
    if (_subject != 0)
        _subject->attach_observer( *this );
}

//--------------------------------------

// virtual
stringex
observing_pointer::make_name_observer() const
{
    return "observing_pointer";
}

//--------------------------------------

// virtual
void
observing_pointer::update_observer(
    const observable &  in_observable,
    const void *        in_affected_object,
    observer_flags      in_flags )
{
    if (&in_observable == _subject)
        if (in_flags & observable::observe_destructing)
            set( 0 );
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
