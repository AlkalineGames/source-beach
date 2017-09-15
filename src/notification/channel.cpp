//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       channel.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/channel.hpp> // this header

#include <atoms/stream_string.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog.hpp>
#include <notification/command_distributed.hpp>
#include <notification/packet.hpp>
#include <notification/packet_factory.hpp>
#include <notification/packet_handler.hpp>

namespace notification
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "channel";

//--------------------------------------
//  public methods 
//--------------------------------------

channel::channel(
    Identity inId )
  : 
    _id( inId )
{}

//--------------------------------------

channel::~channel()
{}

//--------------------------------------

String 
channel::getLocationName( 
    Identity ) const
{
    return ""; // intended for override
}

//--------------------------------------

void
channel::receive( 
    const packet & in_packet )
    // anonymous
{
    // source unknown
    receive( in_packet, 0 );
}

//--------------------------------------

void
channel::receive( 
    const packet & in_packet,
    Identity       in_source )
{
    // assume we are the destination
    receive( in_packet, in_source, getId() );
}

//--------------------------------------

void
channel::receive( 
    const packet & in_packet,
    Identity       in_source,
    Identity       in_destination )
{
    static const text this_method_name[]
        = "receive(...)";

    stringex errordesc;
    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( "romp_recv" )
                 || log.is_including( this_class_name );

    packet_handler * handler = 
        packet_factory::acquire_singleton().retrieve_handler( 
            in_packet.getHeader().getTypeId() );
    if ( handler == 0 )
    {            
        errordesc = "handler not registered";
        dolog = true;
    }
    else if ( ! handler->handle_packet( 
                    in_packet, this, in_source, 
                    in_destination ) ) // !!! assume we are the destination
    {
        errordesc  = "not handled by <";
        errordesc += handler->get_name();
        errordesc += '>';
        dolog = true;
    }
    if ( dolog )
    {
        stringex sourcename( getLocationName( in_source ) );
        packet_header::TypeId packettypeid =
            in_packet.getHeader().getTypeId();
        stream_string_o sso;
        sso << "ROMP RECV from "    << sourcename
            << ": packet type id "  << packettypeid;
        if ( ! errordesc.empty() )
        {
            command_distributed::class_identity possibleclassid =
                *reinterpret_cast<const command_distributed::class_identity*>(
                    in_packet.getData());
            stringex possibleclassname =
                lifecycle::class_catalog::get_singleton()
                    .find_class_name( possibleclassid );
            sso
                << ", "                         << errordesc
                << "; possible command class <" << possibleclassid
                << '/'                          << possibleclassname 
                << '>';
            logger::get_singleton().log_error(
                this_class_name, this_method_name, sso.str().c_str() );
        }
        else
        {
            logger::get_singleton().log_trace(
                0, 0, sso.str().c_str() );
        }
    }
}

//--------------------------------------

void
channel::send(
    const packet &,
    boolean )
    // multiplex
{}  // do nothing

//--------------------------------------

void
channel::send( 
    const packet &, 
    Identity,
    boolean )
{}  // do nothing

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
