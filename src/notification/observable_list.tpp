//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
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

#include <notification/observable_list.hpp> // this header

#include <atoms/destroyer.hpp>

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
observable_list<T>::observable_list()
{}

//--------------------------------------

template <class T>
observable_list<T>::observable_list(
    ownership )
  :
    _list( atoms::destroyer<T>() )
{}

//--------------------------------------

// virtual
template <class T>
observable_list<T>::~observable_list()
{}

//--------------------------------------

// virtual
template <class T>
void observable_list<T>::add(
    element & in_element )
{
    _list.add( in_element );
    notify_observers( observe_element_added, &in_element );
}

//--------------------------------------

// virtual
template <class T>
void
observable_list<T>::change(
    element &       in_element,
    const element & in_new_value )
{
    if ( _list.contains( in_element ) )
    {
        in_element = in_new_value;
        notify_observers( observe_element_changed, &in_element );
    }
}

//--------------------------------------

// virtual
template <class T>
void 
observable_list<T>::remove(
    element & in_element )
{
    notify_observers( observe_element_removing, &in_element );
    _list.erase_first( in_element );
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
