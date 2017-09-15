#if !defined(BEACH_GEOMETRY_CONSTANTS)
#define      BEACH_GEOMETRY_CONSTANTS
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       constants.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

/// Beach Geometry Framework
namespace geometry
{
    using atoms::boolean;

//--------------------------------------

/// precalculated constants for a numeric type 
/**
 *  This is provided as a performance enhancement
 *  to reduce redundant calculations.
 */      
template <class T>
class constants
{
public:

    typedef T numeric_type;

    /// @name corrupt values (using <cgeometry> macros)
    //@{
    static T get_huge_val() { return __huge_val; }
    static T get_infinity() { return __infinity; }
    static T get_nan()      { return __nan; }

    static boolean is_nan( T );
    //@}

    /// @name trigonometric values
    //@{
    static T get_pi()                   { return __pi; }
    static T get_pi_halved()            { return __pi_halved; }
    static T get_pi_doubled()           { return __pi_doubled; }
    static T get_pi_quartered()         { return __pi_quartered; }
    static T get_degrees_per_radian()   { return __degrees_per_radian; }
    static T get_radians_per_degree()   { return __radians_per_degree; }
    //@}

private:

    static T __huge_val;
    static T __infinity;
    static T __nan;
    static T __pi;
    static T __pi_halved;
    static T __pi_doubled;
    static T __pi_quartered;
    static T __degrees_per_radian;
    static T __radians_per_degree;

}; // end of class constants

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_CONSTANTS
