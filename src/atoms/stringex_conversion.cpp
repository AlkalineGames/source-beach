//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stringex_conversion.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stream_string.hpp>
#include <atoms/stringex_conversion.hpp>

#include <iomanip>
#include <sstream>

namespace atoms
{

//--------------------------------------
//  internal methods
//--------------------------------------

static
void
set_ssi_format(
    stream_string_i &   inout_ssi,
    whole8              in_base )
{
    if ( in_base == 2 )
    {
        // @@@ NO SUPPORT IN STANDARD LIBRARY FOR BINARY
    }
    else if ( in_base == 8 )
    {
        inout_ssi >> std::oct;
    }
    else if ( in_base == 16 )
    {
        inout_ssi >> std::hex;
    }
    // default is decimal
    inout_ssi >> std::skipws;
}

//--------------------------------------

static
void
set_sso_format(
    stream_string_o &   inout_sso,
    whole8              in_base,
    whole8              in_byte_size )
{
    if ( in_base == 2 )
    {
        // @@@ NO SUPPORT IN STANDARD LIBRARY FOR BINARY
    }
    else if ( in_base == 8 )
    {
        inout_sso << '0'
            << std::oct
            << std::setfill( '0' )
            << std::setw( in_byte_size*4 );
    }
    else if ( in_base == 16 )
    {
        inout_sso << "0x"
            << std::hex
            << std::setfill( '0' )
            << std::setw( in_byte_size*2 );
    }
    // default is decimal format, no fill, no set width
}

//--------------------------------------
//  public methods
//--------------------------------------

// static
stringex
stringex_conversion::from(
    integer8    in_value,
    whole8      in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 1 );
    sso << integer(in_value); // !!! treated as character otherwise
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    integer16   in_value,
    whole8      in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 2 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    integer32   in_value,
    whole8      in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 4 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    integer64   in_value,
    whole8      in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 8 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    integer_machine in_value,
    whole8          in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, sizeof(integer) );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    whole8  in_value,
    whole8  in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 1 );
    sso << whole(in_value); // !!! treated as character otherwise
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    whole16 in_value,
    whole8  in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 2 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    whole32 in_value,
    whole8  in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 4 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    whole64 in_value,
    whole8  in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, 8 );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    whole_machine   in_value,
    whole8          in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, sizeof(whole) );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    pointer in_value,
    whole8  in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, sizeof(pointer) );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    pointer_to_const    in_value,
    whole8              in_base )
{
    stream_string_o sso;
    set_sso_format( sso, in_base, sizeof(pointer_to_const) );
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    real32  in_value,
    whole8  in_base )
{
    stream_string_o sso;
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    real64  in_value,
    whole8  in_base )
{
    stream_string_o sso;
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    real80  in_value,
    whole8  in_base )
{
    stream_string_o sso;
    sso << in_value;
    return sso.str();
}

//--------------------------------------

// static
stringex
stringex_conversion::from(
    boolean in_value,
    boolean in_as_number,
    boolean in_as_letter )
{
    if ( in_as_number )
    {
        return in_value ? "1" : "0";
    }
    else if ( in_as_letter )
    {
        return in_value ? "T" : "F";
    }
    else
    {
        return in_value ? "true" : "false";
    }
}

//--------------------------------------

// static
integer8  
stringex_conversion::to(
    integer8 &      out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        integer val;
        ssi >> val; // !!! treated as character otherwise
        out_value = integer8(val);
    }
    return out_value;
}

//--------------------------------------

// static
integer16 
stringex_conversion::to(
    integer16 &     out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
integer32 
stringex_conversion::to(
    integer32 &     out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
integer64 
stringex_conversion::to(
    integer64 &     out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
integer_machine   
stringex_conversion::to(
    integer_machine &   out_value,
    const text *        in_text,
    whole8              in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
whole8    
stringex_conversion::to(
    whole8 &        out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        whole val;
        ssi >> val; // !!! treated as character otherwise
        out_value = whole8(val);
    }
    return out_value;
}

//--------------------------------------

// static
whole16   
stringex_conversion::to(
    whole16 &       out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
whole32   
stringex_conversion::to(
    whole32 &       out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
whole64   
stringex_conversion::to(
    whole64 &       out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
whole_machine     
stringex_conversion::to(
    whole_machine & out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
pointer   
stringex_conversion::to(
    pointer &       out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
pointer_to_const
stringex_conversion::to(
    pointer_to_const &  out_value,
    const text *        in_text,
    whole8              in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        pointer p;
        ssi >> p;
        out_value = p;
    }
    return out_value;
}

//--------------------------------------

// static
real32    
stringex_conversion::to(
    real32 &        out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
real64    
stringex_conversion::to(
    real64 &        out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
real80    
stringex_conversion::to(
    real80 &        out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = 0;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        set_ssi_format( ssi, in_base );
        ssi >> out_value;
    }
    return out_value;
}

//--------------------------------------

// static
boolean   
stringex_conversion::to(
    boolean &       out_value,
    const text *    in_text,
    whole8          in_base )
{
    out_value = false;
    if ( in_text != 0 )
    {
        stream_string_i ssi( in_text );
        ssi >> std::skipws >> std::boolalpha >> out_value;
    }
    return out_value;
}

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
// (end of file)
