#if !defined(BEACH_GEOMETRY_MATRIX)
#define      BEACH_GEOMETRY_MATRIX
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       matrix.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace geometry
{
    template <class T> class matrix_4x4;
    // @@@ must forward declare this because vector.hpp includes
    // @@@ this header and we include vector.hpp
};

#include <atoms/enumerations.hpp>
#include <geometry/angles.hpp>
#include <geometry/vector.hpp>

#include <cmath>
#include <memory>

namespace geometry
{

//--------------------------------------

/// 4x4 matrix

template <class T>
class matrix_4x4
{
public:

    typedef T                   row_type[4];
    typedef radians_xyz<T>      angles_rad;
    typedef coordinates_xyz<T>  coordinates;
    typedef coordinates_xyz<T>  size;
    typedef vector_xyz<T>       vector;

    matrix_4x4( atoms::no_init_type )
    {}
    matrix_4x4( // default to identity matrix
        T in00 = 1, T in01 = 0, T in02 = 0, T in03 = 0,
        T in10 = 0, T in11 = 1, T in12 = 0, T in13 = 0,
        T in20 = 0, T in21 = 0, T in22 = 1, T in23 = 0,
        T in30 = 0, T in31 = 0, T in32 = 0, T in33 = 1 )
    {   
        row( 0, in00, in01, in02, in03 );
        row( 1, in10, in11, in12, in13 );
        row( 2, in20, in21, in22, in23 );
        row( 3, in30, in31, in32, in33 );
    }
    matrix_4x4( typename vector::axis_enum in_axis,
                T in_radians ) // rotation about orthogonal axis
    {
        switch ( in_axis )
        {
            case vector::axis_x : init_rotation_x( in_radians ); break;
            case vector::axis_y : init_rotation_y( in_radians ); break;
            case vector::axis_z : init_rotation_z( in_radians ); break;
            default : init_identity();
        }        
    }
    matrix_4x4( const vector & in_vector,
                T in_radians ) // rotation about arbitrary axis
    {
        init_rotation( in_vector, in_radians );
    }
    matrix_4x4( const angles_rad & in_angles )
    {
        init_alignment( in_angles );
    }
    // accessors & mutators
    operator const T*() const { return _m[0]; }
    operator       T*()       { return _m[0]; }
    const row_type & operator []( int i ) const { return _m[i]; }
          row_type & operator []( int i )       { return _m[i]; }
    void row( int i, T in0, T in1, T in2 )
    {  
        _m[i][0] = in0; _m[i][1] = in1; _m[i][2] = in2;
    }
    void row( int i, T in0, T in1, T in2, T in3 )
    {  
        _m[i][0] = in0; _m[i][1] = in1; _m[i][2] = in2; _m[i][3] = in3;
    }
    void set( 
        T in00, T in01, T in02, T in03,
        T in10, T in11, T in12, T in13,
        T in20, T in21, T in22, T in23,
        T in30, T in31, T in32, T in33 )
    {   
        row( 0, in00, in01, in02, in03 );
        row( 1, in10, in11, in12, in13 );
        row( 2, in20, in21, in22, in23 );
        row( 3, in30, in31, in32, in33 );
    }
    void set_submatrix(
        const matrix_4x4 & rhs ) 
    {   
        row( 0, rhs._m[0][0], rhs._m[0][1], rhs._m[0][2] );
        row( 1, rhs._m[1][0], rhs._m[1][1], rhs._m[1][2] );
        row( 2, rhs._m[2][0], rhs._m[2][1], rhs._m[2][2] );
    }
    void transpose_submatrix() 
    {   
        T m01 = _m[0][1];
        T m02 = _m[0][2];
        T m10 = _m[1][0];
        T m12 = _m[1][2];
        T m20 = _m[2][0];
        T m21 = _m[2][1];
        _m[1][0] = m01;
        _m[2][0] = m02;
        _m[0][1] = m10;
        _m[2][1] = m12;
        _m[0][2] = m20;
        _m[1][2] = m21;
    }
    void invert_submatrix()
    {
        // "Fast Inversion of Length- and Angle-Preserving Matrices"
        // by Kevin Wu, Kevin.Wu@eng.sun.com
        // in "Graphics Gems IV", Academic Press, 1994

        // Calculate the square of the isotropic scale factor
        T scale = _m[0][0] * _m[0][0]
                + _m[0][1] * _m[0][1]
                + _m[0][2] * _m[0][2];

        // Is the submatrix A singular?
        if ( scale == 0.0)
        {
            // Matrix M has no inverse
        /*
            ### DO SOMETHING ELSE
            fprintf (stderr, "angle_preserving_matrix4_inverse: singular matrix\n");
        */
            return;
        }
        // Calculate the inverse of the square of the isotropic scale factor
        scale = 1.0 / scale;

        // Transpose and scale the 3 by 3 upper-left submatrix
        T m00 = _m[0][0];
        T m01 = _m[0][1];
        T m02 = _m[0][2];
        T m10 = _m[1][0];
        T m11 = _m[1][1];
        T m12 = _m[1][2];
        T m20 = _m[2][0];
        T m21 = _m[2][1];
        T m22 = _m[2][2];
        _m[0][0] = scale * m00;
        _m[1][0] = scale * m01;
        _m[2][0] = scale * m02;
        _m[0][1] = scale * m10;
        _m[1][1] = scale * m11;
        _m[2][1] = scale * m12;
        _m[0][2] = scale * m20;
        _m[1][2] = scale * m21;
        _m[2][2] = scale * m22;

        // Calculate -(transpose(A) / s*s) C
        _m[0][3] = - ( _m[0][0] * _m[0][3] +
                       _m[0][1] * _m[1][3] +
                       _m[0][2] * _m[2][3] );
        _m[1][3] = - ( _m[1][0] * _m[0][3] +
                       _m[1][1] * _m[1][3] +
                       _m[1][2] * _m[2][3] );
        _m[2][3] = - ( _m[2][0] * _m[0][3] +
                       _m[2][1] * _m[1][3] +
                       _m[2][2] * _m[2][3] );

        // Fill in last row
        row( 3,  0,  0,  0,  1 );
    }

