//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       constants.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/constants.hpp> // this header

#include <cmath>
#include <limits>

namespace geometry
{

//--------------------------------------
//  internal definitions
//--------------------------------------

#define PI 3.14159265358979323846264338327950288419716939937511 // (51 digits)

//--------------------------------------
//  private members
//--------------------------------------

// static
template <class T>
T constants<T>::__huge_val =
    std::numeric_limits<T>::max();

// static
template <class T>
T constants<T>::__infinity =
    std::numeric_limits<T>::has_infinity
    ? std::numeric_limits<T>::infinity()
    : std::numeric_limits<T>::max();

// static
template <class T>
T constants<T>::__nan =
    std::numeric_limits<T>::has_quiet_NaN
    ? std::numeric_limits<T>::quiet_NaN()
    : std::numeric_limits<T>::max();

// static
template <class T>
T constants<T>::__pi
    = T(PI);

// static
template <class T>
T constants<T>::__pi_halved
    = T(PI)*T(0.5);

// static
template <class T>
T constants<T>::__pi_doubled
    = T(PI)*T(2);

// static
template <class T>
T constants<T>::__pi_quartered
    = T(PI)*T(0.25);

// static
template <class T>
T constants<T>::__radians_per_degree
    = T(PI)/T(180);

// static
template <class T>
T constants<T>::__degrees_per_radian
    = T(180)/T(PI);

//--------------------------------------
//  public methods
//--------------------------------------

// static
template <class T>
boolean
constants<T>::is_nan(
    T in_number )
{
    if ( std::numeric_limits<T>::has_quiet_NaN )
    {
        return (in_number == std::numeric_limits<T>::quiet_NaN());
    }
    return false;
/*
    // @@@ KEEPING THIS IN CASE THE == COMPARISON ABOVE DOESN'T WORK

    // @@@ THIS IS LAME; IS THERE A WAY TO GEN THE CORRECT CODE FOR THE TEMPLATE ARG? [cat]
    // !!! copied from MinGW geometry.h
    if ( sizeof(in_number) == sizeof(float) )
    {
        return __isnanf( in_number );
    }
    else if ( sizeof(in_number) == sizeof(double) )
    {
        return __isnan( in_number );
    }
    else if ( sizeof(in_number) == sizeof(long double) )
    {
        return __isnanl( in_number );
    }
    else
    {
        return false;
    }
*/
}

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
