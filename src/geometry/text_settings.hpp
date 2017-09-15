#if !defined(BEACH_GEOMETRY_TEXT_SETTINGS)
#define      BEACH_GEOMETRY_TEXT_SETTINGS
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_settings.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <geometry/color.hpp>

namespace geometry
{
    using atoms::boolean;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;
    using atoms::whole32;

//--------------------------------------

/// settings for text

class text_settings
{
public:

    enum align { left_align, center_align, right_align };
    enum
    {
//         default_font_height     = 10,  ///< !!! arbitrary
         default_max_pixel_width = 500  ///< !!! arbitrary
    };
                
    align    _align;
    boolean  _is_billboard;
    boolean  _is_multiline;
    boolean  _do_wrap;
    color    _foreground_color;
    color    _background_color;
    stringex _font_name;
    whole    _font_height;      ///< 0 implies using settings default
    whole    _max_pixel_width;

    text_settings(
        align               in_align            = left_align,
        boolean             in_is_multiline     = false,
        boolean             in_do_wrap          = false,
        const color &       in_foreground_color = color( color::low_white ),
        const color &       in_background_color =
            color( color::format_ultra, whole32(0xFF000000) ), ///< transparent
        const text *        in_font_name        = 0,
        whole               in_font_height      = 0, ///< 0 implies using settings default
        whole               in_max_pixel_width  = default_max_pixel_width )
      :
        _align(             in_align ),
        _is_billboard(      false ),
        _is_multiline(      in_is_multiline ),
        _do_wrap(           in_do_wrap ),
        _foreground_color(  in_foreground_color ),
        _background_color(  in_background_color ),
        _font_name(         in_font_name ),
        _font_height(       in_font_height ),
        _max_pixel_width(   in_max_pixel_width )
    {}        
    text_settings(
        align               in_align,
        boolean             in_is_billboard,
        boolean             in_is_multiline,
        boolean             in_do_wrap,
        const color &       in_foreground_color,
        const color &       in_background_color =
            color( color::format_ultra, whole32(0xFF000000) ), ///< transparent
        const text *        in_font_name        = 0,
        whole               in_font_height      = 0, ///< 0 implies using settings default
        whole               in_max_pixel_width  = default_max_pixel_width )
      :
        _align(             in_align ),
        _is_billboard(      in_is_billboard ),
        _is_multiline(      in_is_multiline ),
        _do_wrap(           in_do_wrap ),
        _foreground_color(  in_foreground_color ),
        _background_color(  in_background_color ),
        _font_name(         in_font_name ),
        _font_height(       in_font_height ),
        _max_pixel_width(   in_max_pixel_width )
    {}        
    text_settings(
        const color &       in_foreground_color,
        const color &       in_background_color =
            color( color::format_ultra, whole32(0xFF000000) ), ///< transparent
        const text *        in_font_name        = 0,
        align               in_align            = left_align,
        boolean             in_is_multiline     = false,
        boolean             in_do_wrap          = false,
        whole               in_font_height      = 0, ///< 0 implies using settings default
        whole               in_max_pixel_width  = default_max_pixel_width )
      :
        _align(             in_align ),
        _is_billboard(      false ),
        _is_multiline(      in_is_multiline ),
        _do_wrap(           in_do_wrap ),
        _foreground_color(  in_foreground_color ),
        _background_color(  in_background_color ),
        _font_name(         in_font_name ),
        _font_height(       in_font_height ),
        _max_pixel_width(   in_max_pixel_width )
    {}        
   
}; // end of class text_settings

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_TEXT_SETTINGS
