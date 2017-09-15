//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_value_copycat.hpp> // this header

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
observable_value_copycat<T>::observable_value_copycat()
  :
    _original( 0 )
{}

//--------------------------------------

template <class T>
observable_value_copycat<T>::observable_value_copycat( 
    const observable_value_copycat<T> & rhs )
  :
    _original( 0 )
{
    assign( rhs._original );
}

//--------------------------------------

// virtual
template <class T>
observable_value_copycat<T>::~observable_value_copycat()
{
    assign( 0 );
}

//--------------------------------------

template <class T>
void
observable_value_copycat<T>::assign(
    const superclass * in_original )
{
    if (_original != 0)
        _original->detach_observer( *this );
    _original = in_original;
    if (_original != 0) {
        _original->attach_observer( *this );
        this->set_value( _original->get_value() );
    }
}

//--------------------------------------

// virtual
template <class T>
stringex
observable_value_copycat<T>::make_name_observer() const
{
    return "observable_value_copycat<T>"; 
}

//--------------------------------------

// virtual
template <class T>
void
observable_value_copycat<T>::update_observer(
    const observable &  in_observable,
    const void *        in_affected_object,
    observer_flags      in_flags )
{
    if (&in_observable == _original) {
        if (in_flags & observable::observe_destructing)
            assign( 0 );
        else if (in_flags & superclass::observe_value_changed)
            this->set_value( _original->get_value() );
    }
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
