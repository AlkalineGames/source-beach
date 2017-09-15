//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       reader_packeted.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/reader_packeted.hpp> // this header

#include <atoms/stream_string.hpp>
#include <atoms/stringex_conversion.hpp>
#include <lifecycle/logger.hpp>
#include <notification/channel.hpp>
#include <notification/packet.hpp>
#include <notification/packet_factory.hpp>
#include <serialization/context_reading.hpp>
#include <serialization/selector.hpp>
#include <serialization/serializable.hpp>
#include <serialization/serializable_logging.hpp>
#include <serialization/serializable_manager.hpp>
#include <serialization/serializable_spec.hpp>
#include <serialization/text_stream_writer.hpp>

namespace serialization
{
    using namespace atoms;
    using lifecycle::logger;
    using notification::channel_identifier;
    using notification::packet_factory;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "reader_packeted";

//--------------------------------------
//  public methods
//--------------------------------------

reader_packeted::reader_packeted()
  :
    _packet_position(   0 ),
    _packet(            0 )
{}

//--------------------------------------

reader_packeted::reader_packeted(
    reader & in_reader )
  :
    reader(             in_reader ),
    _packet_position(   0 ),
    _packet(            0 )
{}

//--------------------------------------

// virtual
reader_packeted::~reader_packeted()
{}

//--------------------------------------

// virtual
boolean
reader_packeted::read_boolean(
    const selector *    in_selector,
    const text *        in_label,
    boolean &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(whole8) ) )
    {
        return false;
    }
    // read binary data
    const whole8 & value = reinterpret_cast<const whole8&>(
        _packet->getData()[_packet_position]);
    out_value = (value != 0);
    _packet_position += sizeof(whole8);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "boolean",
            stringex_conversion::from( out_value,
                false, true ), // not as number, as letter
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_enum(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_names[],
    whole               in_name_count,
    integer &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(integer) ) )
    {
        return false;
    }
    // read binary data
    const integer & value = reinterpret_cast<const integer&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(integer);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "enum",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_integer(
    const selector *    in_selector,
    const text *        in_label,
    integer &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(integer) ) )
    {
        return false;
    }
    // read binary data
    const integer & value = reinterpret_cast<const integer&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(integer);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "integer",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_integer32(
    const selector *    in_selector,
    const text *        in_label,
    integer32 &         out_value )
{
    if ( ! read_selector( in_selector, sizeof(integer32) ) )
    {
        return false;
    }
    // read binary data
    const integer32 & value = reinterpret_cast<const integer32&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(integer32);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "integer32",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_ordered_real(
    const selector *    in_selector,
    const text *        in_label,
    real                out_values[],
    whole               in_count,
    whole               in_position )
{
    if ( ! read_selector( in_selector, sizeof(real)*in_count ) )
    {
        return false;
    }
    for ( whole i = 0; i < in_count; i++ )
    {
        // read binary data
        const real & value = reinterpret_cast<const real&>(
            _packet->getData()[_packet_position]);
        out_values[i] = value;
        _packet_position += sizeof(real);
    }
    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( this_class_name );
    if ( dolog )
    {
        stream_string_o sso;
        serializable_logging::output_to_stream_selector_label_type(
            in_selector, in_label, "real",
            _packet_position, in_count, sso ); 
        for ( whole i = 0; i < in_count; i++ )
        {
            if ( i > 0 )
            {
                sso << ',';
            }
            sso << out_values[i];
        }
        sso << ')';
        log.log_trace( 0, 0, sso.str().c_str() );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_ordered_whole(
    const selector *    in_selector,
    const text *        in_label,
    whole               out_values[],
    whole               in_count )
{
    if ( ! read_selector( in_selector, sizeof(whole)*in_count ) )
    {
        return false;
    }
    for ( whole i = 0; i < in_count; i++ )
    {
        // read binary data
        const whole & value = reinterpret_cast<const whole&>(
            _packet->getData()[_packet_position]);
        out_values[i] = value;
        _packet_position += sizeof(whole);
    }
    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( this_class_name );
    if ( dolog )
    {
        stream_string_o sso;
        serializable_logging::output_to_stream_selector_label_type(
            in_selector, in_label, "whole",
            _packet_position, in_count, sso ); 
        for ( whole i = 0; i < in_count; i++ )
        {
            if ( i > 0 )
            {
                sso << ',';
            }
            sso << out_values[i];
        }
        sso << ')';
        log.log_trace( 0, 0, sso.str().c_str() );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_real(
    const selector *    in_selector,
    const text *        in_label,
    real &              out_value,
    whole            // in_position_count not used
    )
{
    if ( ! read_selector( in_selector, sizeof(real) ) )
    {
        return false;
    }
    // read binary data
    const real & value = reinterpret_cast<const real&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(real);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "real",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_string(
    const selector *    in_selector,
    const text *        in_label,
    stringex &          out_string,
    whole            // in_position_count not used
    )
{
    if ( ! read_selector( in_selector, sizeof(whole16)+1 ) )
    {
        return false;
    }
    // read text length as a whole16
    const whole16 & text_length = reinterpret_cast<const whole16&>(
        _packet->getData()[_packet_position]);
    _packet_position += sizeof(whole16);
    //out_string.fill( (size_type)0, text_length,
    //                  (value_type)0 );
    //text * out_text = out_string.get_text();

    // read up to text length or end of packet
    for ( whole16 i = 0;
             (i < text_length)
          && (_packet_position < _packet->getHeader().getDataSize());
          i++ )
    {
        out_string += _packet->getData()[_packet_position++];
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "string", out_string,
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_text(
    const selector *    in_selector,
    const text *        in_label,
    text *              out_text,
    size_type           out_text_length )
{
    if ( ! read_selector( in_selector, sizeof(whole16)+1 ) )
    {
        return false;
    }
    // read text length as a whole16
    const whole16 & text_length = reinterpret_cast<const whole16&>(
        _packet->getData()[_packet_position]);
    _packet_position += sizeof(whole16);
    out_text_length = text_length;

    // read up to text length or end of packet
    for ( whole16 i = 0;
             (i < text_length)
          && (_packet_position < _packet->getHeader().getDataSize());
          i++ )
    {
        out_text[i] = _packet->getData()[_packet_position++];
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "text", out_text,
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_whole(
    const selector *    in_selector,
    const text *        in_label,
    whole &             out_value )
{
    if ( ! read_selector( in_selector, sizeof(whole) ) )
    {
        return false;
    }
    // read binary data
    const whole & value = reinterpret_cast<const whole&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(whole);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_whole16(
    const selector *    in_selector,
    const text *        in_label,
    whole16 &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(whole16) ) )
    {
        return false;
    }
    // read binary data
    const whole16 & value = reinterpret_cast<const whole16&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(whole16);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole16",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_whole32(
    const selector *    in_selector,
    const text *        in_label,
    whole32 &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(whole32) ) )
    {
        return false;
    }
    // read binary data
    const whole32 & value = reinterpret_cast<const whole32&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(whole32);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole32",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_whole64(
    const selector *    in_selector,
    const text *        in_label,
    whole64 &           out_value )
{
    if ( ! read_selector( in_selector, sizeof(whole64) ) )
    {
        return false;
    }
    // read binary data
    const whole64 & value = reinterpret_cast<const whole64&>(
        _packet->getData()[_packet_position]);
    out_value = value;
    _packet_position += sizeof(whole64);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole64",
            stringex_conversion::from( out_value ),
            _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_object(
    const selector *    in_selector,
    const text *        in_label,
    serializable * &    out_object,
    whole            // in_position_count not used
    )
{
    if ( ! read_selector( in_selector, sizeof(whole) ) )
    {
        return false;
    }
    context ctx;
    out_object = serializable_manager::acquire_singleton().acquire(
        ctx, *this, 0, false ); // don't log error

    boolean succeeded = true;
    if ( out_object == 0 )
    {
        // check for null reference
        whole32 ref;
        if (   (! read_whole32( 0, in_label, ref ))
            || (ref != 0) )
        {
            succeeded = false;
        }
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        stringex value;
        if ( out_object == 0 )
        {
            value = "null";
        }
        else
        {
            serializable_spec spec;
            out_object->populate_spec( spec );
            value = spec.to_string();
        }
        serializable_logging::log_trace_element(
            in_selector, in_label, "^object", value,
            _packet_position );
    }
    return succeeded;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_root(
    serializable * &        out_root,
    serializable_source *   in_source )
{
    context ctx;
    read_root( ctx, out_root, in_source );
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_root(
    context &               in_context,
    serializable * &        out_root,
    serializable_source *   in_source )
{
    static const text this_method_name[]
        = "read_root(...)";

    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( this_class_name );
    if ( dolog )
    {
        log.log_trace( this_class_name, this_method_name, "START" );
    }
    out_root = serializable_manager::acquire_singleton().acquire(
        in_context, *this, this );
    if ( (out_root != 0) && (in_source != 0) )
    {
        out_root->set_serializable_source( in_source );
    }
    if ( dolog )
    {
        log.log_trace( this_class_name, this_method_name, "FINISH" );
    }
    return ( out_root != 0 );
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_all(
    serializable & )
{
//  ### FINISH THIS
    return false;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_spec(
    const selector *    in_selector,
    const text *        in_label,
    serializable_spec & out_spec )
{
    if ( ! read_selector( in_selector, 0 ) )
    {
        return false;
    }
    if ( ! read_whole16( 0, 0, out_spec._class_id ) )
    {
        return false;
    }
    if ( ! read_whole64( 0, 0, out_spec._object_id ) )
    {
        return false;
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "^spec",
            out_spec.to_string(), _packet_position );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_state(
    serializable & )
{
//  ### FINISH THIS
    return false;
}

//--------------------------------------

// virtual
boolean
reader_packeted::read_value(
    const selector *    in_selector,
    const text *        in_label,
    serializable &      out_value )
{
    if ( ! read_selector( in_selector, 1 ) )
    {
        return false;
    }
    out_value.read_from( *this );
    return true;
}

//--------------------------------------

// virtual
boolean
reader_packeted::has_field(
    const selector * in_selector,
    const text * ) // in_label not used
{
    if (   (in_selector == 0)
        || (   (_packet != 0                              )
            && (   (_packet_position+in_selector->get_size())
                >=  _packet->getHeader().getDataSize()    )))
    {
        return false;
    }
    //
    //  ### NOT YET HANDLING MULTIPLE PACKETS
    //
    for ( whole i = 0; i < in_selector->get_size(); i++ )
    {
        if (   _packet->getData()[_packet_position+i]
            != (*in_selector)[i] )
        {
            return false;
        }
    }
    return true;
}

//--------------------------------------

void
reader_packeted::read_packet(
    ownership           in_packet_ownership,
    const packet &      in_packet,
    channel *           in_channel,
    channel_identifier   in_source,
    channel_identifier   in_destination )
{
    static const text this_method_name[]
        = "read_packet(...)";

    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( "romp_recv" )
                 || log.is_including( this_class_name );
    if ( dolog ) 
    {
        stream_string_o sso;
        sso << "ROMP RECV from " << in_channel->getLocationName( in_source )
            << ", by receiving reader, packet header={"
            << in_packet.getHeader()
            << "}";
        log.log_trace( 0, 0, sso.str().c_str() );
    }            
//  ### JUST DO A SINGLE PACKET RIGHT NOW

    if ( in_packet.getHeader().getCount() == 1 )
    {
        _packet = &in_packet;
        _packet_position = 0;
        serializable * ser;
        context_reading ctxreading;
        channel_identifier senderid( in_packet.getHeader().get_sender_id() );
        ctxreading.set_sender_id( &senderid ); // @@@ WHY A POINTER INSTEAD OF VALUE?
        context ctx( ctxreading );
        if ( ! read_root( ctx, ser ) )
        {
            stream_string_o sso;
            sso << "ROMP: failed to serialize packet from "
                << in_channel->getLocationName( in_source )
                << ", header={"
                << in_packet.getHeader()
                << "}";
            logger::get_singleton().log_error(
                this_class_name, this_method_name,
                sso.str().c_str() );
        }
        if ( dolog && (ser != 0) )
        {
            stringex logmsg( "Read root of:\n" );
            logmsg += text_stream_writer::write_to_string( *ser, 0 );
            logmsg += '.';
            log.log_trace( this_class_name, this_method_name, logmsg );
        }
    }
    if ( in_packet_ownership = own_it )
    {
        packet_factory::acquire_singleton().destroy(
            const_cast<packet&>(in_packet) ); // @@@ CONST CAST
    }
}

//--------------------------------------
//  private methods
//--------------------------------------

boolean
reader_packeted::read_selector(
    const selector *    in_selector,
    size_type           in_data_size )
{
    // check for enough space in packet
    if ( in_selector != 0 )
    {
        in_data_size += in_selector->get_size();
    }
    if (   (_packet == 0)
        || (  (_packet_position+in_data_size)
            > _packet->getHeader().getDataSize()) )
    {
        // ### NOT YET HANDLING MULTIPLE PACKETS
        return false;
    }
    // read tag if non-zero, fail if it doesn't match
    if ( in_selector != 0 )
    {
        whole selector_size = in_selector->get_size();
        const byte * buffer = _packet->getData();
        buffer += _packet_position;
        for ( whole i = 0; i < selector_size; i++ )
        {
            byte buffbyte = buffer[i];
            byte selbyte  = (*in_selector)[i];
            if ( buffbyte != selbyte )
            {
                return false;
            }
        }
        _packet_position += in_selector->get_size();
    }
    return true;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
