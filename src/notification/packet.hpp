#if !defined(BEACH_NOTIFICATION_PACKET)
#define      BEACH_NOTIFICATION_PACKET
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <notification/packet_header.hpp>

#include <cstring>

namespace notification
{
    using atoms::byte;
    using atoms::size_type;

//--------------------------------------

class packet
{
friend class packet_factory;
public:

    const packet_header &   getHeader() const { return reinterpret_cast<const packet_header&>(_buffer[0]); }
          packet_header &   getHeader()       { return reinterpret_cast<packet_header&>(_buffer[0]); }
    const byte *            getData() const   { return &(_buffer[getHeader().getHeaderSize()]); }
          byte *            getData()         { return &(_buffer[getHeader().getHeaderSize()]); }
    void                    set_data( 
        size_type               in_offset,
        size_type               in_length,
        const byte *            in_data )
    {
        if ( in_offset < getHeader().getDataSize() )
        {
            size_type remaining =
                getHeader().getDataSize() - in_offset;
            size_type copylength = 
                (remaining < in_length) ? remaining : in_length; 
            byte * targetdata =
                _buffer + getHeader().getHeaderSize() + in_offset;
            memcpy( targetdata, in_data, copylength );
        }
    }
    size_type get_size() const
    { 
        return getHeader().getHeaderSize()
             + getHeader().getDataSize();
    }

private:

    /// life, death, and copy not implemented
    /** (clients must use packet_factory operations) */
    //@{
    packet();
    ~packet();
    packet( const packet & );
    packet & operator =( const packet & );
    //@}

    /// !!! THIS IS A VARIABLE SIZED BUFFER
    byte _buffer[sizeof(packet_header)];

}; // end of class packet

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKET
