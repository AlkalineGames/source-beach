//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       color.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------
//
#include <geometry/color.hpp> // this header

namespace geometry
{

//--------------------------------------
//  public methods
//--------------------------------------

color::color(
    format  in_format,
    integer in_value )
{
    switch ( in_format )
    {
        case format_low     : set_low( value_low(in_value) ); break;
#if BEACH_COLOR_HIGH_ENABLED
        case format_high    : set_packed_high(  value_packed_high(in_value) ); break;
#endif
        case format_true    : set_packed_true(  value_packed_true(in_value) ); break;
        case format_ultra   : set_packed_ultra( value_packed_ultra(in_value) ); break;
        default             : set_packed_ultra( 0 ); break; // invalid format
    }
}

//--------------------------------------

color::color(
    format  in_format,
    whole32 in_value )
{
    switch ( in_format )
    {
        case format_low     : set_low( value_low(in_value) ); break;
#if BEACH_COLOR_HIGH_ENABLED
        case format_high    : set_packed_high(  value_packed_high(in_value) ); break;
#endif
        case format_true    : set_packed_true(  value_packed_true(in_value) ); break;
        case format_ultra   : set_packed_ultra( value_packed_ultra(in_value) ); break;
        default             : set_packed_ultra( 0 ); break; // invalid format
    }
}

//--------------------------------------

color::color(
    format  in_format, 
    whole8  r,
    whole8  g,
    whole8  b,
    whole8  a )
{
    switch ( in_format )
    {
        case format_low     : set_low( value_low(0) ); break;
#if BEACH_COLOR_HIGH_ENABLED
        case format_high    : set_high_rgb(  r, g, b ); break;
#endif
        case format_true    : set_true_rgb(  r, g, b ); break;
        case format_ultra   : set_ultra_rgb( r, g, b, a ); break;
        default             : set_packed_ultra( 0 ); break; // invalid format
    }
}

//--------------------------------------

void
color::set_low(
    value_low in_low )
{
    _packed_low   = in_low;
#if BEACH_COLOR_HIGH_ENABLED
    _packed_high  = 0;
#endif
    _packed_ultra = 0;

    if ( _packed_low & 8 ) // intensity
    {
        _packed_ultra |= 0x00808080;
#if BEACH_COLOR_HIGH_ENABLED
        _packed_high  |= 0x4210;
#endif
    }
    if ( _packed_low & 4 ) // red
    {
        _packed_ultra |= 0x007F0000;
#if BEACH_COLOR_HIGH_ENABLED
        _packed_high  |= 0x3C00;
#endif
    }
    if ( _packed_low & 2 ) // green
    {
        _packed_ultra |= 0x00007F00;
#if BEACH_COLOR_HIGH_ENABLED
        _packed_high  |= 0x01E0;
#endif
    }
    if ( _packed_low & 1 ) // blue
    {
        _packed_ultra |= 0x0000007F;
#if BEACH_COLOR_HIGH_ENABLED
        _packed_high  |= 0x000F;
#endif
    }
}

//--------------------------------------

#if BEACH_COLOR_HIGH_ENABLED
void
color::highRGB(
    value_high r,
    value_high g,
    value_high b )
{
    _packed_high = (value_packed_high(r & 0x1F) << 10)
                 | (value_packed_high(g & 0x1F) << 5)
                 |  value_packed_high(b & 0x1F);
    update_true_from_high();
    update_low_from_true();
}

//--------------------------------------

void
color::highRed(
    value_high in_value )
{
    _packed_high &= 0x83FF;
    _packed_high |= (value_packed_high(in_value & 0x1F) << 10);
    update_true_from_high();
    update_low_from_true();
}

//--------------------------------------

void
color::highGreen(
    value_high in_value )
{
    _packed_high &= 0xFC1F;
    _packed_high |= (value_packed_high(in_value & 0x1F) << 5);
    update_true_from_high();
    update_low_from_true();
}

//--------------------------------------

void
color::highBlue(
    value_high in_value )
{
    _packed_high &= 0xFFE0;
    _packed_high |= value_packed_high(in_value & 0x1F);
    update_true_from_high();
    update_low_from_true();
}
#endif

//--------------------------------------

void
color::set_true_red(
    value_true in_value )
{
    _packed_ultra &= 0xFF00FFFF;
    _packed_ultra |= (value_packed_ultra(in_value & 0xFF) << 16);
    update_low_from_true();
}

//--------------------------------------

void
color::set_true_green(
    value_true in_value )
{
    _packed_ultra &= 0xFFFF00FF;
    _packed_ultra |= (value_packed_ultra(in_value & 0xFF) << 8);
    update_low_from_true();
}

//--------------------------------------

void
color::set_true_blue(
    value_true in_value )
{
    _packed_ultra &= 0xFFFFFF00;
    _packed_ultra |= value_packed_ultra(in_value & 0xFF);
    update_low_from_true();
}

//--------------------------------------

void
color::set_alpha(
    value_true in_value )
{
    _packed_ultra &= 0x00FFFFFF;
    _packed_ultra |= value_packed_ultra(in_value) << 24;
}

//--------------------------------------

#if BEACH_COLOR_HIGH_ENABLED
void
color::set_packed_high(
    value_packed_high in_value )
{
    _packed_high = in_value;
    update_from_high();
}
#endif

//--------------------------------------

void
color::set_packed_true(
    value_packed_true in_value )
{
    _packed_ultra = value_packed_ultra(in_value) & 0x00FFFFFF;
    update_low_from_true();
}

//--------------------------------------

void
color::set_ultra_rgb( 
    value_true r,
    value_true g,
    value_true b,
    value_true a )
{
    _packed_ultra = (value_packed_ultra(a)        << 24)
                  | (value_packed_ultra(r & 0xFF) << 16)
                  | (value_packed_ultra(g & 0xFF) << 8)
                  |  value_packed_ultra(b & 0xFF);
    update_low_from_true();
}

//--------------------------------------

void
color::set_packed_ultra(
    value_packed_ultra in_value )
{
    _packed_ultra = in_value;
    update_low_from_true();
}

//--------------------------------------
//  private methods
//--------------------------------------

void
color::update_low_from_true()
{
    _packed_low = 0; 
    value_true r = get_true_red();
    value_true g = get_true_green();
    value_true b = get_true_blue();
    if ( r >= threshold_low_from_true_dim )
    {
        _packed_low |= 0x0100;
    }
    if ( g >= threshold_low_from_true_dim )
    {
        _packed_low |= 0x0010;
    }
    if ( b >= threshold_low_from_true_dim )
    {
        _packed_low |= 0x0001;
    }
    if (   (r >= threshold_low_from_true_bright)
        || (g >= threshold_low_from_true_bright)
        || (b >= threshold_low_from_true_bright) )
    {
        _packed_low |= 0x1000;
    }
}

//--------------------------------------

#if BEACH_COLOR_HIGH_ENABLED
void
color::update_true_from_high()
{
    // ### FINISH THIS WHEN ENABLED
}
#endif

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
