#if !defined(BEACH_GEOMETRY_COORDINATES)
#define      BEACH_GEOMETRY_COORDINATES
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       coordinates.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <geometry/constants.hpp>

#include <cmath>

namespace geometry
{
    using atoms::boolean;
    using atoms::no_init_type;
    using atoms::stringex;

//--------------------------------------

/// 2-D coordinates

template <class T>
class coordinates_xy
{
public:

    typedef T units;

    coordinates_xy( no_init_type ) {}
    coordinates_xy( T in_x = 0, T in_y = 0 ) : _x( in_x ), _y( in_y ) {}

    /// @name information
    //@{
    T x()    const { return _x; }
    T y()    const { return _y; }
    T x_abs() const { return _x < 0 ? - _x : _x; }
    T y_abs() const { return _y < 0 ? - _y : _y; }

    boolean is_valid() const
    {
        return (! constants<T>::is_nan( _x ))  
            && (! constants<T>::is_nan( _y ))
            && (_x != constants<T>::get_infinity())
            && (_y != constants<T>::get_infinity());
    }
    boolean is_zero() const { return (x() == 0) && (y() == 0); }
    boolean near_zero( T in_range ) const
    {
        return (   (x() <= in_range) && (x() >= - in_range)
                && (y() <= in_range) && (y() >= - in_range) );
    }
    T calc_magnitude() const
    {
        return sqrt( (this->_x*this->_x) + (this->_y*this->_y) );
    }
    T calc_magnitude_squared() const
    {
        return (this->_x*this->_x) + (this->_y*this->_y);
    }
    T distance( const coordinates_xy<T> & that ) const
    {
        return sqrt( distance_squared( that ) );
    }
    T distance_squared( const coordinates_xy<T> & that ) const
    {
        T dx = that.x() - x();
        T dy = that.y() - y();
        return dx*dx + dy*dy;
    }
    //@}

    /// @name change
    //@{
    void x(   T in_x        ) { _x = in_x;           }
    void y(   T in_y        ) { _y = in_y;           }
    void set( T in_x, T in_y ) { _x = in_x; _y = in_y; }
    T & mutate_x() { return _x; }
    T & mutate_y() { return _y; }
    //@}

    /// @name comparison operators
    //@{
    int operator ==( const coordinates_xy & rhs ) const { return ((x() == rhs.x()) && (y() == rhs.y())); }
    int operator !=( const coordinates_xy & rhs ) const { return ((x() != rhs.x()) || (y() != rhs.y())); }
    int operator > ( const coordinates_xy & rhs ) const { return ((x() >  rhs.x()) || (y() >  rhs.y())); }
    int operator < ( const coordinates_xy & rhs ) const { return ((x() <  rhs.x()) || (y() <  rhs.y())); }
    int operator >=( const coordinates_xy & rhs ) const { return ((x() >= rhs.x()) || (y() >= rhs.y())); }
    int operator <=( const coordinates_xy & rhs ) const { return ((x() <= rhs.x()) || (y() <= rhs.y())); }
    //@}

    /// @name arithmetic operators
    //@{
    coordinates_xy operator -()                               const { return coordinates_xy<T>( -x(), -y() ); }
    coordinates_xy operator +( const T & rhs )                const { return coordinates_xy<T>( x()+rhs, y()+rhs ); }
    coordinates_xy operator -( const T & rhs )                const { return coordinates_xy<T>( x()-rhs, y()-rhs ); }
    coordinates_xy operator *( const T & rhs )                const { return coordinates_xy<T>( x()*rhs, y()*rhs ); }
    coordinates_xy operator /( const T & rhs )                const { return coordinates_xy<T>( x()/rhs, y()/rhs ); }
    coordinates_xy operator +( const coordinates_xy<T> & rhs ) const { return coordinates_xy<T>( x()+rhs.x(), y()+rhs.y() ); }
    coordinates_xy operator -( const coordinates_xy<T> & rhs ) const { return coordinates_xy<T>( x()-rhs.x(), y()-rhs.y() ); }
    coordinates_xy operator *( const coordinates_xy<T> & rhs ) const { return coordinates_xy<T>( x()*rhs.x(), y()*rhs.y() ); }
    coordinates_xy operator /( const coordinates_xy<T> & rhs ) const { return coordinates_xy<T>( x()/rhs.x(), y()/rhs.y() ); }
    //@}

