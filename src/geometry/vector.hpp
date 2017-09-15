#if !defined(BEACH_GEOMETRY_VECTOR)
#define      BEACH_GEOMETRY_VECTOR
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       vector.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace geometry
{
    template <class T> struct vector_xyz;
    // @@@ must forward declare this because matrix.hpp includes
    // @@@ this header and we include matrix.hpp
    // @@@ (although could be moved to imp)
};

#include <geometry/angles.hpp>
#include <geometry/coordinates.hpp>
#include <geometry/matrix.hpp>

#include <cstdlib>

namespace geometry
{

//--------------------------------------

/// template for a 3-D vector, left-handed

template <class T>
class vector_xyz
    : public coordinates_xyz<T>
{
public:

    static const vector_xyz<T> & get_axis_x_neg();
    static const vector_xyz<T> & get_axis_y_neg();
    static const vector_xyz<T> & get_axis_z_neg();
    static const vector_xyz<T> & get_axis_x_pos();
    static const vector_xyz<T> & get_axis_y_pos();
    static const vector_xyz<T> & get_axis_z_pos();

    enum axis_enum { axis_x, axis_y, axis_z };

    vector_xyz( no_init_type )
      : coordinates_xyz<T>( atoms::no_init )
    {}
    vector_xyz( T in_x = 0, T in_y = 0, T in_z = 0 )
      : coordinates_xyz<T>( in_x, in_y, in_z )
    {}
    vector_xyz( const vector_xyz & rhs )
      : coordinates_xyz<T>( rhs )
    {}
    vector_xyz( const coordinates_xyz<T> & rhs )
      : coordinates_xyz<T>( rhs )
    {}
    vector_xyz( const vector_xyz & lhs, const vector_xyz & rhs )
      : coordinates_xyz<T>( ///< cross product
            lhs._y * rhs._z - lhs._z * rhs._y,
		    lhs._z * rhs._x - lhs._x * rhs._z,
    		lhs._x * rhs._y - lhs._y * rhs._x )
    {}
    vector_xyz( axis_enum in_axis )
      : coordinates_xyz<T>( 
            in_axis == axis_x ? 1 : 0,
            in_axis == axis_y ? 1 : 0, 
            in_axis == axis_z ? 1 : 0 )
    {}
    vector_xyz( axis_enum in_axis, const degrees_xyz<T> & in_angles )
      : coordinates_xyz<T>( 
            in_axis == axis_x ? 1 : 0,
            in_axis == axis_y ? 1 : 0, 
            in_axis == axis_z ? 1 : 0 )
    {   
        rotate( in_angles );
    }
    vector_xyz( axis_enum in_axis, const radians_xyz<T> & in_angles )
      : coordinates_xyz<T>( 
            in_axis == axis_x ? 1 : 0,
            in_axis == axis_y ? 1 : 0, 
            in_axis == axis_z ? 1 : 0 )
    {
        rotate( in_angles );
    }
    vector_xyz( const vector_xyz & rhs, const radians_xyz<T> & in_angles )
      : coordinates_xyz<T>( rhs )
    {
        rotate( in_angles );
    }
    vector_xyz & operator =( axis_enum in_axis )
    {
        switch ( in_axis )
        { 
            case axis_x : this->set( 1, 0, 0 ); break;
            case axis_y : this->set( 0, 1, 0 ); break;
            case axis_z : this->set( 0, 0, 1 ); break;
        }
        return *this;
    }
    vector_xyz cross_product( const vector_xyz & rhs ) const
    {
        return vector_xyz<T>(
            this->_y*rhs._z - this->_z*rhs._y,
		    this->_z*rhs._x - this->_x*rhs._z,
		    this->_x*rhs._y - this->_y*rhs._x );
    }
    T dot_product( const vector_xyz & rhs ) const
    {
        return this->_x*rhs._x + this->_y*rhs._y + this->_z*rhs._z;
    }
    T get_magnitude_squared() const
    {
        return ((this->_x*this->_x) + (this->_y*this->_y) + (this->_z*this->_z) );
    }
    T magnitude() const // $$$ expensive
    {
        return sqrt( (this->_x*this->_x) + (this->_y*this->_y) + (this->_z*this->_z) );
    }
    vector_xyz & normalize() // to magnitude of 1, if possible
    {
        T mag = magnitude();
        if ( mag == 0 ) {
            this->zero();
        } else {
            *this /= mag;
        }
        return *this;
    }
    vector_xyz & normalize( T in_magnitude_new )
    {
        if ( in_magnitude_new == 0 ) {
            this->zero();
        } else {
            T ratio = (magnitude()/in_magnitude_new);
            if ( ratio == 0 ) {
                this->zero();
            } else {
                *this /= ratio;
            }
        }
        return *this;
    }
    vector_xyz & normalize_get_magnitude( T & out_magnitude )
    {
        out_magnitude = magnitude();
        if ( out_magnitude == 0 ) {
            this->zero();
        } else {
            *this /= out_magnitude;
        }
        return *this;
    }
    vector_xyz & rotate( const degrees_xyz<T> & in_angles )
    {
        radians_xyz<T> converted( in_angles );
        return rotate( converted );
    }
    vector_xyz & rotate( const radians_xyz<T> & in_angles )
    {
        // rotate Z--X--Y (same as Lightwave)
        matrix_4x4<T> m( axis_z, -in_angles.z() ); // ### USE -Z UNTIL MATRIX UPDATED
	    m.rotate_x( in_angles.x() );
	    m.rotate_y( in_angles.y() );
	    m.transform( *this );
        return *this;
    }
    vector_xyz & rotate( const vector_xyz & in_vector, T in_radians )
    {
        matrix_4x4<T> m( in_vector, in_radians );
        m.transform( *this );
        return *this;
    }
    vector_xyz & rotate_x( T in_radians )
    {
        matrix_4x4<T> m( axis_x, in_radians );
        m.transform( *this );
        return *this;
    }
    vector_xyz & rotate_y( T in_radians )
    {
        matrix_4x4<T> m( axis_y, in_radians );
        m.transform( *this );
        return *this;
    }
    vector_xyz & rotate_z( T in_radians )
    {
        matrix_4x4<T> m( axis_z, in_radians );
        m.transform( *this );
        return *this;
    }
    /// set to a random vector with each dimension no greater than maximum span
    void randomize( T in_maximum_span )
    {
        T doublemaxspan = in_maximum_span * 2.0;
        this->x( ((T(rand())/T(RAND_MAX))-0.5)*doublemaxspan );
        this->y( ((T(rand())/T(RAND_MAX))-0.5)*doublemaxspan );
        this->z( ((T(rand())/T(RAND_MAX))-0.5)*doublemaxspan );
    }
    T angle( const vector_xyz & rhs ) const // between 0 and pi
    {
        return acos( dot_product( rhs )/(magnitude() * rhs.magnitude()) );
    }
    T angle_x() const // facing -x, cw from y axis to z axis
    {   return (this->_z == 0) && (this->_y > 0) ? 0 : atan2( this->_z, this->_y ); }

    T angle_y() const // facing -y, cw from z axis to x axis
    {   return (this->_x == 0) && (this->_z > 0) ? 0 : atan2( this->_x, this->_z ); }

    T angle_z() const // facing +z, cw from y axis to x axis
    {   return (this->_x == 0) && (this->_y > 0) ? 0 : atan2( this->_x, this->_y ); }

    radians_xyz<T> angles() const
    {   return radians_xyz<T>( angle_x(), angle_y(), angle_z() ); }

    int operator ==( const vector_xyz & rhs ) const { return ((this->_x == rhs._x) && (this->_y == rhs._y) && (this->_z == rhs._z)); }
    int operator !=( const vector_xyz & rhs ) const { return ((this->_x != rhs._x) || (this->_y != rhs._y) || (this->_z != rhs._z)); }
    int operator > ( const vector_xyz & rhs ) const { return ((this->_x >  rhs._x) && (this->_y >  rhs._y) && (this->_z >  rhs._z)); }
    int operator < ( const vector_xyz & rhs ) const { return ((this->_x <  rhs._x) && (this->_y <  rhs._y) && (this->_z <  rhs._z)); }
    int operator >=( const vector_xyz & rhs ) const { return ((this->_x >= rhs._x) && (this->_y >= rhs._y) && (this->_z >= rhs._z)); }
    int operator <=( const vector_xyz & rhs ) const { return ((this->_x <= rhs._x) && (this->_y <= rhs._y) && (this->_z <= rhs._z)); }

    vector_xyz operator -()                           const { return vector_xyz<T>( -this->_x, -this->_y, -this->_z ); }
    vector_xyz operator +( const T & rhs )            const { return vector_xyz<T>( this->_x+rhs, this->_y+rhs, this->_z+rhs ); }
    vector_xyz operator -( const T & rhs )            const { return vector_xyz<T>( this->_x-rhs, this->_y-rhs, this->_z-rhs ); }
    vector_xyz operator *( const T & rhs )            const { return vector_xyz<T>( this->_x*rhs, this->_y*rhs, this->_z*rhs ); }
    vector_xyz operator /( const T & rhs )            const { return vector_xyz<T>( this->_x/rhs, this->_y/rhs, this->_z/rhs ); }
    vector_xyz operator +( const vector_xyz<T> & rhs ) const { return vector_xyz<T>( this->_x+rhs._x, this->_y+rhs._y, this->_z+rhs._z ); }
    vector_xyz operator -( const vector_xyz<T> & rhs ) const { return vector_xyz<T>( this->_x-rhs._x, this->_y-rhs._y, this->_z-rhs._z ); }
    vector_xyz operator *( const vector_xyz<T> & rhs ) const { return vector_xyz<T>( this->_x*rhs._x, this->_y*rhs._y, this->_z*rhs._z ); }
    vector_xyz operator /( const vector_xyz<T> & rhs ) const { return vector_xyz<T>( this->_x/rhs._x, this->_y/rhs._y, this->_z/rhs._z ); }

    vector_xyz & operator +=( const T & rhs )            { this->_x+= rhs;    this->_y+= rhs;    this->_z+= rhs;    return *this; }
    vector_xyz & operator -=( const T & rhs )            { this->_x-= rhs;    this->_y-= rhs;    this->_z-= rhs;    return *this; }
    vector_xyz & operator *=( const T & rhs )            { this->_x*= rhs;    this->_y*= rhs;    this->_z*= rhs;    return *this; }
    vector_xyz & operator /=( const T & rhs )            { this->_x/= rhs;    this->_y/= rhs;    this->_z/= rhs;    return *this; }
    vector_xyz & operator +=( const vector_xyz<T> & rhs ) { this->_x+= rhs._x; this->_y+= rhs._y; this->_z+= rhs._z; return *this; }
    vector_xyz & operator -=( const vector_xyz<T> & rhs ) { this->_x-= rhs._x; this->_y-= rhs._y; this->_z-= rhs._z; return *this; }
    vector_xyz & operator *=( const vector_xyz<T> & rhs ) { this->_x*= rhs._x; this->_y*= rhs._y; this->_z*= rhs._z; return *this; }
    vector_xyz & operator /=( const vector_xyz<T> & rhs ) { this->_x/= rhs._x; this->_y/= rhs._y; this->_z/= rhs._z; return *this; }

}; // end of template vector_xyz

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_VECTOR
