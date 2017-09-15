//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       cuboid.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/cuboid.hpp> // this header

#include <atoms/stream_string.hpp>
#include <geometry/matrix.hpp>
#include <geometry/pcube.hpp> // Green & Hatch "Fast Polygon-Cube Intersection"

namespace geometry
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_ret_flags(
    const cuboid & rhs )
{
    int flags = set_center_ret_flags(   rhs.get_center() );
    flags    |= set_right_ret_flags(    rhs.get_right() );
    flags    |= set_up_ret_flags(       rhs.get_up() );
    flags    |= set_facing_ret_flags(   rhs.get_facing() );
    flags    |= set_size_ret_flags(     rhs.get_size() );
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_center_ret_flags(
    T x, T y, T z )
{
    int flags = 0;
    if ( x != _center.x() )
    {
        flags |= (attribute_center | attribute_center_x);
    }
    if ( y != _center.y() )
    {
        flags |= (attribute_center | attribute_center_y);
    }
    if ( z != _center.z() )
    {
        flags |= (attribute_center | attribute_center_z);
    }
    if ( flags != 0 )
    {
        _cuboid_aligned.translate( 
            x-_center.x(), y-_center.y(), z-_center.z() );
        _center.set( x, y, z );
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_right_ret_flags(
    T x, T y, T z )
{
    int flags = 0;
    if ( x != _right.x() )
    {
        flags |= (attribute_right | attribute_right_x);
    }
    if ( y != _right.y() )
    {
        flags |= (attribute_right | attribute_right_y);
    }
    if ( z != _right.z() )
    {
        flags |= (attribute_right | attribute_right_z);
    }
    if ( flags != 0 )
    {
        _right.set( x, y, z );
        calculate_cuboid_aligned();
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_up_ret_flags(
    T x, T y, T z )
{
    int flags = 0;
    if ( x != _up.x() )
    {
        flags |= (attribute_up | attribute_up_x);
    }
    if ( y != _up.y() )
    {
        flags |= (attribute_up | attribute_up_y);
    }
    if ( z != _up.z() )
    {
        flags |= (attribute_up | attribute_up_z);
    }
    if ( flags != 0 )
    {
        _up.set( x, y, z );
        calculate_cuboid_aligned();
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_facing_ret_flags(
    T x, T y, T z )
{
    int flags = 0;
    if ( x != _facing.x() )
    {
        flags |= (attribute_facing | attribute_facing_x);
    }
    if ( y != _facing.y() )
    {
        flags |= (attribute_facing | attribute_facing_y);
    }
    if ( z != _facing.z() )
    {
        flags |= (attribute_facing | attribute_facing_z);
    }
    if ( flags != 0 )
    {
        _facing.set( x, y, z );
        calculate_cuboid_aligned();
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::set_size_ret_flags(
    T x, T y, T z )
{
    int flags = 0;
    if ( x != _size.x() )
    {
        flags |= (attribute_size | attribute_size_x);
    }
    if ( y != _size.y() )
    {
        flags |= (attribute_size | attribute_size_y);
    }
    if ( z != _size.z() )
    {
        flags |= (attribute_size | attribute_size_z);
    }
    if ( flags != 0 )
    {
        _size.set( x, y, z );
        calculate_cuboid_aligned();
        _radius_squared = -1;
        _radius = -1;
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::translate_ret_flags(
    const position & in_displacement )
{
    int flags = 0;
    if ( in_displacement.x() != 0 )
    {
        flags |= (attribute_center | attribute_center_x);
    }
    if ( in_displacement.y() != 0 )
    {
        flags |= (attribute_center | attribute_center_y);
    }
    if ( in_displacement.z() != 0 )
    {
        flags |= (attribute_center | attribute_center_z);
    }
    if ( flags != 0 )
    {
        translate( in_displacement );
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
void
cuboid<T>::change_basis(
const cuboid & in_cuboid )
{
    // using Gem (I) by Steve Cunningham
    // "3D Viewing and Rotation Using Orthonormal Bases"
    matrix m(
        in_cuboid.get_right().x(), in_cuboid.get_up().x(), in_cuboid.get_facing().x(), 0,
        in_cuboid.get_right().y(), in_cuboid.get_up().y(), in_cuboid.get_facing().y(), 0,
        in_cuboid.get_right().z(), in_cuboid.get_up().z(), in_cuboid.get_facing().z(), 0 );
    _center -= in_cuboid.get_center();
    m.transform( _center );
    m.transform( _right  );
    m.transform( _up     );
    m.transform( _facing );
    calculate_cuboid_aligned();
}

//--------------------------------------

template <class T>
void
cuboid<T>::transform_to_basis(
    const cuboid & in_cuboid )
{
    // using Gem (I) by Steve Cunningham
    // "3D Viewing and Rotation Using Orthonormal Bases"
    matrix m( no_init );
    m.init_transform_basis_inverted(
        in_cuboid.get_right(), in_cuboid.get_up(), in_cuboid.get_facing() );
    m.transform( _center );
    m.transform( _right  );
    m.transform( _up     );
    m.transform( _facing );
    _center += in_cuboid.get_center();
    calculate_cuboid_aligned();
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::expand_to_enclose_cuboid(
    const cuboid & in_cuboid,
    position *  inout_center_offset )
{
    // @@@ REFACTOR SOMEDAY!
    // @@@ BEGIN SECTION BLOCK COPIED FROM intersects_unit_cube BELOW

    // setup the cuboid vectors
    // (cost == ?)
    vector c( in_cuboid.get_center() );
    vector r( in_cuboid.get_right()  );
    vector u( in_cuboid.get_up()     );
    vector f( in_cuboid.get_facing() );
    r *= (in_cuboid.get_size().x() * 0.5);
    u *= (in_cuboid.get_size().y() * 0.5);
    f *= (in_cuboid.get_size().z() * 0.5);

    // generate vertices for this cuboid
    position verts[8] =
    {
        position( (c.x()-r.x()+u.x()+f.x()), (c.y()-r.y()+u.y()+f.y()), (c.z()-r.z()+u.z()+f.z()) ),
        position( (c.x()-r.x()+u.x()-f.x()), (c.y()-r.y()+u.y()-f.y()), (c.z()-r.z()+u.z()-f.z()) ),
        position( (c.x()+r.x()+u.x()-f.x()), (c.y()+r.y()+u.y()-f.y()), (c.z()+r.z()+u.z()-f.z()) ),
        position( (c.x()+r.x()+u.x()+f.x()), (c.y()+r.y()+u.y()+f.y()), (c.z()+r.z()+u.z()+f.z()) ),
        position( (c.x()-r.x()-u.x()+f.x()), (c.y()-r.y()-u.y()+f.y()), (c.z()-r.z()-u.z()+f.z()) ),
        position( (c.x()-r.x()-u.x()-f.x()), (c.y()-r.y()-u.y()-f.y()), (c.z()-r.z()-u.z()-f.z()) ),
        position( (c.x()+r.x()-u.x()-f.x()), (c.y()+r.y()-u.y()-f.y()), (c.z()+r.z()-u.z()-f.z()) ),
        position( (c.x()+r.x()-u.x()+f.x()), (c.y()+r.y()-u.y()+f.y()), (c.z()+r.z()-u.z()+f.z()) )
    };
    // @@@ END SECTION BLOCK COPIED

    // !!! similar logic to polygon_form_element::calculate_center_and_size

    size halfsize( _size );
    halfsize *= 0.5;
    position max(  halfsize );
    position min( -halfsize );
    boolean keepcenter = (inout_center_offset == 0);
    if ( ! keepcenter )
    {       
        max += *inout_center_offset;
        min += *inout_center_offset;
    }
    for ( whole v = 0; v < 8; v++ )
    {
        const position & pos = verts[v];
        if ( pos.x() < min.x() )
        {
            min.x( pos.x() );
            if ( keepcenter )
            {
                max.x( - max.x() );
            }
        }
        if ( pos.y() < min.y() )
        {
            min.y( pos.y() );
            if ( keepcenter )
            {
                max.y( - min.y() );
            }
        }
        if ( pos.z() < min.z() )
        {
            min.z( pos.z() );
            if ( keepcenter )
            {
                max.z( - min.z() );
            }
        }
        if ( pos.x() > max.x() )
        {
            max.x( pos.x() );
            if ( keepcenter )
            {
                min.x( - max.x() );
            }
        }
        if ( pos.y() > max.y() )
        {
            max.y( pos.y() );
            if ( keepcenter )
            {
                min.y( - max.y() );
            }
        }
        if ( pos.z() > max.z() )
        {
            max.z( pos.z() );
            if ( keepcenter )
            {
                min.z( - max.z() );
            }
        }
    }   
    size newsize( max - min );
    attribute_flag flags = set_size_ret_flags( newsize );
    if ( ! keepcenter )
    {
        position centeroffset( min + (_size * 0.5) );
        flags = attribute_flag(flags |
            translate_ret_flags( centeroffset ));
        *inout_center_offset = centeroffset;
    }
    return flags;
}

//--------------------------------------

template <class T>
boolean
cuboid<T>::intersects_unit_cube( 
    const position & inUnitCubePosition,
    const matrix   & inUnitCubeBasisTransformation ) const
{
    // setup the cuboid vectors
    // (cost == ?)
    vector c( _center );
    vector r( _right  );
    vector u( _up     );
    vector f( _facing );
    c -= inUnitCubePosition;
    r *= (_size.x() * 0.5);
    u *= (_size.y() * 0.5);
    f *= (_size.z() * 0.5);

    // generate vertices for this cuboid
    real v[8][3] =
    {
        { (c.x()-r.x()+u.x()+f.x()), (c.y()-r.y()+u.y()+f.y()), (c.z()-r.z()+u.z()+f.z()) },
        { (c.x()-r.x()+u.x()-f.x()), (c.y()-r.y()+u.y()-f.y()), (c.z()-r.z()+u.z()-f.z()) },
        { (c.x()+r.x()+u.x()-f.x()), (c.y()+r.y()+u.y()-f.y()), (c.z()+r.z()+u.z()-f.z()) },
        { (c.x()+r.x()+u.x()+f.x()), (c.y()+r.y()+u.y()+f.y()), (c.z()+r.z()+u.z()+f.z()) },
        { (c.x()-r.x()-u.x()+f.x()), (c.y()-r.y()-u.y()+f.y()), (c.z()-r.z()-u.z()+f.z()) },
        { (c.x()-r.x()-u.x()-f.x()), (c.y()-r.y()-u.y()-f.y()), (c.z()-r.z()-u.z()-f.z()) },
        { (c.x()+r.x()-u.x()-f.x()), (c.y()+r.y()-u.y()-f.y()), (c.z()+r.z()-u.z()-f.z()) },
        { (c.x()+r.x()-u.x()+f.x()), (c.y()+r.y()-u.y()+f.y()), (c.z()+r.z()-u.z()+f.z()) }
    };

    // apply unit cube transformation to vertices
    for ( whole i = 0; i < 8; i++ )
    {
        inUnitCubeBasisTransformation.transform( v[i][0], v[i][1], v[i][2] );
    }
    boolean isInside = true; // assume origin is inside

    switch( trivial_vertex_tests( 8, v, false, false ) )
    {
        case  0 : return false; // no intersection!
        case  1 : return true;  // yes, intersection!
        default : // == -1
        {   // check all edges of that cuboid
            if (   segment_intersects_cube( v[0], v[1] )
                || segment_intersects_cube( v[0], v[3] )
                || segment_intersects_cube( v[0], v[4] )
                || segment_intersects_cube( v[1], v[2] )
                || segment_intersects_cube( v[1], v[5] )
                || segment_intersects_cube( v[2], v[3] )
                || segment_intersects_cube( v[2], v[6] )
                || segment_intersects_cube( v[3], v[7] )
                || segment_intersects_cube( v[4], v[5] )
                || segment_intersects_cube( v[4], v[7] ) 
                || segment_intersects_cube( v[5], v[6] )
                || segment_intersects_cube( v[6], v[7] ) )
            {
                return true;
            }
            // check all faces of that cuboid
            real normal[3];
            {
                const real face[][3] =
                {
                    { v[3][0], v[3][1], v[3][2] },
                    { v[2][0], v[2][1], v[2][2] },
                    { v[1][0], v[1][1], v[1][2] },
                    { v[0][0], v[0][1], v[0][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[0][0])+(normal[1]*v[0][1])+(normal[2]*v[0][2])) < 0 )
                {
                    isInside = false;
                }
            }
            {
                const real face[][3] =
                {
                    { v[4][0], v[4][1], v[4][2] },
                    { v[5][0], v[5][1], v[5][2] },
                    { v[6][0], v[6][1], v[6][2] },
                    { v[7][0], v[7][1], v[7][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[6][0])+(normal[1]*v[6][1])+(normal[2]*v[6][2])) < 0 )
                {
                    isInside = false;
                }
            }
            {
                const real face[][3] =
                {
                    { v[0][0], v[0][1], v[0][2] },
                    { v[1][0], v[1][1], v[1][2] },
                    { v[5][0], v[5][1], v[5][2] },
                    { v[4][0], v[4][1], v[4][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[0][0])+(normal[1]*v[0][1])+(normal[2]*v[0][2])) < 0 )
                {
                    isInside = false;
                }
            }
            {
                const real face[][3] =
                {
                    { v[2][0], v[2][1], v[2][2] },
                    { v[3][0], v[3][1], v[3][2] },
                    { v[7][0], v[7][1], v[7][2] },
                    { v[6][0], v[6][1], v[6][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[6][0])+(normal[1]*v[6][1])+(normal[2]*v[6][2])) < 0 )
                {
                    isInside = false;
                }
            }
            {
                const real face[][3] =
                {
                    { v[0][0], v[0][1], v[0][2] },
                    { v[4][0], v[4][1], v[4][2] },
                    { v[7][0], v[7][1], v[7][2] },
                    { v[3][0], v[3][1], v[3][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[0][0])+(normal[1]*v[0][1])+(normal[2]*v[0][2])) < 0 )
                {
                    isInside = false;
                }
            }
            {
                const real face[][3] =
                {
                    { v[1][0], v[1][1], v[1][2] },
                    { v[2][0], v[2][1], v[2][2] },
                    { v[6][0], v[6][1], v[6][2] },
                    { v[5][0], v[5][1], v[5][2] },
                };               
                get_polygon_normal( normal, 4, face );
                if ( polygon_intersects_cube( 4, face, normal, true, true, false ) )
                {
                    return true;
                }
                // use dot product to determine if origin is inside side of cuboid
                if ( ((normal[0]*v[6][0])+(normal[1]*v[6][1])+(normal[2]*v[6][2])) < 0 )
                {
                    isInside = false;
                }
            }
            // final check for origin inside cuboid
            return isInside;
        }
    }
}

//--------------------------------------

template <class T>
boolean
cuboid<T>::intersects( 
    const cuboid<T>          & that,
    const geometry::matrix_4x4<T> * inUnitCubeVertexTransformation,
    const geometry::matrix_4x4<T> * inUnitCubeAxisTransformation ) const
{
/*
    ### DISABLE FOR NOW
    // create our own matrix if none provided
    geometry::matrix_4x4<T> theLocalVertexTransformation( no_init );
    geometry::matrix_4x4<T> theLocalAxisTransformation(   no_init );
    if (   (inUnitCubeVertexTransformation == 0)
        || (inUnitCubeAxisTransformation   == 0) )
    {
        that.makeUnitCubeMatrices( 
            theLocalVertexTransformation, theLocalAxisTransformation );
        inUnitCubeVertexTransformation = & theLocalVertexTransformation;
        inUnitCubeAxisTransformation   = & theLocalAxisTransformation;
    }
    return intersects_unit_cube( 
        *inUnitCubeVertexTransformation,
        *inUnitCubeAxisTransformation );
*/
    return false;
}

//--------------------------------------

template <class T>
integer 
cuboid<T>::side_of_plane( 
    const vector & n ) const
{
    // $$$ OPTIMIZE ALL OF THIS
    // cost == 36 multiplies, 88 adds,
    //         16 compares, 33 sets

    // generate corner vertices for this cuboid
    vector r( _right  );
    vector u( _up     );
    vector f( _facing );
    r *= _size.x() * 0.5; // $$$ INEFFICIENT
    u *= _size.y() * 0.5; // $$$ INEFFICIENT
    f *= _size.z() * 0.5; // $$$ INEFFICIENT

    const T v[][3] =
    {
        { _center.x()-r.x()-u.x()-f.x(),
          _center.y()+r.y()+u.y()+f.y(),
          _center.z()+r.z()+u.z()+f.z() },
        { _center.x()-r.x()-u.x()-f.x(),
          _center.y()+r.y()+u.y()+f.y(),
          _center.z()-r.z()-u.z()-f.z() },
        { _center.x()+r.x()+u.x()+f.x(),
          _center.y()+r.y()+u.y()+f.y(),
          _center.z()-r.z()-u.z()-f.z() },
        { _center.x()+r.x()+u.x()+f.x(),
          _center.y()+r.y()+u.y()+f.y(),
          _center.z()+r.z()+u.z()+f.z() },
        { _center.x()-r.x()-u.x()-f.x(),
          _center.y()-r.y()-u.y()-f.y(),
          _center.z()+r.z()+u.z()+f.z() },
        { _center.x()-r.x()-u.x()-f.x(),
          _center.y()-r.y()-u.y()-f.y(),
          _center.z()-r.z()-u.z()-f.z() },
        { _center.x()+r.x()+u.x()+f.x(),
          _center.y()-r.y()-u.y()-f.y(),
          _center.z()-r.z()-u.z()-f.z() },
        { _center.x()+r.x()+u.x()+f.x(),
          _center.y()-r.y()-u.y()-f.y(),
          _center.z()+r.z()+u.z()+f.z() }
    };

    boolean isPositive = false;
    boolean isNegative = false;
        
    for ( integer i = 0; i < 8; i++ )
    {
        T value = n.x()*v[i][0] + n.y()*v[i][1] + n.z()*v[i][2];
        if ( value > 0 )
        {
            isPositive = true;
        }
        else if ( value < 0 )
        {
            isNegative = true;
        }
    }
    if ( isPositive == isNegative )
    {
        return 0;
    }
    else
    {
        if ( isPositive )
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}       

//--------------------------------------
// internal methods
//--------------------------------------

template <class T>
void
cuboid<T>::calculate_cuboid_aligned()
{
    // Transforming Axis-Aligned Bounding Boxes
    // by Jim Arvo
    // from "Graphics Gems", Academic Press, 1990

    // Transforms a 3D axis-aligned cuboid via a 3x3 matrix
    // and returns an axis-aligned cuboid enclosing the result.

    matrix mat( no_init );
    mat.init_transform_basis( _right, _up, _facing );

    units origMax[3] =
    {
        _size.x() * 0.5, // $$$
        _size.y() * 0.5, // $$$
        _size.z() * 0.5  // $$$
    };
    units origMin[3] =
    {
        - origMax[0],
        - origMax[1],
        - origMax[2]
    };
    units newMin[3] = { _center.x(), _center.y(), _center.z() };
    units newMax[3] = { _center.x(), _center.y(), _center.z() };

    // Now find the extreme points by considering the product
    // of the min and max with each component of matrix
                     
    for ( int i = 0; i < 3; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            units a = mat[i][j] * origMin[j];
            units b = mat[i][j] * origMax[j];
            if ( a < b ) 
            { 
                newMin[i] += a; 
                newMax[i] += b;
            }
            else 
            { 
                newMin[i] += b; 
                newMax[i] += a;
            }
        }
    }
    _cuboid_aligned.set_minimumMaximum(
        newMin[0], newMin[1], newMin[2],
        newMax[0], newMax[1], newMax[2] );
}

//--------------------------------------

template <class T>
void
cuboid<T>::calculate_radius_squared() const
{
    // hypotenuse
    // cost = 4 multiplies, 2 additions, 1 set
    _radius_squared = 0.25 *
        (  (_size.x() * _size.x())
         + (_size.y() * _size.y())
         + (_size.z() * _size.z()));
}

//--------------------------------------

template <class T>
void
cuboid<T>::calculate_radius() const
{
    if ( _radius_squared < 0 ) // lazy evaluation
    {
        calculate_radius_squared();
    }
    // cost == 1 square root
    _radius = sqrt( _radius_squared );
}

//--------------------------------------

template <class T>
void
cuboid<T>::internal_rotate_global(
    units   in_x_radians,
    units   in_y_radians,
    units   in_z_radians,
    boolean in_do_set_alignment )
{
    // rotate Z--X--Y (same order as Lightwave)
    matrix m( no_init );
    m.init_alignment( in_x_radians, in_y_radians, in_z_radians );
    if ( in_do_set_alignment )
    {
        _right  = vector::axis_x;
        _up     = vector::axis_y;
        _facing = vector::axis_z;
    }
    else
    {
        m.transform( _center );
    }
    m.transform( _right  );
    m.transform( _up     );
    m.transform( _facing );
    calculate_cuboid_aligned();
}

//--------------------------------------

template <class T>
typename cuboid<T>::attribute_flag
cuboid<T>::internal_rotate_global_ret_flags(
    units   in_x_radians,
    units   in_y_radians,
    units   in_z_radians,
    boolean in_do_set_alignment )
{
    // rotate Z--X--Y (same order as Lightwave)
    matrix m( no_init );
    m.init_alignment( in_x_radians, in_y_radians, in_z_radians );
    vector right(   in_do_set_alignment ? vector::axis_x : _right );
    vector up(      in_do_set_alignment ? vector::axis_y : _up );
    vector facing(  in_do_set_alignment ? vector::axis_z : _facing );
    m.transform( right  );
    m.transform( up     );
    m.transform( facing );

    int centerflags = 0;
    if ( ! in_do_set_alignment )
    {
        vector center( _center );
        m.transform( center );
        if ( center.x() != _center.x() )
        {
            centerflags |= (attribute_center | attribute_center_x);
        }
        if ( center.y() != _center.y() )
        {
            centerflags |= (attribute_center | attribute_center_y);
        }
        if ( center.z() != _center.z() )
        {
            centerflags |= (attribute_center | attribute_center_z);
        }
        if ( centerflags != 0 )
        {
            _center = center;
        }
    }
    int rightflags = 0;
    if ( right.x() != _right.x() )
    {
        rightflags |= (attribute_right | attribute_right_x);
    }
    if ( right.y() != _right.y() )
    {
        rightflags |= (attribute_right | attribute_right_y);
    }
    if ( right.z() != _right.z() )
    {
        rightflags |= (attribute_right | attribute_right_z);
    }
    if ( rightflags != 0 )
    {
        _right = right;
    }
    int upflags = 0;
    if ( up.x() != _up.x() )
    {
        upflags |= (attribute_up | attribute_up_x);
    }
    if ( up.y() != _up.y() )
    {
        upflags |= (attribute_up | attribute_up_y);
    }
    if ( up.z() != _up.z() )
    {
        upflags |= (attribute_up | attribute_up_z);
    }
    if ( upflags != 0 )
    {
        _up = up;
    } 
    int facingflags = 0;
    if ( facing.x() != _facing.x() )
    {
        facingflags |= (attribute_facing | attribute_facing_x);
    }
    if ( facing.y() != _facing.y() )
    {
        facingflags |= (attribute_facing | attribute_facing_y);
    }
    if ( facing.z() != _facing.z() )
    {
        facingflags |= (attribute_facing | attribute_facing_z);
    }
    if ( facingflags != 0 )
    {
        _facing = facing;
    }
    int flags = centerflags | rightflags | upflags | facingflags;
    if ( flags != 0 )
    {
        calculate_cuboid_aligned();
    }
    return attribute_flag(flags);
}

//--------------------------------------

template <class T>
stringex
cuboid<T>::make_formatted_string(
    boolean in_cdl_format ) const
{
    stream_string_o sso;
    sso << "center="            << _center.make_formatted_string( in_cdl_format )
        << ",size="             <<   _size.make_formatted_string( in_cdl_format )
        << ",right="            <<  _right.make_formatted_string( in_cdl_format )
        << ",up="               <<     _up.make_formatted_string( in_cdl_format )
        << ",facing="           << _facing.make_formatted_string( in_cdl_format )
        << ",aligned="          << "@@@???@@@"
        << ",radius_squared="   << _radius_squared
        << ",radius="           << _radius;
    return sso.str();
}

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