    /// @name arithmetic assignment operators
    //@{
    coordinates_xy & operator +=( const T & rhs )                { _x+= rhs;    _y+= rhs;    return *this; }
    coordinates_xy & operator -=( const T & rhs )                { _x-= rhs;    _y-= rhs;    return *this; }
    coordinates_xy & operator *=( const T & rhs )                { _x*= rhs;    _y*= rhs;    return *this; }
    coordinates_xy & operator /=( const T & rhs )                { _x/= rhs;    _y/= rhs;    return *this; }
    coordinates_xy & operator +=( const coordinates_xy<T> & rhs ) { _x+= rhs._x; _y+= rhs._y; return *this; }
    coordinates_xy & operator -=( const coordinates_xy<T> & rhs ) { _x-= rhs._x; _y-= rhs._y; return *this; }
    coordinates_xy & operator *=( const coordinates_xy<T> & rhs ) { _x*= rhs._x; _y*= rhs._y; return *this; }
    coordinates_xy & operator /=( const coordinates_xy<T> & rhs ) { _x/= rhs._x; _y/= rhs._y; return *this; }
    //@}

protected: ///< allow subclasses to modify data members

    T _x, _y;
};

//--------------------------------------

/// 3-D coordinates

template <class T>
class coordinates_xyz
{
public:

    typedef T units;

    coordinates_xyz( no_init_type ) {}
    coordinates_xyz( stringex & s ) { from_string( s ); }
    coordinates_xyz( T in_x = 0, T in_y = 0, T in_z = 0 )
      : _x( in_x ), _y( in_y ), _z( in_z ) {}
    
    /// @name information
    //@{
    T x()    const { return _x; }
    T y()    const { return _y; }
    T z()    const { return _z; }
    T x_abs() const { return _x < 0 ? - _x : _x; }
    T y_abs() const { return _y < 0 ? - _y : _y; }
    T z_abs() const { return _z < 0 ? - _z : _z; }

    boolean is_valid() const
    {
        return (! constants<T>::is_nan( _x ))  
            && (! constants<T>::is_nan( _y ))
            && (! constants<T>::is_nan( _z ))
            && (_x != constants<T>::get_infinity())
            && (_y != constants<T>::get_infinity())
            && (_z != constants<T>::get_infinity());
    }
    boolean is_zero() const { return (x() == 0) && (y() == 0) && (z() == 0); }
    boolean near_zero( T in_range ) const
    {
        return (   (x() <= in_range) && (x() >= - in_range)
                && (y() <= in_range) && (y() >= - in_range)
                && (z() <= in_range) && (z() >= - in_range) );
    }
    void clamp_near_ends( T end1, T end2, T nearness )
    {
        T nearend1neg = end1 - nearness;
        T nearend1pos = end1 + nearness;
        T nearend2neg = end2 - nearness;
        T nearend2pos = end2 + nearness;
        if ( (_x >= nearend1neg) && (_x <= nearend1pos) )
        {
            _x = end1;
        }
        else if ( (_x >= nearend2neg) && (_x <= nearend2pos) )
        {
            _x = end2;
        }
        if ( (_y >= nearend1neg) && (_y <= nearend1pos) )
        {
            _y = end1;
        }
        else if ( (_y >= nearend2neg) && (_y <= nearend2pos) )
        {
            _y = end2;
        }
        if ( (_z >= nearend1neg) && (_z <= nearend1pos) )
        {
            _z = end1;
        }
        else if ( (_z >= nearend2neg) && (_z <= nearend2pos) )
        {
            _z = end2;
        }
    }
    T distance( const coordinates_xyz<T> & that ) const
    {
        return sqrt( distance_squared( that ) );
    }
    T distance_squared( const coordinates_xyz<T> & that ) const
    {
        T dx = that.x() - x();
        T dy = that.y() - y();
        T dz = that.z() - z();
        return dx*dx + dy*dy + dz*dz;
    }
    T distance_xz( const coordinates_xyz<T> & that ) const
    {
        T dx = that.x() - x();
        T dz = that.z() - z();
        return sqrt( dx*dx + dz*dz );
    }
    coordinates_xyz<T>
    interpolate( 
        const coordinates_xyz<T> & that,
        T                         in_ratio ) const
    {
        return coordinates_xyz(
            _x + ((that._x-_x)*in_ratio),
            _y + ((that._y-_y)*in_ratio),
            _z + ((that._z-_z)*in_ratio) );
    }
    //@}

    /// @name change
    //@{
    void x(        T in_x                 ) { _x = in_x;                     }
    void y(        T in_y                 ) { _y = in_y;                     }
    void z(        T in_z                 ) { _z = in_z;                     }
    void set(      T in_x, T in_y, T in_z ) { _x = in_x; _y = in_y; _z = in_z; }
    void add(      T in_x, T in_y, T in_z ) { _x+= in_x; _y+= in_y; _z+= in_z; }
    void subtract( T in_x, T in_y, T in_z ) { _x-= in_x; _y-= in_y; _z-= in_z; }
    void multiply( T in_x, T in_y, T in_z ) { _x*= in_x; _y*= in_y; _z*= in_z; }
    void divide(   T in_x, T in_y, T in_z ) { _x/= in_x; _y/= in_y; _z/= in_z; }
    void negate()                           { _x = -_x; _y = -_y; _z = -_z; }
    void zero()                             { _x = 0;   _y = 0;   _z = 0;   }

