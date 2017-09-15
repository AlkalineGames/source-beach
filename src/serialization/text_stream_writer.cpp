//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_writer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_writer.hpp> // this header

#include <atoms/stream_string.hpp>
#include <atoms/stringex.hpp>
#include <serialization/serializable.hpp>
#include <serialization/serializable_spec.hpp>

#include <iomanip>

namespace serialization
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const whole ostream_precision_default
    = 12;

static const text attributeSeparator[] =
    ", ";

static const text embeddedInitiator =
    '<';

static const text embeddedTerminator =
    '>';

static const text labelSeparator =
    '=';

static const text object_terminator =
    ';';

static const text orderedInitiator[] =
    "{";

static const text orderedSeparator =
    '/';

static const text orderedTerminator =
    '}';

static const text root_spec_terminator[] =
    ": ";

static const text textInitiator =
    '\"';

static const text textTerminator =
    '\"';

//--------------------------------------
//  public methods
//--------------------------------------

// static 
stringex
text_stream_writer::write_to_string(
    serializable &      in_serializable,
    const selector *    in_selector )
{
    stream_string_o sso;
    text_stream_writer tswriter( sso );
    context ctx;
    in_serializable.write_to( ctx, tswriter, in_selector );
    return sso.str();
}

//--------------------------------------

text_stream_writer::text_stream_writer(
    std::ostream & out_stream )
  :
    _stream_adapter_echo( out_stream ),
    _needs_attribute_separator(  false ),
    _needs_root_spec_terminator( false )
{
    _stream_adapter_echo.get_stream_real()
        << std::setprecision( ostream_precision_default );
}

//--------------------------------------

text_stream_writer::text_stream_writer(
    stream_adapter_echo & out_stream_adapter_echo )
  :
    _stream_adapter_echo( out_stream_adapter_echo ),
    _needs_attribute_separator(  false ),
    _needs_root_spec_terminator( false )
{
    _stream_adapter_echo.get_stream_real()
        << std::setprecision( ostream_precision_default );
}

//--------------------------------------

// virtual
text_stream_writer::~text_stream_writer()
{}

//--------------------------------------

// virtual
void
text_stream_writer::write_boolean(
    const selector *, // selector not used
    const text *    in_label,
    boolean         in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << (in_value ? "true" : "false");
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_enum(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_names[],
    whole               in_name_count,
    integer             in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    if (   (in_value >= 0)
        && (in_value < in_name_count)
        && (in_names[in_value] != 0) )
    {
        _stream_adapter_echo << in_names[in_value];
    } 
    else
    {
        _stream_adapter_echo << in_value;
    }
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_integer(
    const selector *, // in_selector not used
    const text *    in_label,
    integer         in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void 
text_stream_writer::write_integer32(
    const selector *, // in_selector not used
    const text *    in_label,
    integer32       in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_ordered_real(
    const selector *, // in_selector not used
    const text *    in_label,
    const real      in_values[],
    whole           in_count )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << orderedInitiator;
    --in_count;
    for ( whole i = 0; i < in_count; i++ )
    {
        _stream_adapter_echo << in_values[i] << orderedSeparator;
    }
    _stream_adapter_echo << in_values[in_count] << orderedTerminator;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_ordered_whole(
    const selector *, // in_selector not used
    const text *    in_label,
    const whole     in_values[],
    whole           in_count )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << orderedInitiator;
    --in_count;
    for ( whole i = 0; i < in_count; i++ )
    {
        _stream_adapter_echo << in_values[i] << orderedSeparator;
    }
    _stream_adapter_echo << in_values[in_count] << orderedTerminator;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_real( 
    const selector *, // in_selector not used
    const text *    in_label,
    real            in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_string(
    const selector *,   // in_selector not used
    const text *        in_label,
    const stringex &    in_string )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << textInitiator << in_string << textTerminator;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_text(
    const selector *,   // in_selector not used
    const text *        in_label,
    const text *        in_text )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << textInitiator << in_text << textTerminator;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_whole(
    const selector *    in_selector,
    const text *        in_label,
    whole               in_value )
{
    write_whole32( in_selector, in_label, in_value );
}

//--------------------------------------

// virtual
void 
text_stream_writer::write_whole16(
    const selector *,   // in_selector not used
    const text *        in_label,
    whole16             in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_whole32(
    const selector *,   // in_selector not used
    const text *        in_label,
    whole32             in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_whole64( 
    const selector *,   // in_selector not used
    const text *        in_label,
    whole64             in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_value;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_object(
    const selector *,   // in_selector not used
    const selector *    in_identity_selector,
    const text *        in_label,
    serializable *      in_object )
{
    if ( _needs_attribute_separator )
    {   
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    if ( in_object != 0 )
    {
        _needs_attribute_separator = false;
        context ctx;
        in_object->write_to( ctx, *this, in_identity_selector );
    }
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_root(
    const selector *    in_selector,
    serializable &      in_object )
{
    context ctx;
    write_root( ctx, in_selector, in_object );
}

//--------------------------------------

// virtual
void
text_stream_writer::write_root(
    context &           in_context,
    const selector *    in_selector,
    serializable &      in_object )
{
    _needs_attribute_separator  = false;
    _needs_root_spec_terminator = true;
    in_object.write_to( in_context, *this, in_selector );
    _stream_adapter_echo << object_terminator << std::endl;
    _needs_attribute_separator  = false;
    _needs_root_spec_terminator = false;
}

//--------------------------------------

// virtual
void
text_stream_writer::write_spec(
    const selector *            in_selector,
    const text *                in_label,
    const serializable_spec &   in_spec )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << in_spec.to_string();
    if ( _needs_root_spec_terminator )
    {
        _stream_adapter_echo << root_spec_terminator;
        _needs_root_spec_terminator = false;
        _needs_attribute_separator = false;
    }
    else
    {
        _needs_attribute_separator = true;
    }
}

//--------------------------------------

// virtual
void
text_stream_writer::write_value(
    const selector *,   // in_selector not used
    const selector *    in_member_selector,
    const text *        in_label,
    serializable &      in_value )
{
    if ( _needs_attribute_separator )
    {
        _stream_adapter_echo << attributeSeparator;
        _needs_attribute_separator = false;
    }
    if ( in_label != 0 )
    {
        _stream_adapter_echo << in_label << labelSeparator;
    }
    _stream_adapter_echo << embeddedInitiator;
    context ctx;
    in_value.write_to( ctx, *this, in_member_selector );
    _stream_adapter_echo << embeddedTerminator;
    _needs_attribute_separator = true;
}

//--------------------------------------

// virtual
boolean
text_stream_writer::write_newline()
{
    _stream_adapter_echo << object_terminator << std::endl;
    _needs_attribute_separator = false;
    _needs_root_spec_terminator = true;
    return true;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
