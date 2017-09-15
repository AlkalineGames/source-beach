#if !defined(BEACH_NOTIFICATION_OBSERVABLE_STRING)
#define      BEACH_NOTIFICATION_OBSERVABLE_STRING
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <notification/observable_imp.hpp>

namespace notification
{
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// string that is observable
/**
 *  @note   design patterns applied:
 *              - Adapter    [GoF]
 *              - observable [GoF]
 */      
class observable_string /// Adapter
    : public virtual observable_imp
{
public:

    enum observer_flag /// bitwise values can be combined
    { 
        observe_value_changed = observable::next_observer_flag,
        next_observer_flag    = observe_value_changed << 1
    };
    observable_string();
    observable_string( const text * );
    observable_string( const stringex & );
    observable_string( const observable_string & rhs );
    virtual ~observable_string();

    bool operator ==( const observable_string & rhs )
    {
        return (_value.compare( rhs._value ) == 0);
    }
    bool operator !=( const observable_string & rhs )
    {
        return (_value.compare( rhs._value ) != 0);
    }
    const stringex & get_value_ref() const { return _value; }
          stringex   get_value()     const { return _value; }

    void set_value( const text *     in_value, observer_flags * = 0 );
    void set_value( const stringex & in_value, observer_flags * = 0 );

    observable_string & operator =( const text * in_value )
    {
        set_value( in_value );
        return *this;
    }
    observable_string & operator =( const stringex & in_value )
    {
        set_value( in_value );
        return *this;
    }
    observable_string & operator =( const observable_string & rhs )
    {
        if ( &rhs != this )
        {
            set_value( rhs._value );
        }
        return *this;
    }

private:

    stringex _value;    
    
}; // end of class observable_string

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_STRING
