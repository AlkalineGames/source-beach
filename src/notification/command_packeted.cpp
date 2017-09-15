//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_packeted.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/command_packeted.hpp> // this header

#include <atoms/memory_dump.hpp>
#include <atoms/stream_string.hpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog.hpp>

#include <memory>

namespace notification
{
    using namespace atoms;
    using lifecycle::logger;
    using lifecycle::object_catalog;
        
//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "command_packeted";
   
//--------------------------------------
//  public methods
//--------------------------------------

// static
command_packeted::priority 
command_packeted::get_class_priority(
    const stringex &    in_key,
    priority            in_modifier )
{
    object_catalog & objcat = object_catalog::get_singleton();
    object_catalog::object value = objcat.resolve( in_key );
    if ( value == 0 )
    {
        value = object_catalog::object(
            int(command_packeted::default_priority+in_modifier));
        objcat.rebind( in_key, value );
    }
    return priority(integer_machine(value));
}

//--------------------------------------

// static
void
command_packeted::set_class_priority(
    const stringex &    in_key,
    priority            in_priority )
{
    object_catalog & objcat = object_catalog::get_singleton();
    objcat.rebind( in_key, object_catalog::object(int(in_priority)) );
}

//--------------------------------------

command_packeted::~command_packeted() // virtual
{}

//--------------------------------------

command_packeted::command_packeted(
    const text *        in_name )
  :
    command_abstract(   in_name )
{}

//--------------------------------------

command_packeted::command_packeted( // protected
    const command_packeted & ) 
{}

//--------------------------------------

boolean
command_packeted::initPacket( 
    const packet & inPacket )
{
    static const text this_method_name[]
        = "initPacket( const packet & )";

    static const text classIdMismatchError[]
        = "class ids do not match.";

    static const text sizeMismatchError[]
        = "packet sizes do not match.";

    const text * error = 0;

    size_type inSize   = inPacket.get_size();
    size_type thisSize = getPacketSize();
    class_identity classId =
        * reinterpret_cast<const class_identity*>(
            inPacket.getData());

    if ( classId != getClassId() )
    {
        error = classIdMismatchError;
    }
    else
    {            
        if ( inSize != thisSize )
        {
            error = sizeMismatchError;
        }
        else
        {
            ::memcpy( &getPacket(), &inPacket, getPacketSize() );
        }                
    }
    if ( error != 0 )
    {          
        stream_string_o sso;
        sso << "Cannot initialize from packet. This class id == " << getClassId()
            << ", this packet size == "      << thisSize
            << "; input packet class id == " << classId
            << ", input packet size == "     << inSize
            << "; " << error << std::endl << std::endl;

        logger & log = logger::get_singleton();
        if ( log.is_including( "romp_recv" ) ) // $$$ WILL THIS SCALE?
        {
    		sso << "Dump of this command_packeted object:" << std::endl;
	    	sso << memory_dump::dump( (char *)(void *)this, thisSize );
		    sso << std::endl;
		   
    		sso << "Dump of input packet object:" << std::endl;
	    	sso << memory_dump::dump( (char *)(void *)&inPacket, inSize );
		    sso << std::endl;
        }
		sso << std::flush;

        log.log_error( this_class_name, this_method_name, sso.str().c_str() );
        return false;
    }
    return true;
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
