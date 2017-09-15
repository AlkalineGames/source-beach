//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_distributed.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/command_distributed.hpp> // this header

#include <lifecycle/class_catalog.hpp>
#include <lifecycle/logger.hpp>

namespace notification
{
    using namespace atoms;
    using lifecycle::class_catalog;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "command_distributed";

//--------------------------------------
//  public methods
//--------------------------------------

// virtual    
command_distributed::~command_distributed()
{}

//--------------------------------------

command_distributed *
command_distributed::clone() const
{
    static const text this_method_name[]
        = "clone()";

    logger::get_singleton().log_error(
        this_class_name, this_method_name,
        "abstract method must not be called" );
    return 0;
}

//--------------------------------------

std::ostream &
operator <<( 
    std::ostream             & out_stream,
    const command_distributed & in_command )
{
    command_distributed::class_identity cid =
        in_command.getClassId();
    stringex name( class_catalog::get_singleton().find_class_name( cid ) );
    if ( ! name.is_empty() )
    {            
        out_stream << name;
    }
    else
    {
        out_stream << "*unregistered class*";
    }            
    out_stream << ", cid="  << cid
               << ", size=" << in_command.getPacketSize();
    return out_stream;
}

//--------------------------------------
//  protected methods
//--------------------------------------

command_distributed::command_distributed(
    const text * in_name )
  :
    command_packeted( in_name ),
    _channel( 0 ),
    _source( 0 ),
    _destination( 0 )
{}

//--------------------------------------

command_distributed::command_distributed( 
    const command_distributed & rhs )
  :
    command_packeted( rhs ),
    _channel(        rhs._channel ),
    _source(         rhs._source ),
    _destination(    rhs._destination )
{}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
