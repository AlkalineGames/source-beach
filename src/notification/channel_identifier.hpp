#if !defined(BEACH_NOTIFICATION_CHANNEL_IDENTIFIER)
#define      BEACH_NOTIFICATION_CHANNEL_IDENTIFIER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       channel_identifier.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>

namespace notification
{

//--------------------------------------

class channel_identifier
{
public:

    typedef atoms::whole32 Major;
    typedef atoms::whole16 Minor;

    BEACH_ALLOCATION_OPERATORS

    channel_identifier( atoms::no_init_type ) {}

    channel_identifier( Major inMajor = 0, Minor inMinor = 0 )
      : _major( inMajor ), _minor( inMinor ) {}

    channel_identifier( const channel_identifier & rhs )
      : _major( rhs._major ), _minor( rhs._minor ) {}

    channel_identifier & operator =( const channel_identifier & rhs )
    {   _major = rhs._major; _minor = rhs._minor; return *this; }

    channel_identifier & operator =( Major inMajor )
    {   _major = inMajor; _minor = 0; return *this; }

    bool operator ==( const channel_identifier & rhs ) const
    {   return (_major == rhs._major) && (_minor == rhs._minor); }

    bool operator !=( const channel_identifier & rhs ) const
    {   return ! operator ==( rhs ); }        

    Major getMajor() const          { return _major; }
    Minor getMinor() const          { return _minor; }

    void  setMajor( Major inMajor ) { _major = inMajor; }
    void  setMinor( Minor inMinor ) { _minor = inMinor; }
    void  set( Major inMajor, Minor inMinor )
    {   _major = inMajor; _minor = inMinor; }

private:

    Major _major;
    Minor _minor;

}; // end of class channel_identifier

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_CHANNEL_IDENTIFIER