    // initializers
    void init_identity()
    {
        row( 0,  1,  0,  0,  0 );
        row( 1,  0,  1,  0,  0 );
        row( 2,  0,  0,  1,  0 );
        row( 3,  0,  0,  0,  1 );
    }
    void init_identity_3x3()
    {
        row( 0,  1,  0,  0 );
        row( 1,  0,  1,  0 );
        row( 2,  0,  0,  1 );
    }
    void init_projection_orthographic( 
        T left, T right, T bottom, T top, T front, T back )
    {
        /// @note this is pretty big to be inline
        vector delta( right - left, top - bottom, back - front );
        vector sum(   right + left, top + bottom, back + front );
        vector ratio( sum );
        ratio /= delta;
        vector tworatio( 2.0, 2.0, 2.0 );
        tworatio /= delta;
        row( 0, tworatio.x(),              0,              0,  0 );
        row( 1,            0,   tworatio.y(),              0,  0 );
    // @@@ make left-handed for now
    //  row( 2,            0,              0, - tworatio.z(),  0 );
        row( 2,            0,              0,   tworatio.z(),  0 );
        row( 3,  - ratio.x(),    - ratio.y(),    - ratio.z(),  1 );
    }
    void init_projection_perspective( 
        T left, T right, T bottom, T top, T front, T back )
    {
        /// @note this is pretty big to be inline
        vector delta( right - left, top - bottom, back - front );
        vector sum(   right + left, top + bottom, back + front );
        vector ratio( sum );
        ratio /= delta;
        T twofront = 2.0 * front;
        vector tworatio( twofront, twofront, twofront );
        tworatio /= delta;
        row( 0, tworatio.x(),              0,                   0,  0 );
        row( 1,            0,   tworatio.y(),                   0,  0 );
    // @@@ make left-handed for now
    //  row( 2,            0,              0,         - ratio.z(), -1 );
        row( 2,    ratio.x(),      ratio.y(),           ratio.z(),  1 );
        row( 3,            0,              0, - back*tworatio.z(),  0 );
    }
    void init_rotation( 
        const vector & in_vector,
        T in_radians ) // rotation about arbitrary axis
    {
        // note: this is pretty big to be inline
        vector v( in_vector );
        v.normalize();
        T x = v.x();
        T y = v.y();
        T z = v.z();
        T c = cos( in_radians );
        T s = sin( in_radians );
        T t = 1.0 - c;
        row( 0, t*x*x+c,   t*x*y+s*z, t*x*z-s*y, 0 );
        row( 1, t*x*y-s*z, t*y*y+c,   t*y*z+s*x, 0 );
        row( 2, t*x*z+s*y, t*y*z-s*x, t*z*z+c,   0 );
        row( 3, 0,         0,         0,         1 );
    }
    void init_scaling( T x, T y, T z )
    {
        row( 0,  x,  0,  0,  0 );
        row( 1,  0,  y,  0,  0 );
        row( 2,  0,  0,  z,  0 );
        row( 3,  0,  0,  0,  1 );
    }
    void init_translation( T x, T y, T z )
    {
        row( 0,  1,  0,  0,  0 );
        row( 1,  0,  1,  0,  0 );
        row( 2,  0,  0,  1,  0 );
        row( 3,  x,  y,  z,  1 );
    }
    void init_rotation_x( T in_radians ) 
    {   // facing +x, cw from +y axis to -z axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        row( 0,  1,  0,  0,  0 );
        row( 1,  0,  c, -s,  0 );
        row( 2,  0,  s,  c,  0 );
        row( 3,  0,  0,  0,  1 );
    }
    void init_rotation_y( T in_radians )
    {   // facing +y, cw from +z axis to -x axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        row( 0,  c,  0,  s,  0 );
        row( 1,  0,  1,  0,  0 );
        row( 2, -s,  0,  c,  0 );
        row( 3,  0,  0,  0,  1 );
    }
    void init_rotation_z( T in_radians )
    {   // facing +z, cw from +y axis to +x axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        row( 0,  c, -s,  0,  0 );
        row( 1,  s,  c,  0,  0 );
        row( 2,  0,  0,  1,  0 );
        row( 3,  0,  0,  0,  1 );
    }
    void init_alignment( 
        T x_radians, T y_radians, T z_radians )
    {
        // same order as Lightwave: bank, pitch, heading
        init_rotation_z( z_radians );
        rotate_x(       x_radians );
        rotate_y(       y_radians );
    }
    void init_alignment(
        const angles_rad & in_angles )
    {
        init_alignment( in_angles.x(), in_angles.y(), in_angles.z() );
    }
    /** set orientation using Gem (I) by Steve Cunningham
     *  "3D Viewing and Rotation Using Orthonormal Bases" */
    //@{
    void set_transform_basis_inverted( 
        const vector & in_local_x, 
        const vector & in_local_y,
        const vector & in_local_z )
    {
        row( 0,  in_local_x.x(), in_local_x.y(), in_local_x.z() );
        row( 1,  in_local_y.x(), in_local_y.y(), in_local_y.z() );
        row( 2,  in_local_z.x(), in_local_z.y(), in_local_z.z() );
    }
    void init_transform_basis_inverted( 
        const vector & in_local_x, 
        const vector & in_local_y,
        const vector & in_local_z )
    {
        row( 0,  in_local_x.x(), in_local_x.y(), in_local_x.z(), 0 );
        row( 1,  in_local_y.x(), in_local_y.y(), in_local_y.z(), 0 );
        row( 2,  in_local_z.x(), in_local_z.y(), in_local_z.z(), 0 );
        row( 3,  0,              0,              0,              1 );
    }
    void init_transform_basis( 
        const vector & in_local_x, 
        const vector & in_local_y,
        const vector & in_local_z )
    {
        row( 0,  in_local_x.x(), in_local_y.x(), in_local_z.x(), 0 );
        row( 1,  in_local_x.y(), in_local_y.y(), in_local_z.y(), 0 );
        row( 2,  in_local_x.z(), in_local_y.z(), in_local_z.z(), 0 );
        row( 3,  0,              0,              0,              1 );
    }
    void init_transform_basis( 
        const coordinates & in_center,
        const vector      & in_local_x, 
        const vector      & in_local_y,
        const vector      & in_local_z )
    {
        row( 0,  in_local_x.x(), in_local_y.x(), in_local_z.x(), 0 );
        row( 1,  in_local_x.y(), in_local_y.y(), in_local_z.y(), 0 );
        row( 2,  in_local_x.z(), in_local_y.z(), in_local_z.z(), 0 );
        row( 3,  - in_local_x.x() * in_center.x()
                 - in_local_x.y() * in_center.y()
                 - in_local_x.z() * in_center.z(), 
                 - in_local_y.x() * in_center.x()
                 - in_local_y.y() * in_center.y()
                 - in_local_y.z() * in_center.z(), 
                 - in_local_z.x() * in_center.x()
                 - in_local_z.y() * in_center.y()
                 - in_local_z.z() * in_center.z(), 
                 1 );
    }
    void init_transform_unit_cube( 
        const coordinates & in_center,
        const size &        in_size )
    {
        T xFactor = 1/in_size.x();
        T yFactor = 1/in_size.y();
        T zFactor = 1/in_size.z();
        row( 0,  xFactor,  0,        0,        0 );
        row( 1,  0,        yFactor,  0,        0 );
        row( 2,  0,        0,        zFactor,  0 );
        row( 3,  -in_center.x()*xFactor,
                 -in_center.y()*yFactor,
                 -in_center.z()*zFactor,        1 );
    }
    //@}
    void init_orient_towards(
        const coordinates & in_point,
        const vector &      in_up )
    {
        vector facing( in_point );
        facing.normalize(); // $$$
        vector right( in_up, facing ); // cross product
        vector up( facing, right );   // cross product
        init_transform_basis( right, up, facing );
    }
    void init_transform_unit_cube( 
        const vector & in_local_x, 
        const vector & in_local_y,
        const vector & in_local_z,
        const size   & in_size )
    {
        init_transform_basis( in_local_x, in_local_y, in_local_z );
        scale( 1/in_size.x(), 1/in_size.y(), 1/in_size.z() );
    }
    /** !!! alternate version that only scales the translation
     *  !!! maybe this should be the only version */
    void init_transform_unit_cube( 
        const coordinates & in_center,
        const vector      & in_local_x, 
        const vector      & in_local_y,
        const vector      & in_local_z,
        const size        & in_size )
    {
        init_transform_basis( in_center, in_local_x, in_local_y, in_local_z );
        scale_translation( 1/in_size.x(), 1/in_size.y(), 1/in_size.z() );
    }
    void init_transform_unit_cube_scale_all( 
        const coordinates & in_center,
        const vector      & in_local_x, 
        const vector      & in_local_y,
        const vector      & in_local_z,
        const size        & in_size )
    {
        init_transform_basis( in_center, in_local_x, in_local_y, in_local_z );
        scale( 1/in_size.x(), 1/in_size.y(), 1/in_size.z() );
    }
    void set_translation( vector v )
    {
        row( 3, v.x(), v.y(), v.z() );
    }
    /// @name concatenating operations
    /** from Gems (I) by by Joseph M. Cychosz, Purdue University
     * "Efficient Post-Concatenation of Transformation Matrices" */
    //@{
    matrix_4x4 & rotate_x( T in_radians )
    {   // facing +x, cw from +y axis to -z axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        for ( int i = 0 ; i < 4 ; i++ )
        {
            T t = _m[i][1];
            _m[i][1] = t * c + _m[i][2] * s;
            _m[i][2] = _m[i][2] * c - t * s;
        }
        return *this;
    }
    matrix_4x4 & rotate_y( T in_radians )
    {   // facing +y, cw from +z axis to -x axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        for ( int i = 0 ; i < 4 ; i++ )
        {
            T t = _m[i][0];
            _m[i][0] = t * c - _m[i][2] * s;
            _m[i][2] = t * s + _m[i][2] * c;
        }
        return *this;
    }
    matrix_4x4 & rotate_z( T in_radians )
    {   // facing +z, cw from +y axis to +x axis
        T c = cos( in_radians );
        T s = sin( in_radians );
        for ( int i = 0 ; i < 4 ; i++ )
        {
            T t = _m[i][0];
            _m[i][0] = t * c + _m[i][1] * s;
            _m[i][1] = _m[i][1] * c - t * s;
        }
        return *this;
    }
    matrix_4x4 & scale_orientation( T inXfactor, T inYfactor, T inZfactor )
    {
        _m[0][0] *= inXfactor; _m[0][1] *= inYfactor;   _m[0][2] *= inZfactor;
        _m[1][0] *= inXfactor; _m[1][1] *= inYfactor;   _m[1][2] *= inZfactor;
        _m[2][0] *= inXfactor; _m[2][1] *= inYfactor;   _m[2][2] *= inZfactor;
        return *this;
    }
    matrix_4x4 & scale_translation( T inXfactor, T inYfactor, T inZfactor )
    {
        _m[3][0] *= inXfactor; _m[3][1] *= inYfactor;   _m[3][2] *= inZfactor;
        return *this;
    }
    matrix_4x4 & scale( T inXfactor, T inYfactor, T inZfactor )
    {
        scale_orientation( inXfactor, inYfactor, inZfactor );
        scale_translation( inXfactor, inYfactor, inZfactor );
        return *this;
    }
    matrix_4x4 & translate( T x, T y, T z )
    {
        _m[0][0] += _m[0][3]*x; _m[0][1] += _m[0][3]*y; _m[0][2] += _m[0][3]*z;
        _m[1][0] += _m[1][3]*x; _m[1][1] += _m[1][3]*y; _m[1][2] += _m[1][3]*z;
        _m[2][0] += _m[2][3]*x; _m[2][1] += _m[2][3]*y; _m[2][2] += _m[2][3]*z;
        _m[3][0] += _m[3][3]*x; _m[3][1] += _m[3][3]*y; _m[3][2] += _m[3][3]*z;
        return *this;
    }
    matrix_4x4 & perspective( T inDistance )
    {
        T f = 1 / inDistance;
        _m[0][3] += _m[0][2]*f; _m[0][2] = 0;
        _m[1][3] += _m[1][2]*f; _m[1][2] = 0;
        _m[2][3] += _m[2][2]*f; _m[2][2] = 0;
        _m[3][3] += _m[3][2]*f; _m[3][2] = 0;
        return *this;
    }
    //@}

