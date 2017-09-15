//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       forwarder.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/forwarder.hpp> // this header

#include <notification/command_distributed.hpp>

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

forwarder::forwarder(
    channel &           in_channel,
    channel_identifier  in_destination )
  : 
    _channel(           in_channel ),
    _destination(       in_destination )
{}

//--------------------------------------

forwarder::~forwarder()
{}

//--------------------------------------

void
forwarder::send( 
    packet &    in_packet,
    boolean     in_be_guaranteed )
{	
    if ( getDestination().getMajor() == 0 )
    {
        _channel.send( // multiplex
            in_packet,
            in_be_guaranteed );
    }
    else
    {       
        _channel.send(
            in_packet,
            getDestination(),
            in_be_guaranteed );
    }
}

//--------------------------------------

void
forwarder::send( 
    command_distributed &   in_command,
    boolean                 in_be_guaranteed )
{	
    if ( getDestination() == 0 )
    {
        _channel.send( // multiplex
            in_command.getPacket(),
            in_be_guaranteed );
    }
    else
    {
        _channel.send(
            in_command.getPacket(),
            getDestination(),
            in_be_guaranteed );
    }
}

//--------------------------------------
//  protected internal methods
//--------------------------------------

void
forwarder::marshal()
{
    // ### FINISH THIS
}

//--------------------------------------

void
forwarder::deliver()
{
    // ### FINISH THIS
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
