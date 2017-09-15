//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_packet_read.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/command_packet_read.hpp> // this header

#include <serialization/reader_packeted.hpp>

namespace serialization
{

//--------------------------------------
//  public methods
//--------------------------------------

command_packet_read::command_packet_read(
    const command_packet_read & rhs )
  :
    _reader_packeted(   rhs._reader_packeted    ),
    _packet_ownership(  rhs._packet_ownership   ),
    _packet(            rhs._packet             ),
    _channel(           rhs._channel            ),
    _source(            rhs._source             ),
    _destination(       rhs._destination        )
{}

//--------------------------------------

command_packet_read::command_packet_read( 
    reader_packeted &   in_reader_packeted,
    ownership           in_packet_ownership,
    const packet &      in_packet,
    channel *           in_channel,
    channel_identifier  in_source,
    channel_identifier  in_destination )
  :
    _reader_packeted(   in_reader_packeted  ),
    _packet_ownership(  in_packet_ownership ),
    _packet(            in_packet           ),
    _channel(           in_channel          ),
    _source(            in_source           ),
    _destination(       in_destination      )
{}

//--------------------------------------

// virtual
command_packet_read::~command_packet_read()
{}

//--------------------------------------

// virtual
command * 
command_packet_read::clone() const
{
    return (command *)(new command_packet_read( *this ));
}
   
//--------------------------------------

// virtual
void
command_packet_read::execute()
{
    _reader_packeted.read_packet(
        _packet_ownership, _packet,
        _channel, _source, _destination );
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