    matrix_4x4 & operator *= ( const matrix_4x4 & rhs )
    {   return multiply( rhs ); }

    matrix_4x4 & multiply( const matrix_4x4 & rhs ) // 64 multiplies, 48 adds
    {
        row( 0, _m[0][0]*rhs._m[0][0] + _m[0][1]*rhs._m[1][0] + _m[0][2]*rhs._m[2][0] + _m[0][3]*rhs._m[3][0],
                _m[0][0]*rhs._m[0][1] + _m[0][1]*rhs._m[1][1] + _m[0][2]*rhs._m[2][1] + _m[0][3]*rhs._m[3][1],
                _m[0][0]*rhs._m[0][2] + _m[0][1]*rhs._m[1][2] + _m[0][2]*rhs._m[2][2] + _m[0][3]*rhs._m[3][2],
                _m[0][0]*rhs._m[0][3] + _m[0][1]*rhs._m[1][3] + _m[0][2]*rhs._m[2][3] + _m[0][3]*rhs._m[3][3]
            );
        row( 1, _m[1][0]*rhs._m[0][0] + _m[1][1]*rhs._m[1][0] + _m[1][2]*rhs._m[2][0] + _m[1][3]*rhs._m[3][0],
                _m[1][0]*rhs._m[0][1] + _m[1][1]*rhs._m[1][1] + _m[1][2]*rhs._m[2][1] + _m[1][3]*rhs._m[3][1],
                _m[1][0]*rhs._m[0][2] + _m[1][1]*rhs._m[1][2] + _m[1][2]*rhs._m[2][2] + _m[1][3]*rhs._m[3][2],
                _m[1][0]*rhs._m[0][3] + _m[1][1]*rhs._m[1][3] + _m[1][2]*rhs._m[2][3] + _m[1][3]*rhs._m[3][3]
            );
        row( 2, _m[2][0]*rhs._m[0][0] + _m[2][1]*rhs._m[1][0] + _m[2][2]*rhs._m[2][0] + _m[2][3]*rhs._m[3][0],
                _m[2][0]*rhs._m[0][1] + _m[2][1]*rhs._m[1][1] + _m[2][2]*rhs._m[2][1] + _m[2][3]*rhs._m[3][1],
                _m[2][0]*rhs._m[0][2] + _m[2][1]*rhs._m[1][2] + _m[2][2]*rhs._m[2][2] + _m[2][3]*rhs._m[3][2],
                _m[2][0]*rhs._m[0][3] + _m[2][1]*rhs._m[1][3] + _m[2][2]*rhs._m[2][3] + _m[2][3]*rhs._m[3][3]
            );
        row( 3, _m[3][0]*rhs._m[0][0] + _m[3][1]*rhs._m[1][0] + _m[3][2]*rhs._m[2][0] + _m[3][3]*rhs._m[3][0],
                _m[3][0]*rhs._m[0][1] + _m[3][1]*rhs._m[1][1] + _m[3][2]*rhs._m[2][1] + _m[3][3]*rhs._m[3][1],
                _m[3][0]*rhs._m[0][2] + _m[3][1]*rhs._m[1][2] + _m[3][2]*rhs._m[2][2] + _m[3][3]*rhs._m[3][2],
                _m[3][0]*rhs._m[0][3] + _m[3][1]*rhs._m[1][3] + _m[3][2]*rhs._m[2][3] + _m[3][3]*rhs._m[3][3]
            );
        return *this;
    }

