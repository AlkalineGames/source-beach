//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_factory.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/packet_factory.hpp> // this header

#include <invocation/command_kill.tpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <notification/packet.hpp>
#include <notification/packet_handler.hpp>

namespace notification
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "packet_factory";

enum { type_id_base = 500 };

static packet_factory * cached_singleton = 0;
    
//--------------------------------------
//  public methods
//--------------------------------------

// static
packet_factory & 
packet_factory::acquire_singleton()
{
    return lifecycle::object_catalog_utility<packet_factory,packet_factory>
            ::acquire_object( this_class_name, &cached_singleton );
}

//--------------------------------------

packet & 
packet_factory::create( 
    const packet_header & in_header )
{
    size_type buffersize = in_header.getHeaderSize()
                        + in_header.getDataSize();
    byte * buffer = new BEACH_ALLOCATION byte[buffersize];
    memcpy( buffer, &in_header, in_header.getHeaderSize() );
    memset( buffer + in_header.getHeaderSize(), 0, in_header.getDataSize() );
    return reinterpret_cast<packet&>(*buffer);
}

//--------------------------------------

void packet_factory::destroy( 
    packet & in_packet )
{
    byte * buffer = reinterpret_cast<byte*>(&in_packet);
    BEACH_DELETE_WITHOUT_DESTRUCT(buffer);
}

//--------------------------------------

packet & 
packet_factory::clone(
    const packet & in_packet )
{
    size_type buffersize = in_packet.getHeader().getHeaderSize()
                        + in_packet.getHeader().getDataSize();
    byte * buffer = new BEACH_ALLOCATION byte[buffersize];
    memcpy( buffer, &in_packet, buffersize );
    return reinterpret_cast<packet&>(*buffer);
}

//--------------------------------------

packet &
packet_factory::compress(
    const packet & in_packet )
{
/*
    ### FINISH THIS
*/
    return clone( in_packet );
}

//--------------------------------------

packet &
packet_factory::decompress(
    const packet & in_packet )
{
/*
    ### FINISH THIS
*/
    return clone( in_packet );
}

//--------------------------------------

packet &
packet_factory::decrypt(
    const packet & in_packet )
{
/*
    ### FINISH THIS
*/
    return clone( in_packet );
}

//--------------------------------------

packet &
packet_factory::encrypt(
    const packet & in_packet )
{
/*
    ### FINISH THIS
*/
    return clone( in_packet );
}

//--------------------------------------

packet &
packet_factory::resize(
    const packet & in_packet,
    size_type       in_new_data_size )
{
    size_type oldbuffersize = in_packet.getHeader().getHeaderSize()
                            + in_packet.getHeader().getDataSize();
    size_type newbuffersize = in_packet.getHeader().getHeaderSize()
                            + in_new_data_size;
    byte * newbuffer = new BEACH_ALLOCATION byte[newbuffersize];
    memcpy( newbuffer, &in_packet, 
           (newbuffersize < oldbuffersize) 
          ? newbuffersize : oldbuffersize );
    if ( newbuffersize > oldbuffersize )
    {
        memset( newbuffer     + oldbuffersize, 0,
                newbuffersize - oldbuffersize );
    }
    packet & newPacket = reinterpret_cast<packet&>(*newbuffer);
    newPacket.getHeader()._dataSize = in_new_data_size;
    return newPacket;
}

//--------------------------------------

void
packet_factory::register_handler( 
    packet_header::TypeId in_type_id, 
    packet_handler *      in_handler )
{
    if ( in_type_id != 0 )
    {
        for ( handler_registrations::iterator
              i(   _handler_registrations.begin() );
              i != _handler_registrations.end(); i++ )
        {
            handler_registration & handreg = *i;        
            if ( handreg._typeId == in_type_id )
            {
                handreg._handler = in_handler;
                return;            
            }
        }
        handler_registration * handreg = new handler_registration;
        handreg->_typeId  = in_type_id;
        handreg->_handler = in_handler;
        _handler_registrations.add( *handreg );
    }
}

//--------------------------------------

packet_handler *
packet_factory::retrieve_handler(
    packet_header::TypeId in_type_id )
{
    if ( in_type_id != 0 )
    {
        for ( handler_registrations::iterator
              i(   _handler_registrations.begin() );
              i != _handler_registrations.end(); i++ )
        {
            handler_registration & handreg = *i;        
            if ( handreg._typeId == in_type_id )
            {
                return handreg._handler;
            }
        }
    }
    return 0;
}

//--------------------------------------
//  private methods
//--------------------------------------

packet_factory::packet_factory()
  :
    _handler_registrations( atoms::destroyer<packet_factory::handler_registration>() )
{}

//--------------------------------------

packet_factory::~packet_factory()
{}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file) 
