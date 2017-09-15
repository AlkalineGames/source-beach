//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       writer_forwarded.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/writer_forwarded.hpp> // this header

#include <atoms/stream_string.hpp>
#include <atoms/stringex_conversion.hpp>
#include <lifecycle/logger.hpp>
#include <notification/forwarder.hpp>
#include <notification/packet.hpp>
#include <notification/packet_factory.hpp>
#include <serialization/packet_type_serialization.hpp>
#include <serialization/selector.hpp>
#include <serialization/serializable.hpp>
#include <serialization/serializable_logging.hpp>
#include <serialization/serializable_spec.hpp>

#include <typeinfo>

namespace serialization
{
    using namespace atoms;
    using lifecycle::logger;
    using notification::packet_factory;
    using notification::packet_header;

//--------------------------------------
//  internal definitions
//--------------------------------------

enum 
{
    //max_packet_data_size   = 511 - sizeof(packet_header),
    max_packet_data_size   = 1023 - sizeof(packet_header),
    packet_size_increment = 128
};

//--------------------------------------

static const text this_class_name[]
    = "writer_forwarded";

//--------------------------------------
//  private members
//--------------------------------------

writer * writer_forwarded::__trace_writer = 0;

//--------------------------------------
//  public methods
//--------------------------------------

writer_forwarded::writer_forwarded(
    forwarder & in_forwarder )
  :
    _forwarder( in_forwarder ),
    _packet_position( 0 ),
    _packet( 0 )
{}

//--------------------------------------

// virtual
writer_forwarded::~writer_forwarded()
{
    if ( _packet != 0 )
    {
        packet_factory::acquire_singleton().destroy( *_packet );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_boolean(
    const selector *    in_selector,
    const text *        in_label,
    boolean             in_value )
{
    if ( ! write_selector( in_selector, sizeof(whole8) ) )
    {
        return;
    }
    // write binary data
    whole8 & value = reinterpret_cast<whole8&>(
        _packet->getData()[_packet_position]);
    value = (in_value ? 1 : 0);
    _packet_position += sizeof(whole8);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "boolean",
            stringex_conversion::from( in_value,
                false, true ), // not as number, as letter
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_enum(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_names[],
    whole               in_name_count,
    integer             in_value )
{
    if ( !write_selector( in_selector, sizeof(integer) ) )
    {
        return;
    }
    // write binary data
    integer & value = reinterpret_cast<integer&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(integer);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "enum",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_integer(
    const selector *    in_selector,
    const text *        in_label,
    integer             in_value )
{
    if ( !write_selector( in_selector, sizeof(integer) ) )
    {
        return;
    }
    // write binary data
    integer & value = reinterpret_cast<integer&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(integer);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "integer",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_integer32( 
    const selector *    in_selector,
    const text *        in_label,
    integer32           in_value )
{
    if ( !write_selector( in_selector, sizeof(integer32) ) )
    {
        return;
    }
    // write binary data
    integer32 & value = reinterpret_cast<integer32&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(integer32);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "integer32",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_ordered_real(
    const selector *    in_selector,
    const text *        in_label,
    const real          in_values[],
    whole               in_count )
{
    if ( ! write_selector( in_selector, sizeof(real)*in_count ) )
    {
        return;
    }
    for ( whole i = 0; i < in_count; i++ )
    {
        // write binary data
        real & value = reinterpret_cast<real&>(
            _packet->getData()[_packet_position]);
        value = in_values[i];
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
            sso << in_values[i];
        }
        sso << ')';
        log.log_trace( 0, 0, sso.str().c_str() );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_ordered_whole(
    const selector *    in_selector,
    const text *        in_label,
    const whole         in_values[],
    whole               in_count )
{
    if ( ! write_selector( in_selector, sizeof(whole)*in_count ) )
    {
        return;
    }
    for ( whole i = 0; i < in_count; i++ )
    {
        // write binary data
        whole & value = reinterpret_cast<whole&>(
            _packet->getData()[_packet_position]);
        value = in_values[i];
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
            sso << in_values[i];
        }
        sso << ')';
        log.log_trace( 0, 0, sso.str().c_str() );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_real(
    const selector *    in_selector,
    const text *        in_label,
    real                in_value )
{
    if ( ! write_selector( in_selector, sizeof(real) ) )
    {            
        return;
    }
    // write binary data
    real & value = reinterpret_cast<real&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(real);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "real",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_string(
    const selector *    in_selector,
    const text *        in_label,
    const stringex &    in_string )
{
    if ( ! write_selector( in_selector, sizeof(whole16)+1 ) )
    {
        return;
    }
    // write string length as a whole16
    whole16 & textlen = reinterpret_cast<whole16&>(
        _packet->getData()[_packet_position]);
    _packet_position += sizeof(whole16);
    textlen = in_string.size();

    // write until end of text or end of packet
	for ( whole16 i = 0;
             (i < textlen)
          && (_packet_position < _packet->getHeader().getDataSize());
          i++, _packet_position++ )
    {
        byte ch = in_string[stringex::size_type(i)];
        _packet->getData()[_packet_position] = ch;
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "string",
            in_string, _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_text(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_text )
{
    if ( ! write_selector( in_selector, sizeof(whole16)+1 ) )
    {
        return;
    }
    // write text length as a whole16
    whole16 & textlen = reinterpret_cast<whole16&>(
        _packet->getData()[_packet_position]);
    _packet_position += sizeof(whole16);

    // write until end of text or end of packet
	whole16 i = 0;
    while (   (i != 0xFFFF)
           && (_packet_position < _packet->getHeader().getDataSize()) )
    {
        _packet->getData()[_packet_position++] = in_text[i];
        if ( in_text[i++] == '\0' ) // (writes terminating null)
        {
            break;
        }
    }
    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "text",
            in_text, _packet_position );
    }
    textlen = i;
}

//--------------------------------------

// virtual
void
writer_forwarded::write_whole(
    const selector *    in_selector,
    const text *        in_label,
    whole               in_value )
{
    if ( ! write_selector( in_selector, sizeof(whole) ) )
    {
        return;
    }
    // write binary data
    whole & value = reinterpret_cast<whole&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(whole);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_whole16(
    const selector *    in_selector,
    const text *        in_label,
    whole16             in_value )
{
    if ( ! write_selector( in_selector, sizeof(whole16) ) )
    {
        return;
    }
    // write binary data
    whole16 & value = reinterpret_cast<whole16&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(whole16);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole16",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_whole32(
    const selector *    in_selector,
    const text*         in_label,
    whole32             in_value )
{
    if ( ! write_selector( in_selector, sizeof(whole32) ) )
    {
        return;
    }
    // write binary data
    whole32 & value = reinterpret_cast<whole32&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(whole32);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole32",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_whole64(
    const selector *    in_selector,
    const text *        in_label,
    whole64             in_value )
{
    if ( ! write_selector( in_selector, sizeof(whole64) ) )
    {
        return;
    }
    // write binary data
    whole64 & value = reinterpret_cast<whole64&>(
        _packet->getData()[_packet_position]);
    value = in_value;
    _packet_position += sizeof(whole64);

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "whole64",
            stringex_conversion::from( in_value ),
            _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_object(
    const selector *    in_selector,
    const selector *    in_identity_selector,
    const text *        in_label,
    serializable *      in_object )
{
    if ( in_object == 0 )
    {
        write_whole32( in_selector, in_label, 0 );
        return;
    }
    if ( ! write_selector( in_selector, 0 ) )
    {
        return;
    }
    context ctx;
    in_object->write_to( ctx, *this, in_identity_selector );

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        stringex value;
        if ( in_object == 0 )
        {
            value = "null";
        }
        else
        {
            serializable_spec spec;
            in_object->populate_spec( spec );
            value = spec.to_string();
        }
        serializable_logging::log_trace_element(
            in_selector, in_label, "^object", value, _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_root(
    const selector *    in_selector, // ### DO SOMETHING WITH THIS
    serializable &      in_object )
{
    context ctx;
    write_root( ctx, in_selector, in_object );
}

//--------------------------------------

// virtual
void
writer_forwarded::write_root(
    context &           in_context,
    const selector *    in_selector, // ### DO SOMETHING WITH THIS
    serializable &      in_object )
{
    static const text this_method_name[]
        = "write_root(...)";

    logger & log = logger::get_singleton();
    boolean dolog = log.is_including( this_class_name );
    if ( dolog )
    {
        log.log_trace( this_class_name, this_method_name,
            "START" );
    }
    write_to_packet( in_context, in_selector, in_object );
    _forwarder.send( *_packet );

    if ( __trace_writer != 0 )
    {
        __trace_writer->write_root( in_context, in_selector, in_object );
    }
    if ( dolog )
    {
        log.log_trace( this_class_name, this_method_name,
            "FINISH" );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_spec(
    const selector *            in_selector,
    const text *                in_label,
    const serializable_spec &   in_spec )
{
    if ( ! write_selector( in_selector, 0 ) )
    {
        return;
    }
    write_whole16( 0, 0, in_spec._class_id );
    write_whole64( 0, 0, in_spec._object_id );

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "^spec",
            in_spec.to_string(), _packet_position );
    }
}

//--------------------------------------

// virtual
void
writer_forwarded::write_value(
    const selector *    in_selector,
    const selector *    in_member_selector,
    const text *        in_label,
    serializable &      in_value )
{
    if ( ! write_selector( in_selector, 0 ) )
    {
        return;
    }
    context ctx;
    in_value.write_to( ctx, *this, in_member_selector );

    if ( logger::get_singleton().is_including( this_class_name ) )
    {
        serializable_logging::log_trace_element(
            in_selector, in_label, "value/type",
            typeid(in_value).name(), _packet_position );
    }
}

//--------------------------------------
//  protected methods
//--------------------------------------

void
writer_forwarded::write_to_packet(
    context &           in_context,
    const selector *    in_selector,
    serializable &      in_object )
{
    packet_factory & packfactory = packet_factory::acquire_singleton();

//  ### JUST DO A SINGLE PACKET FOR NOW

    if ( _packet == 0 )
    {
        // create header
        packet_header header(
            packet_type_serialization::type_serializable,
            0, 1, max_packet_data_size );
            // ### HARDCODED MAXIMUM PACKET SIZE

        // create packet
        _packet = & packfactory.create( header );
    }
    else if ( _packet->getHeader().getDataSize()
              != max_packet_data_size )
    {
        
        packet & newPacket = packfactory.resize(
            *_packet, max_packet_data_size );
        packfactory.destroy( *_packet );
        _packet = &newPacket;
    }
    _packet_position = 0;

    in_object.write_to( in_context, *this, in_selector );

//  ### JUST DO A SINGLE PACKET FOR NOW

    // resize the packet to what was actually used
    packet & newPacket = packfactory.resize(
        *_packet, _packet_position );
    packfactory.destroy( *_packet );
    _packet = &newPacket;

    logger & log = logger::get_singleton();
    if ( log.is_including( "romp_send" ) ) // $$$ WILL THIS SCALE?
    {
        stream_string_o sso;
        sso << "ROMP SENT to " << _forwarder.getDestinationName()
            << ", by forwarding writer, packet header={"
            << _packet->getHeader()
            << "}";
        log.log_information( 0, 0, sso.str().c_str() );
    }            
}

//--------------------------------------
//  private methods
//--------------------------------------

boolean 
writer_forwarded::write_selector(
    const selector *    in_selector,
    size_type           in_data_size )
{
    // check for enough remaining space
    if ( in_selector != 0 )
    {
        in_data_size += in_selector->get_size();
    }
    if (   (_packet == 0)
        || (  (_packet_position+in_data_size)
            >= _packet->getHeader().getDataSize()) )
    {
    //  ### NOT YET HANDLING MULTIPLE PACKETS
        return false;
    }
    if ( in_selector != 0 )
    {
        whole selector_size = in_selector->get_size();
        byte * buffer = _packet->getData();
        for ( whole i = 0; i < in_selector->get_size(); i++ )
        {
            buffer[_packet_position++] = (*in_selector)[i];
        }
    }
    return true;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