    matrix_4x4 & multiply( T rhs00, T rhs01, T rhs02, // 36 multiplies, 24 adds
                          T rhs10, T rhs11, T rhs12,
                          T rhs20, T rhs21, T rhs22 )
    {
        row( 0, _m[0][0]*rhs00 + _m[0][1]*rhs10 + _m[0][2]*rhs20,
                _m[0][0]*rhs01 + _m[0][1]*rhs11 + _m[0][2]*rhs21,
                _m[0][0]*rhs02 + _m[0][1]*rhs12 + _m[0][2]*rhs22
            );
        row( 1, _m[1][0]*rhs00 + _m[1][1]*rhs10 + _m[1][2]*rhs20,
                _m[1][0]*rhs01 + _m[1][1]*rhs11 + _m[1][2]*rhs21,
                _m[1][0]*rhs02 + _m[1][1]*rhs12 + _m[1][2]*rhs22
            );
        row( 2, _m[2][0]*rhs00 + _m[2][1]*rhs10 + _m[2][2]*rhs20,
                _m[2][0]*rhs01 + _m[2][1]*rhs11 + _m[2][2]*rhs21,
                _m[2][0]*rhs02 + _m[2][1]*rhs12 + _m[2][2]*rhs22 
            );
        row( 3, _m[3][0]*rhs00 + _m[3][1]*rhs10 + _m[3][2]*rhs20,
                _m[3][0]*rhs01 + _m[3][1]*rhs11 + _m[3][2]*rhs21,
                _m[3][0]*rhs02 + _m[3][1]*rhs12 + _m[3][2]*rhs22
            );
        return *this;
    }

