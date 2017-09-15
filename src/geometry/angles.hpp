#if !defined(BEACH_GEOMETRY_ANGLES)
#define      BEACH_GEOMETRY_ANGLES
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       angles.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/coordinates.hpp>

namespace geometry
{
    using atoms::real;

//--------------------------------------

// @@@ SHOULD REPLACE USING THESE WITH constants<T>
const real pi                   = 3.141592653589793; ///< (16 digits)
const real pi_halved            = pi*real(0.5);
const real pi_doubled           = pi*real(2);
const real radians_per_degree   = pi/real(180);
const real degrees_per_radian   = real(180)/pi;

//--------------------------------------

/// 2-D angles in degrees

template <class T>
class degrees_xy
    : public coordinates_xy<T>
{
public:

    enum { cycle = 360 };

    degrees_xy( no_init_type ) {}
    degrees_xy( T in_x = 0, T in_y = 0 )
      : coordinates_xy<T>( in_x, in_y )
    {}
    void normalize()
    {   ///< !!! THIS ASSUMES THAT T IS A FLOATING POINT TYPE!
        this->_x -= fmod( this->_x, cycle );
        this->_y -= fmod( this->_y, cycle );
    }
    degrees_xy & operator +=( const degrees_xy & rhs ) { this->_x+= rhs._x; this->_y+= rhs._y; return *this; }
    degrees_xy & operator -=( const degrees_xy & rhs ) { this->_x-= rhs._x; this->_y-= rhs._y; return *this; }

    int operator ==( const degrees_xy & rhs ) const { return ((this->_x == rhs._x) && (this->_y == rhs._y)); }
    int operator !=( const degrees_xy & rhs ) const { return ((this->_x != rhs._x) || (this->_y != rhs._y)); }
    int operator > ( const degrees_xy & rhs ) const { return ((this->_x >  rhs._x) && (this->_y >  rhs._y)); }
    int operator < ( const degrees_xy & rhs ) const { return ((this->_x <  rhs._x) && (this->_y <  rhs._y)); }
    int operator >=( const degrees_xy & rhs ) const { return ((this->_x >= rhs._x) && (this->_y >= rhs._y)); }
    int operator <=( const degrees_xy & rhs ) const { return ((this->_x <= rhs._x) && (this->_y <= rhs._y)); }

    friend degrees_xy<T> operator +( const degrees_xy<T> & lhs,
                                     const degrees_xy<T> & rhs )
    {   return degrees_xy<T>( (lhs._x+rhs._x), (lhs._y+rhs._y) ); }

    friend degrees_xy<T> operator -( const degrees_xy<T> & lhs,
                                     const degrees_xy<T> & rhs )
    {   return degrees_xy<T>( (lhs._x-rhs._x), (lhs._y-rhs._y) ); }

}; // end of template degrees_xy<>

//--------------------------------------

template <class T> struct radians_xyz;

//--------------------------------------

/// 3-D angles in degrees

template <class T>
class degrees_xyz
    : public coordinates_xyz<T>
{
public:

    enum { cycle = 360 };

    degrees_xyz( no_init_type ) {}
    degrees_xyz( T in_x = 0, T in_y = 0, T in_z = 0 )
      : coordinates_xyz<T>( in_x, in_y, in_z ) {}
    degrees_xyz( const radians_xyz<T> & rhs )
      : coordinates_xyz<T>(
            rhs._x*degrees_per_radian,
            rhs._y*degrees_per_radian,
            rhs._z*degrees_per_radian )
    {}
    void normalize()
    {   ///< !!! THIS ASSUMES THAT T IS A FLOATING POINT TYPE!
        this->_x -= fmod( this->_x, cycle );
        this->_y -= fmod( this->_y, cycle );
        this->_z -= fmod( this->_z, cycle );
    }
    int operator ==( const degrees_xyz & rhs ) const { return ((this->_x == rhs._x) && (this->_y == rhs._y) && (this->_z == rhs._z)); }
    int operator !=( const degrees_xyz & rhs ) const { return ((this->_x != rhs._x) || (this->_y != rhs._y) || (this->_z != rhs._z)); }
    int operator > ( const degrees_xyz & rhs ) const { return ((this->_x >  rhs._x) && (this->_y >  rhs._y) && (this->_z >  rhs._z)); }
    int operator < ( const degrees_xyz & rhs ) const { return ((this->_x <  rhs._x) && (this->_y <  rhs._y) && (this->_z <  rhs._z)); }
    int operator >=( const degrees_xyz & rhs ) const { return ((this->_x >= rhs._x) && (this->_y >= rhs._y) && (this->_z >= rhs._z)); }
    int operator <=( const degrees_xyz & rhs ) const { return ((this->_x <= rhs._x) && (this->_y <= rhs._y) && (this->_z <= rhs._z)); }

    degrees_xyz operator -()                            const { return degrees_xyz<T>( -this->_x, -this->_y, -this->_z ); }
    degrees_xyz operator +( const T & rhs )             const { return degrees_xyz<T>( this->_x+rhs, this->_y+rhs, this->_z+rhs ); }
    degrees_xyz operator -( const T & rhs )             const { return degrees_xyz<T>( this->_x-rhs, this->_y-rhs, this->_z-rhs ); }
    degrees_xyz operator *( const T & rhs )             const { return degrees_xyz<T>( this->_x*rhs, this->_y*rhs, this->_z*rhs ); }
    degrees_xyz operator /( const T & rhs )             const { return degrees_xyz<T>( this->_x/rhs, this->_y/rhs, this->_z/rhs ); }
    degrees_xyz operator +( const degrees_xyz<T> & rhs ) const { return degrees_xyz<T>( this->_x+rhs._x, this->_y+rhs._y, this->_z+rhs._z ); }
    degrees_xyz operator -( const degrees_xyz<T> & rhs ) const { return degrees_xyz<T>( this->_x-rhs._x, this->_y-rhs._y, this->_z-rhs._z ); }
    degrees_xyz operator *( const degrees_xyz<T> & rhs ) const { return degrees_xyz<T>( this->_x*rhs._x, this->_y*rhs._y, this->_z*rhs._z ); }
    degrees_xyz operator /( const degrees_xyz<T> & rhs ) const { return degrees_xyz<T>( this->_x/rhs._x, this->_y/rhs._y, this->_z/rhs._z ); }

    degrees_xyz & operator +=( const T & rhs )             { this->_x+= rhs;    this->_y+= rhs;    this->_z+= rhs;    return *this; }
    degrees_xyz & operator -=( const T & rhs )             { this->_x-= rhs;    this->_y-= rhs;    this->_z-= rhs;    return *this; }
    degrees_xyz & operator *=( const T & rhs )             { this->_x*= rhs;    this->_y*= rhs;    this->_z*= rhs;    return *this; }
    degrees_xyz & operator /=( const T & rhs )             { this->_x/= rhs;    this->_y/= rhs;    this->_z/= rhs;    return *this; }
    degrees_xyz & operator +=( const degrees_xyz<T> & rhs ) { this->_x+= rhs._x; this->_y+= rhs._y; this->_z+= rhs._z; return *this; }
    degrees_xyz & operator -=( const degrees_xyz<T> & rhs ) { this->_x-= rhs._x; this->_y-= rhs._y; this->_z-= rhs._z; return *this; }
    degrees_xyz & operator *=( const degrees_xyz<T> & rhs ) { this->_x*= rhs._x; this->_y*= rhs._y; this->_z*= rhs._z; return *this; }
    degrees_xyz & operator /=( const degrees_xyz<T> & rhs ) { this->_x/= rhs._x; this->_y/= rhs._y; this->_z/= rhs._z; return *this; }

}; // end of template degrees_xyz<>

//--------------------------------------

/// 2-D angles in radians

template <class T>
class radians_xy
    : public coordinates_xy<T>
{
public:

    static const T cycle()
    {   return 2*pi; }

    radians_xy( no_init_type ) {}
    radians_xy( T in_x = 0, T in_y = 0 )
      : coordinates_xy<T>( in_x, in_y )
    {}
    void normalize()
    {   ///< !!! THIS ASSUMES THAT T IS A FLOATING POINT TYPE!
        this->_x -= fmod( this->_x, cycle() );
        this->_y -= fmod( this->_y, cycle() );
    }
    radians_xy & operator +=( const radians_xy & rhs ) { this->_x+= rhs._x; this->_y+= rhs._y; return *this; }
    radians_xy & operator -=( const radians_xy & rhs ) { this->_x-= rhs._x; this->_y-= rhs._y; return *this; }
    radians_xy & operator *=( const radians_xy & rhs ) { this->_x*= rhs._x; this->_y*= rhs._y; return *this; }
    radians_xy & operator /=( const radians_xy & rhs ) { this->_x/= rhs._x; this->_y/= rhs._y; return *this; }

    int operator ==( const radians_xy & rhs ) const { return ((this->_x == rhs._x) && (this->_y == rhs._y)); }
    int operator !=( const radians_xy & rhs ) const { return ((this->_x != rhs._x) || (this->_y != rhs._y)); }
    int operator > ( const radians_xy & rhs ) const { return ((this->_x >  rhs._x) && (this->_y >  rhs._y)); }
    int operator < ( const radians_xy & rhs ) const { return ((this->_x <  rhs._x) && (this->_y <  rhs._y)); }
    int operator >=( const radians_xy & rhs ) const { return ((this->_x >= rhs._x) && (this->_y >= rhs._y)); }
    int operator <=( const radians_xy & rhs ) const { return ((this->_x <= rhs._x) && (this->_y <= rhs._y)); }

}; // end of template radians_xy<>

//--------------------------------------

/// 3-D angles in radians

template <class T>
class radians_xyz
    : public coordinates_xyz<T>
{
public:

    static const T cycle() { return pi_doubled; }

    radians_xyz( no_init_type ) {}
    radians_xyz( T in_x = 0, T in_y = 0, T in_z = 0 )
      : coordinates_xyz<T>( in_x, in_y, in_z ) {}
    radians_xyz( const degrees_xyz<T> & rhs )
      : coordinates_xyz<T>(
            rhs.x()*radians_per_degree,
            rhs.y()*radians_per_degree,
            rhs.z()*radians_per_degree )
    {}
    void normalize()
    {   ///< !!! THIS ASSUMES THAT T IS A FLOATING POINT TYPE!
        this->_x -= fmod( this->_x, cycle() );
        this->_y -= fmod( this->_y, cycle() );
        this->_z -= fmod( this->_z, cycle() );
    }
    int operator ==( const radians_xyz & rhs ) const { return ((this->_x == rhs._x) && (this->_y == rhs._y) && (this->_z == rhs._z)); }
    int operator !=( const radians_xyz & rhs ) const { return ((this->_x != rhs._x) || (this->_y != rhs._y) || (this->_z != rhs._z)); }
    int operator > ( const radians_xyz & rhs ) const { return ((this->_x >  rhs._x) && (this->_y >  rhs._y) && (this->_z >  rhs._z)); }
    int operator < ( const radians_xyz & rhs ) const { return ((this->_x <  rhs._x) && (this->_y <  rhs._y) && (this->_z <  rhs._z)); }
    int operator >=( const radians_xyz & rhs ) const { return ((this->_x >= rhs._x) && (this->_y >= rhs._y) && (this->_z >= rhs._z)); }
    int operator <=( const radians_xyz & rhs ) const { return ((this->_x <= rhs._x) && (this->_y <= rhs._y) && (this->_z <= rhs._z)); }

    radians_xyz operator -()                            const { return radians_xyz<T>( -this->_x, -this->_y, -this->_z ); }
    radians_xyz operator +( const T & rhs )             const { return radians_xyz<T>( this->_x+rhs, this->_y+rhs, this->_z+rhs ); }
    radians_xyz operator -( const T & rhs )             const { return radians_xyz<T>( this->_x-rhs, this->_y-rhs, this->_z-rhs ); }
    radians_xyz operator *( const T & rhs )             const { return radians_xyz<T>( this->_x*rhs, this->_y*rhs, this->_z*rhs ); }
    radians_xyz operator /( const T & rhs )             const { return radians_xyz<T>( this->_x/rhs, this->_y/rhs, this->_z/rhs ); }
    radians_xyz operator +( const radians_xyz<T> & rhs ) const { return radians_xyz<T>( this->_x+rhs._x, this->_y+rhs._y, this->_z+rhs._z ); }
    radians_xyz operator -( const radians_xyz<T> & rhs ) const { return radians_xyz<T>( this->_x-rhs._x, this->_y-rhs._y, this->_z-rhs._z ); }
    radians_xyz operator *( const radians_xyz<T> & rhs ) const { return radians_xyz<T>( this->_x*rhs._x, this->_y*rhs._y, this->_z*rhs._z ); }
    radians_xyz operator /( const radians_xyz<T> & rhs ) const { return radians_xyz<T>( this->_x/rhs._x, this->_y/rhs._y, this->_z/rhs._z ); }

    radians_xyz & operator +=( const T & rhs )             { this->_x+= rhs;    this->_y+= rhs;    this->_z+= rhs;    return *this; }
    radians_xyz & operator -=( const T & rhs )             { this->_x-= rhs;    this->_y-= rhs;    this->_z-= rhs;    return *this; }
    radians_xyz & operator *=( const T & rhs )             { this->_x*= rhs;    this->_y*= rhs;    this->_z*= rhs;    return *this; }
    radians_xyz & operator /=( const T & rhs )             { this->_x/= rhs;    this->_y/= rhs;    this->_z/= rhs;    return *this; }
    radians_xyz & operator +=( const radians_xyz<T> & rhs ) { this->_x+= rhs._x; this->_y+= rhs._y; this->_z+= rhs._z; return *this; }
    radians_xyz & operator -=( const radians_xyz<T> & rhs ) { this->_x-= rhs._x; this->_y-= rhs._y; this->_z-= rhs._z; return *this; }
    radians_xyz & operator *=( const radians_xyz<T> & rhs ) { this->_x*= rhs._x; this->_y*= rhs._y; this->_z*= rhs._z; return *this; }
    radians_xyz & operator /=( const radians_xyz<T> & rhs ) { this->_x/= rhs._x; this->_y/= rhs._y; this->_z/= rhs._z; return *this; }

}; // end of template radians_xyz<>

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_ANGLES
