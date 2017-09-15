#if !defined(BEACH_NOTIFICATION_OBSERVABLE_VALUE_COPYCAT)
#define      BEACH_NOTIFICATION_OBSERVABLE_VALUE_COPYCAT
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_value_copycat.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_value.hpp>
#include <notification/observer.hpp>

namespace notification
{

//--------------------------------------

/// class template for a copycat of an observable value
/**
 *  @note   design patterns applied:
 *              - Adapter  [GoF]
 *              - Observer [GoF], [PLoP2], [WF]
 */     
template <class T>
class observable_value_copycat
    : public observable_value<T>,
      public observer
{
public:

    typedef observable_value<T> superclass;

    observable_value_copycat();
    observable_value_copycat( const observable_value_copycat & );
    virtual ~observable_value_copycat();

    void assign( const superclass * ); 

    BEACH_NOTIFICATION_OBSERVER_OVERRIDES_REQUIRED

private:

    const superclass * _original;

}; // end of template class observable_value_copycat

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_VALUE_COPYCAT
