//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_distributed_group.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/command_distributed_group.hpp> // this header

#include <atoms/destroyer.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stream_string.hpp>
#include <lifecycle/logger.hpp>
#include <notification/command_distributed.hpp>

#include <iomanip>

namespace notification
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text name_this_class[]
    = "command_distributed_group";
    
//--------------------------------------
//  internal methods
//--------------------------------------

static
void
log_command(
    const command_distributed & in_command,
    const text *                in_name_method,
    logger &                    in_logger )
{
    stream_string_o sso1;
    sso1 << "command address <"
         << std::hex << &in_command << '>';
    stringex logmsg( sso1.str() );
    stream_string_o sso2;
    sso2 << " id <" << in_command.getClassId() << '>';
    logmsg += sso2.str();
    const text * name = in_command.get_name();
    if ( name != 0 )
    {
        logmsg += " name <";
        logmsg += name;
        logmsg += '>';   
    }
    in_logger.log_trace( name_this_class, in_name_method, logmsg );
}

//--------------------------------------
//  public methods
//--------------------------------------

command_distributed_group::command_distributed_group()
  :
    command_distributed_group_collection(
        destroyer<command_distributed>() )
{}

//--------------------------------------

command_distributed_group::~command_distributed_group()
{
    static const text name_this_method[]
        = "~command_distributed_group(...)";
    
    ///< !!! only needed for debugging
    logger & log = logger::get_singleton();
    if ( ! log.is_including( name_this_class ) )
    {
        return; // superclass destructor will delete elements
    };
    for ( iterator iter( begin() ); iter != end(); )
    {
        log_command( *iter, name_this_method, log );
        iter = erase( iter );
    }
}

//--------------------------------------

void
command_distributed_group::add(
    command_distributed &   in_command,
    const text *            in_name_prefix )
{
    static const text name_this_method[]
        = "add(...)";
    
    if ( in_name_prefix != 0 )
    {
        stringex name( in_name_prefix );
        name += in_command.get_name();
        in_command.set_name( name );
    }
    command_distributed_group_collection::add( in_command );
    logger & log = logger::get_singleton();
    if ( log.is_including( name_this_class ) )
    {
        log_command( in_command, name_this_method, log );
    }
}

//--------------------------------------

command_distributed * 
command_distributed_group::spawn( 
    const packet &      in_packet,
    channel *           in_channel,
    channel_identifier  in_source,
    channel_identifier  in_destination )
{
    static const text name_this_method[]
        = "spawn(...)";
    
    // cast packet data into class id
    command_distributed::class_identity classId =
        * reinterpret_cast<const command_distributed::class_identity*>(
            in_packet.getData());
    
    // search for matching command class
	command_distributed::class_identity cid; // debugging aid
    for ( const_iterator i( begin() ); i != end(); i++ )
    {
        const command_distributed & dc = *i;
		cid = dc.getClassId(); 
        if ( cid == classId )
        {
            command_distributed * cdc = dc.clone();
            boolean success = cdc->initPacket( in_packet );
            if ( success )
            {
                cdc->_channel     = in_channel;
                cdc->_source      = in_source;
                cdc->_destination = in_destination;
                return cdc;
            }                
            // generate detailed error info
            stream_string_o sso;
            sso << "initPacket(...) failed for packet from source "
                << (in_channel == 0 ? "(unknown)" : in_channel->getLocationName( in_source ))
                << " to destination "
                << (in_channel == 0 ? "(unknown)" : in_channel->getLocationName( in_destination ))
                << std::flush;
            logger::get_singleton().log_error(
                name_this_class, name_this_method, sso.str().c_str() );
        }
    }
    return 0; // command not found
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