    void divide_safely( const coordinates_xyz & rhs )
    {
        rhs.x() == 0.0 ? _x == 0 : _x /= rhs.x();
        rhs.y() == 0.0 ? _y == 0 : _y /= rhs.y();
        rhs.z() == 0.0 ? _z == 0 : _z /= rhs.z();
    }
    T & mutate_x() { return _x; }
    T & mutate_y() { return _y; }
    T & mutate_z() { return _z; }
    //@}

    T operator[]( size_t i ) const
    {
        return (i == 0) ? _x : ((i == 1) ? _y : _z);
    }

    /// @name comparison operators
    //@{
    int operator ==( const coordinates_xyz & rhs ) const { return ((x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z())); }
    int operator !=( const coordinates_xyz & rhs ) const { return ((x() != rhs.x()) || (y() != rhs.y()) || (z() != rhs.z())); }
    int operator > ( const coordinates_xyz & rhs ) const { return ((x() >  rhs.x()) || (y() >  rhs.y()) || (z() >  rhs.z())); }
    int operator < ( const coordinates_xyz & rhs ) const { return ((x() <  rhs.x()) || (y() <  rhs.y()) || (z() <  rhs.z())); }
    int operator >=( const coordinates_xyz & rhs ) const { return ((x() >= rhs.x()) || (y() >= rhs.y()) || (z() >= rhs.z())); }
    int operator <=( const coordinates_xyz & rhs ) const { return ((x() <= rhs.x()) || (y() <= rhs.y()) || (z() <= rhs.z())); }
    //@}

    /// @name arithmetic operators
    //@{
    coordinates_xyz operator -()                                const { return coordinates_xyz<T>( -x(), -y(), -z() ); }
    coordinates_xyz operator +( const T & rhs )                 const { return coordinates_xyz<T>( x()+rhs, y()+rhs, z()+rhs ); }
    coordinates_xyz operator -( const T & rhs )                 const { return coordinates_xyz<T>( x()-rhs, y()-rhs, z()-rhs ); }
    coordinates_xyz operator *( const T & rhs )                 const { return coordinates_xyz<T>( x()*rhs, y()*rhs, z()*rhs ); }
    coordinates_xyz operator /( const T & rhs )                 const { return coordinates_xyz<T>( x()/rhs, y()/rhs, z()/rhs ); }
    coordinates_xyz operator +( const coordinates_xyz<T> & rhs ) const { return coordinates_xyz<T>( x()+rhs.x(), y()+rhs.y(), z()+rhs.z() ); }
    coordinates_xyz operator -( const coordinates_xyz<T> & rhs ) const { return coordinates_xyz<T>( x()-rhs.x(), y()-rhs.y(), z()-rhs.z() ); }
    coordinates_xyz operator *( const coordinates_xyz<T> & rhs ) const { return coordinates_xyz<T>( x()*rhs.x(), y()*rhs.y(), z()*rhs.z() ); }
    coordinates_xyz operator /( const coordinates_xyz<T> & rhs ) const { return coordinates_xyz<T>( x()/rhs.x(), y()/rhs.y(), z()/rhs.z() ); }
    //@}

    /// @name arithmetic assignment operators
    //@{
    coordinates_xyz & operator +=( const T & rhs )                 { _x+= rhs;    _y+= rhs;    _z+= rhs;    return *this; }
    coordinates_xyz & operator -=( const T & rhs )                 { _x-= rhs;    _y-= rhs;    _z-= rhs;    return *this; }
    coordinates_xyz & operator *=( const T & rhs )                 { _x*= rhs;    _y*= rhs;    _z*= rhs;    return *this; }
    coordinates_xyz & operator /=( const T & rhs )                 { _x/= rhs;    _y/= rhs;    _z/= rhs;    return *this; }
    coordinates_xyz & operator +=( const coordinates_xyz<T> & rhs ) { _x+= rhs._x; _y+= rhs._y; _z+= rhs._z; return *this; }
    coordinates_xyz & operator -=( const coordinates_xyz<T> & rhs ) { _x-= rhs._x; _y-= rhs._y; _z-= rhs._z; return *this; }
    coordinates_xyz & operator *=( const coordinates_xyz<T> & rhs ) { _x*= rhs._x; _y*= rhs._y; _z*= rhs._z; return *this; }
    coordinates_xyz & operator /=( const coordinates_xyz<T> & rhs ) { _x/= rhs._x; _y/= rhs._y; _z/= rhs._z; return *this; }
    //@}

    ///@ name conversions
    //@{ 
    void        from_string( const stringex & ); ///< format is CDL: "{n/n/n}"
    stringex    make_formatted_string( boolean in_cdl_format = false ) const;
    //@}

protected: ///< allow subclasses to modify data members

    T _x, _y, _z;
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_COORDINATES