    void transform( coordinates & c ) const
    {
        c.set( _m[0][0]*c.x() + _m[1][0]*c.y() + _m[2][0]*c.z() + _m[3][0],
               _m[0][1]*c.x() + _m[1][1]*c.y() + _m[2][1]*c.z() + _m[3][1],
               _m[0][2]*c.x() + _m[1][2]*c.y() + _m[2][2]*c.z() + _m[3][2] );
    }
    void transform( T & x, T & y, T & z ) const
    {
        T nx = _m[0][0]*x + _m[1][0]*y + _m[2][0]*z + _m[3][0];
        T ny = _m[0][1]*x + _m[1][1]*y + _m[2][1]*z + _m[3][1];
        T nz = _m[0][2]*x + _m[1][2]*y + _m[2][2]*z + _m[3][2];
        x = nx;
        y = ny;
        z = nz;
    }
    void transform( T & x, T & y, T & z, T & w ) const
    {
        T nx = _m[0][0]*x + _m[1][0]*y + _m[2][0]*z + _m[3][0];
        T ny = _m[0][1]*x + _m[1][1]*y + _m[2][1]*z + _m[3][1];
        T nz = _m[0][2]*x + _m[1][2]*y + _m[2][2]*z + _m[3][2];
        T nw = _m[0][3]*x + _m[1][3]*y + _m[2][3]*z + _m[3][3];
        x = nx;
        y = ny;
        z = nz;
        w = nw;
    }

