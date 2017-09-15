#if !defined(BEACH_GEOMETRY_AXIS)
#define      BEACH_GEOMETRY_AXIS
//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       axis.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace geometry
{
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;

//--------------------------------------

/// 3-D axis indicator

class axis
{
public:

    enum moving     ///< Y-up left-handed coordinates
    {
        no_moving,
        left,       ///< - X axis
        right,      ///< + X axis
        down,       ///< - Y axis
        up,         ///< + Y axis
        backward,   ///< - Z axis
        forward,    ///< + Z axis
        moving_count,
    };
    enum turning    ///< Y-up left-handed coordinates
    {
        no_turning,
        pitch_down, ///< - X axis
        pitch_up,   ///< + X axis
        yaw_right,  ///< - Y axis
        yaw_left,   ///< + Y axis
        bank_left,  ///< - Z axis
        bank_right, ///< + Z axis
        turning_count,
    };
    typedef whole index;

    static axis x() { return axis( 0 ); }
    static axis y() { return axis( 1 ); }
    static axis z() { return axis( 2 ); }

    static axis by_letter( text l )
    {
        return (( l == 'x') || ( l == 'X')) ? 0 : 
              ((( l == 'y') || ( l == 'Y')) ? 1 : 2);
    }
    static axis by_text( const text * t )
    {
        return ((*t == 'x') || (*t == 'X')) ? 0 : 
              (((*t == 'y') || (*t == 'Y')) ? 1 : 2);
    }
    static stringex to_string_moving( moving m )
    {
        switch ( m )
        {
            case left       : return "left";        break;
            case right      : return "right";       break;
            case down       : return "down";        break;
            case up         : return "up";          break;
            case backward   : return "backward";    break;
            case forward    : return "forward";     break;
            default         : return 0;             break;
        }
    }
    static stringex to_string_turning( turning t )
    {
        switch ( t )
        {
            case pitch_down : return "pitch_down";  break;
            case pitch_up   : return "pitch_up";    break;
            case yaw_right  : return "yaw_right";   break;
            case yaw_left   : return "yaw_left";    break;
            case bank_right : return "bank_right";  break;
            case bank_left  : return "bank_left";   break;
            default         : return 0;             break;
        }
    }

    axis( index i = 0 )
      :
        _index( i > 2 ? 2 : i )
    {} 
    index to_index() const
    {
        return _index;
    }
    text to_letter() const
    {
        return  (_index == 0) ? 'x' :
               ((_index == 1) ? 'y' : 'z');
    }
    const text * to_text() const
    {
        return  (_index == 0) ? "x" :
               ((_index == 1) ? "y" : "z");
    }
    bool operator ==( const axis & rhs ) const
    {
        return _index == rhs._index;
    } 
    bool operator !=( const axis & rhs ) const
    {
        return _index != rhs._index;
    } 

private:

    index _index;    
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_AXIS
