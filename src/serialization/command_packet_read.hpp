#if !defined(BEACH_SERIALIZATION_COMMAND_PACKET_READ)
#define      BEACH_SERIALIZATION_COMMAND_PACKET_READ
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

#include <atoms/enumerations.hpp>
#include <invocation/command_abstract.hpp>
#include <notification/channel_identifier.hpp>

namespace notification 
{
    class channel;
    class packet;
};

namespace serialization
{
    class reader_packeted;
    using atoms::ownership;
    using invocation::command;
    using invocation::command_abstract;
    using notification::channel;
    using notification::channel_identifier;
    using notification::packet;

//--------------------------------------

/// command to read a packet

class command_packet_read
    : public command_abstract
{
public:

    command_packet_read( const command_packet_read & );
    command_packet_read(
        reader_packeted &,
        ownership           in_packet_ownerhip,
        const packet &,
        channel *,
        channel_identifier  in_source,
        channel_identifier  in_destination );

    virtual ~command_packet_read();

    /// @name command overrides
    //@{
    virtual command *   clone() const; ///< prototype method
    virtual void        execute();
    //@}

private:
                    
	reader_packeted &   _reader_packeted;
    ownership           _packet_ownership;
    const packet &      _packet;
    channel *           _channel;
    channel_identifier  _source;
    channel_identifier  _destination;

}; // end of class command_packet_read

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_COMMAND_PACKET_READ