    /// @name pre-concatenation operations @@@ refactor for efficiency 
    //@{
    matrix_4x4 & pre_multiply( const matrix_4x4 & rhs ) // 64 multiplies, 48 adds
    {
#if 0 // @@@ FIGURE THIS OUT
        row( 0, _m[0][0]*rhs._m[0][0] + _m[0][1]*rhs._m[1][0] + _m[0][2]*rhs._m[2][0] + _m[0][3]*rhs._m[3][0],
                _m[0][0]*rhs._m[0][1] + _m[0][1]*rhs._m[1][1] + _m[0][2]*rhs._m[2][1] + _m[0][3]*rhs._m[3][1],
                _m[0][0]*rhs._m[0][2] + _m[0][1]*rhs._m[1][2] + _m[0][2]*rhs._m[2][2] + _m[0][3]*rhs._m[3][2],
                _m[0][0]*rhs._m[0][3] + _m[0][1]*rhs._m[1][3] + _m[0][2]*rhs._m[2][3] + _m[0][3]*rhs._m[3][3]
            );
        row( 1, _m[1][0]*rhs._m[0][0] + _m[1][1]*rhs._m[1][0] + _m[1][2]*rhs._m[2][0] + _m[1][3]*rhs._m[3][0],
                _m[1][0]*rhs._m[0][1] + _m[1][1]*rhs._m[1][1] + _m[1][2]*rhs._m[2][1] + _m[1][3]*rhs._m[3][1],
                _m[1][0]*rhs._m[0][2] + _m[1][1]*rhs._m[1][2] + _m[1][2]*rhs._m[2][2] + _m[1][3]*rhs._m[3][2],
                _m[1][0]*rhs._m[0][3] + _m[1][1]*rhs._m[1][3] + _m[1][2]*rhs._m[2][3] + _m[1][3]*rhs._m[3][3]
            );
        row( 2, _m[2][0]*rhs._m[0][0] + _m[2][1]*rhs._m[1][0] + _m[2][2]*rhs._m[2][0] + _m[2][3]*rhs._m[3][0],
                _m[2][0]*rhs._m[0][1] + _m[2][1]*rhs._m[1][1] + _m[2][2]*rhs._m[2][1] + _m[2][3]*rhs._m[3][1],
                _m[2][0]*rhs._m[0][2] + _m[2][1]*rhs._m[1][2] + _m[2][2]*rhs._m[2][2] + _m[2][3]*rhs._m[3][2],
                _m[2][0]*rhs._m[0][3] + _m[2][1]*rhs._m[1][3] + _m[2][2]*rhs._m[2][3] + _m[2][3]*rhs._m[3][3]
            );
        row( 3, _m[3][0]*rhs._m[0][0] + _m[3][1]*rhs._m[1][0] + _m[3][2]*rhs._m[2][0] + _m[3][3]*rhs._m[3][0],
                _m[3][0]*rhs._m[0][1] + _m[3][1]*rhs._m[1][1] + _m[3][2]*rhs._m[2][1] + _m[3][3]*rhs._m[3][1],
                _m[3][0]*rhs._m[0][2] + _m[3][1]*rhs._m[1][2] + _m[3][2]*rhs._m[2][2] + _m[3][3]*rhs._m[3][2],
                _m[3][0]*rhs._m[0][3] + _m[3][1]*rhs._m[1][3] + _m[3][2]*rhs._m[2][3] + _m[3][3]*rhs._m[3][3]
            );
#else
        matrix_4x4<T> matrhs( rhs );
        matrhs *= *this;
        *this = matrhs;
#endif
        return *this;
    }
    void pre_orient(
        const vector & in_local_x, 
        const vector & in_local_y,
        const vector & in_local_z )
    {
        matrix_4x4<T> morientation( atoms::no_init );
        morientation.init_transform_basis_inverted(
            in_local_x, in_local_y, in_local_z );
        *this *= morientation;
    }
    void pre_scale( const vector & in_scaling )
    {
        matrix_4x4<T> mscaling( atoms::no_init );
        mscaling.init_scaling( in_scaling.x(), in_scaling.y(), in_scaling.z() );
        mscaling.multiply( *this );
        *this = mscaling;
    }
    void pre_translate( const vector & in_translation )
    {
        matrix_4x4<T> mtranslation( atoms::no_init );
        mtranslation.init_translation( in_translation.x(), in_translation.y(), in_translation.z() );
        mtranslation.multiply( *this );
        *this = mtranslation;
    }
    //@}

    /// @name comparison operators
    //@{
    int operator ==( const matrix_4x4 & rhs ) const
    {
        for (     int row = 0 ; row < 4 ; row++ )
            for ( int col = 0 ; col < 4 ; col++ )
                if ( _m[row][col] != rhs._m[row][col] )
                    return false;
        return true;
    }
    int operator !=( const matrix_4x4 & rhs ) const
    {
        return !(*this == rhs );
    }
    //@}
    
private:

    row_type _m[4];
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_MATRIX
