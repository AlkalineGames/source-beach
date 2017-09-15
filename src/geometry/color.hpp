#if !defined(BEACH_GEOMETRY_COLOR)
#define      BEACH_GEOMETRY_COLOR
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       color.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>

namespace geometry
{
    using atoms::integer;
    using atoms::whole8;
    using atoms::whole16;
    using atoms::whole32;

//--------------------------------------

class color
{
public:

#if BEACH_COLOR_HIGH_ENABLED
    enum format { format_low, format_high, format_true, format_ultra };
#else
    enum format { format_low, format_true, format_ultra };
#endif
    enum value_low ///< 4 bits of color
    {
        low_black,          ///< ....
        low_blue,           ///< ...B
        low_green,          ///< ..G.
        low_cyan,           ///< ..GB
        low_red,            ///< .R..
        low_magenta,        ///< .R.B
        low_brown,          ///< .RG.
        low_gray_bright,    ///< .RGB
        low_gray,           ///< I...
        low_blue_bright,    ///< I..B
        low_green_bright,   ///< I.G.
        low_cyan_bright,    ///< I.GB
        low_red_bright,     ///< IR..
		low_magenta_bright, ///< IR.B
        low_yellow,         ///< IRG.
        low_white,          ///< IRGB
        value_low_count
    };
    enum
    {
        threshold_low_from_true_dim    = 85, ///< == 255/3
        threshold_low_from_true_bright = 171 ///< == 255 * 2/3 
    };
#if BEACH_COLOR_HIGH_ENABLED
    typedef whole8  value_high;         ///< 5-bit level of RGB (0-31)
#endif
    typedef whole8  value_true;         ///< 8-bit level of RGB (0-255)
    typedef whole8  value_packed_low;   ///< 4-bit IRGB
#if BEACH_COLOR_HIGH_ENABLED
    typedef whole16 value_packed_high;  ///< full 16-bits of 0-R-G-B
#endif
    typedef whole32 value_packed_true;  ///< full 32-bits of 0-R-G-B
    typedef whole32 value_packed_ultra; ///< full 32-bits of ALPHA-R-G-B

#if BEACH_COLOR_HIGH_ENABLED
    static const value_high         max_value_high()            { return 0x01F; }
#endif
    static const value_true         max_value_true()            { return 0x0FF; }
    static const value_packed_low   max_value_packed_low()      { return 0x00F; }
#if BEACH_COLOR_HIGH_ENABLED
    static const value_packed_high  max_value_packed_high()     { return 0x07FFF; }
#endif
    static const value_packed_true  max_value_packed_true()     { return 16777215l; }
    static const value_packed_ultra max_value_packed_ultra()    { return 4294967295ul; }

    color( atoms::no_init_type ) {}
    color( value_low in_value = low_black ) { set_low( in_value ); }
    color( format, integer );
    color( format, whole32 );
    color( format, whole8 r, whole8 g, whole8 b, whole8 a = 0 );

    bool operator ==( const color & rhs ) const
    {
        return (_packed_ultra == rhs._packed_ultra);
    }
    bool operator !=( const color & rhs ) const
    {
        return (_packed_ultra != rhs._packed_ultra);
    }
    value_low           get_low()           const { return value_low(_packed_low); }
#if BEACH_COLOR_HIGH_ENABLED
    value_high          get_high_red()      const { return value_high(_packed_high >> 10); }
    value_high          get_high_green()    const { return value_high(_packed_high >> 5) & 0x1F; }
    value_high          get_high_blue()     const { return value_high(_packed_high) & 0x1F; }
#endif
    value_true          get_true_red()      const { return value_true(_packed_ultra >> 16) & 0xFF; }
    value_true          get_true_green()    const { return value_true(_packed_ultra >> 8) & 0xFF; }
    value_true          get_true_blue()     const { return value_true(_packed_ultra) & 0xFF; }
    value_true          get_alpha()         const { return value_true(_packed_ultra >> 24); }
#if BEACH_COLOR_HIGH_ENABLED
    value_packed_high   get_packed_high()   const { return _packed_high; }
#endif
    value_packed_true   get_packed_true()   const { return _packed_ultra & 0x00FFFFFF; }
    value_packed_ultra  get_packed_ultra()  const { return _packed_ultra; }

    void set_low(           value_low           );
#if BEACH_COLOR_HIGH_ENABLED
    void set_high_red(      value_high          );
    void set_high_green(    value_high          );
    void set_high_blue(     value_high          );
    void set_high_rgb(      value_high r, value_high g, value_high b );
#endif
    void set_true_red(      value_true          );
    void set_true_green(    value_true          );
    void set_true_blue(     value_true          );
    void set_true_rgb(      value_true r, value_true g, value_true b )
    {
        set_ultra_rgb( r, g, b, 0 );
    }
    void set_ultra_rgb(     value_true r, value_true g, value_true b, value_true a );
    void set_alpha(         value_true          );
#if BEACH_COLOR_HIGH_ENABLED
    void set_packed_high(   value_packed_high   );
#endif
    void set_packed_true(   value_packed_true   );
    void set_packed_ultra(  value_packed_ultra  );

private:

    void update_low_from_true();
#if BEACH_COLOR_HIGH_ENABLED
    void update_true_from_high();
#endif

    value_packed_low    _packed_low;
#if BEACH_COLOR_HIGH_ENABLED
    value_packed_high   _packed_high;
#endif
    value_packed_ultra  _packed_ultra;

}; // end of class color

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_COLOR
