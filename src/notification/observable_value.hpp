#if !defined(BEACH_NOTIFICATION_OBSERVABLE_VALUE)
#define      BEACH_NOTIFICATION_OBSERVABLE_VALUE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_value.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_imp.hpp>

namespace notification
{

//--------------------------------------

/// class template adapter for values that notify observers
/**
 *  Specify the class arg T without the &
 *
 *  @note       design patterns applied:
 *                  - Adapter  [GoF]
 *                  - Observer [GoF], [PLoP2], [cat]
 *
 */     
template <class T>
class observable_value
    : public virtual observable_imp
{
public:

    typedef T value;
    enum observer_flag /// bitwise values can be combined
    { 
        observe_value_changed = observable::next_observer_flag,
        next_observer_flag    = observe_value_changed << 1
    };
    
    observable_value();
    observable_value( const value & );
    observable_value( const observable_value & rhs );
    virtual ~observable_value();

    bool operator ==( const observable_value & rhs )
    {
        return (_value == rhs._value);
    }
    bool operator !=( const observable_value & rhs )
    {
        return (_value != rhs._value);
    }

    const value & get_value_ref() const { return _value; }

    value get_value() const { return _value; }

    void set_value( const value & in_value )
    {
        if ( _value != in_value )
        {
            _value = in_value;
            notify_observers( observe_value_changed );
        }
    }
    observable_value & operator =(
        value in_value ) ///< temp copy
    {
        set_value( in_value );
        return *this;
    }
    observable_value & operator =(
        const observable_value & rhs )
    {
        if ( &rhs != this )
        {
            set_value( rhs._value );
        }
        return *this;
    }

private:

    value _value;

}; // end of template class observable_value

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_VALUE
