#if !defined(BEACH_NOTIFICATION_FORWARDER)
#define      BEACH_NOTIFICATION_FORWARDER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       forwarder.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/stringex.hpp>
#include <notification/channel.hpp>

namespace notification
{
    class command_distributed;
    using atoms::stringex;

//--------------------------------------

class forwarder
{
public:

    BEACH_ALLOCATION_OPERATORS

    forwarder( 
        channel &,
        channel_identifier in_destination ); ///< 0 for multiplex

    virtual ~forwarder();

    const channel & get_channel() const { return _channel; }

    channel_identifier getDestination() const ///< 0 for multiplex
    {   return _destination; }

    void setDestination( channel_identifier in_destination )
    {   _destination = in_destination; }

    stringex getDestinationName()
    {   return _channel.getLocationName( _destination ); }

    /// @name communications (delegated to channel) 
    //@{
    virtual void send(
        packet &,
        boolean in_be_guaranteed = false );

    virtual void send(
        command_distributed &,
        boolean in_be_guaranteed = false );
    //@}

protected:

    void marshal();
    void deliver();

private:
    
    /// @name copy operations not implemented
    //@{
    forwarder(              const forwarder & );
    forwarder & operator =( const forwarder & );
    //@}

    channel &           _channel;
    channel_identifier  _destination;

}; // end of class forwarder

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_FORWARDER
