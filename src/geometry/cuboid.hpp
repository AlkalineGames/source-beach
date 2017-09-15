#if !defined(BEACH_GEOMETRY_CUBOID)
#define      BEACH_GEOMETRY_CUBOID
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       cuboid.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <geometry/angles.hpp>
#include <geometry/cuboid_aligned.hpp>
#include <geometry/matrix.hpp>
#include <geometry/vector.hpp>

namespace geometry
{
    using atoms::boolean;
    using atoms::integer;
    using atoms::no_init;
    using atoms::no_init_type;

//--------------------------------------

/// 3-D cuboid
/**
 *  A cuboid is defined by a center coordinate relative to 
 *  some external frame of reference, orientation vectors
 *  that are relative to the center (as origin) for each 
 *  side of the cuboid (only three vectors are needed to be
 *  defined since the other three vectors (for 6 sides)
 *  are implied to exist in the opposing directions),
 *  and a size.
 *
 *  WARNING: Orthogonal vectors are assumed but not
 *  enforced. Supplying non-orthogonal vectors will
 *  produce erroneous geometryematical results.
 * 
 *  Also, a radius value (scalar) is provided that
 *  defines the bounding sphere of the cuboid. This value
 *  is used as the first step in intersection tests so
 *  that subsequent expensive calculations can be avoided.
 *
 *  Additionally, the extent (maximum and minimum) values
 *  of the axis-aligned cuboid that bounds this cuboid are
 *  provided and recalculated on every state change. This
 *  is used as the second step in intersection tests so
 *  that subsequent expensive calculations can be avoided.
 */      
template <class T>
class cuboid
{
public:

    typedef T                           units;
    typedef geometry::radians_xyz<T>    angles_rad;
    typedef geometry::cuboid_aligned<T> cuboid_aligned;
    typedef geometry::matrix_4x4<T>     matrix;
    typedef geometry::vector_xyz<T>     position;
    typedef geometry::vector_xyz<T>     size;
    typedef geometry::vector_xyz<T>     vector;

    enum attribute_flag ///< bitwise values can be combined
    { 
        no_attribute,
        attribute_center,
        attribute_center_x  = attribute_center      << 1,
        attribute_center_y  = attribute_center_x    << 1,
        attribute_center_z  = attribute_center_y    << 1,
        attribute_right     = attribute_center_z    << 1,
        attribute_right_x   = attribute_right       << 1,
        attribute_right_y   = attribute_right_x     << 1,
        attribute_right_z   = attribute_right_y     << 1,
        attribute_up        = attribute_right_z     << 1,
        attribute_up_x      = attribute_up          << 1,
        attribute_up_y      = attribute_up_x        << 1,
        attribute_up_z      = attribute_up_y        << 1,
        attribute_facing    = attribute_up_z        << 1,
        attribute_facing_x  = attribute_facing      << 1,
        attribute_facing_y  = attribute_facing_x    << 1,
        attribute_facing_z  = attribute_facing_y    << 1,
        attribute_size      = attribute_facing_z    << 1,
        attribute_size_x    = attribute_size        << 1,
        attribute_size_y    = attribute_size_x      << 1,
        attribute_size_z    = attribute_size_y      << 1
    };

    cuboid<T>( no_init_type )
      :
        _center(        no_init ),
        _right(         no_init ),
        _up(            no_init ),
        _facing(        no_init ),
        _size(          no_init ),
        _cuboid_aligned(   no_init )
    {}
    /// default creates cuboid of 1 unit radius around the origin
    cuboid(
        T cX = 0, T cY = 0, T cZ = 0,
        T rX = 1, T rY = 0, T rZ = 0,
        T uX = 0, T uY = 1, T uZ = 0,
        T fX = 0, T fY = 0, T fZ = 1,
        T sX = 1, T sY = 1, T sZ = 1 )
      :
        _center(            cX, cY, cZ ),
        _right(             rX, rY, rZ ),
        _up(                uX, uY, uZ ),
        _facing(            fX, fY, fZ ),
        _size(              sX, sY, sZ ),
        _radius_squared(    -1 ), ///< lazy evaluation
        _radius(            -1 )  ///< ...ditto...
    {
        calculate_cuboid_aligned();
    }
    cuboid( const position & in_center )
      :
        _center(            in_center ),
        _right(             1, 0, 0 ),
        _up(                0, 1, 0 ),
        _facing(            0, 0, 1 ),
        _size(              1, 1, 1 ),
        _radius_squared(    -1 ), ///< lazy evaluation
        _radius(            -1 )  ///< ...ditto...
    {
        calculate_cuboid_aligned();
    }
    cuboid(
        const position &    in_center,
        const vector &      in_right,
        const vector &      in_up,
        const vector &      in_facing, 
        const size &        in_size = size( 1, 1, 1 ) )
      :
        _center(            in_center ),
        _right(             in_right ),
        _up(                in_up ),
        _facing(            in_facing ),
        _size(              in_size ),
        _radius_squared(    -1 ), ///< lazy evaluation
        _radius(            -1 )  ///< ...ditto...
    {
        calculate_cuboid_aligned();
    }
    cuboid(
        const position &    in_center,
        const angles_rad &  in_alignment,
        const size &        in_size = size( 1, 1, 1 ) )
      :
        _center(            in_center ),
        _size(              in_size ),
        _radius_squared(    -1 ), ///< lazy evaluation
        _radius(            -1 )  ///< ...ditto...
    {
        set_alignment( in_alignment );
    }
    cuboid(
        const position &    in_center,
        const size &        in_size )
      :
        _center(            in_center ),
        _right(             1, 0, 0 ),
        _up(                0, 1, 0 ),
        _facing(            0, 0, 1 ),
        _size(              in_size ),
        _radius_squared(    -1 ), ///< lazy evaluation
        _radius(            -1 )  ///< ...ditto...
    {
        calculate_cuboid_aligned();
    }

    /// @name primary attributes
    //@{
    const position &        get_center()            const { return _center;         }
    const vector &          get_right()             const { return _right;          }  
    const vector &          get_up()                const { return _up;             }  
    const vector &          get_facing()            const { return _facing;         }  
    const size &            get_size()              const { return _size;           }
    const cuboid_aligned &  get_cuboid_aligned()    const { return _cuboid_aligned; }
    //@}

    /// @name calculated and cached attributes
    //@{
    T get_radius_squared() const
    {
        if ( _radius_squared < 0 ) // lazy evaluation
        {
            calculate_radius_squared();
        }
        return _radius_squared;
    }
    T get_radius() const ///< $$ expensive
    {
        if ( _radius < 0 ) // lazy evaluation
        {
            calculate_radius();
        }
        return _radius;
    }
    T get_radius_inner() const
    {
        if ( _size.x() <= _size.y() )
        {
            if ( _size.x() <= _size.z() )
            {
                return _size.x();
            }
        }
        if ( _size.y() <= _size.z() )
        {
            return _size.y();
        }
        return _size.z();
    }
    //@}

    /// @name validity
    //@{
    boolean is_valid() const
    {
        return _center      .is_valid()
            && _right       .is_valid()
            && _up          .is_valid()
            && _facing      .is_valid()
            && _size        .is_valid()
            && _cuboid_aligned .is_valid();
    }
    //@}

    /// @name mutators
    //@{
    attribute_flag set_ret_flags( const cuboid & );

    void set_center( const position & c )
    {
        _cuboid_aligned.translate( c-_center );
        _center = c;
    }
    void set_right(  const vector & r ) { _right  = r; calculate_cuboid_aligned(); }
    void set_up(     const vector & u ) { _up     = u; calculate_cuboid_aligned(); }
    void set_facing( const vector & f ) { _facing = f; calculate_cuboid_aligned(); }
    void set_size(   const size   & s ) { _size   = s; calculate_cuboid_aligned(); _radius_squared = -1; _radius = -1; }

    attribute_flag  set_center_ret_flags(   T x, T y, T z );
    attribute_flag  set_center_ret_flags(   const position & c )
    {
        return set_center_ret_flags( c.x(), c.y(), c.z() );
    }
    void            set_center(              T x, T y, T z )
    {
        _cuboid_aligned.translate(
            x-_center.x(), y-_center.y(), z-_center.z() );
        _center.set( x, y, z );
    }
    attribute_flag  set_right_ret_flags(    T x, T y, T z );
    attribute_flag  set_right_ret_flags(    const vector & r )
    {
        return set_right_ret_flags( r.x(), r.y(), r.z() );
    }
    void            set_right(               T x, T y, T z )
    {
        _right.set( x, y, z );
        calculate_cuboid_aligned();
    }
    attribute_flag  set_up_ret_flags(       T x, T y, T z );
    attribute_flag  set_up_ret_flags(       const vector & u )
    {
        return set_up_ret_flags( u.x(), u.y(), u.z() );
    }
    void            set_up(                  T x, T y, T z )
    {
        _up.set( x, y, z );
        calculate_cuboid_aligned();
    }
    attribute_flag  set_facing_ret_flags(   T x, T y, T z );
    attribute_flag  set_facing_ret_flags(   const vector & f )
    {
        return set_facing_ret_flags( f.x(), f.y(), f.z() );
    }
    void            set_facing(              T x, T y, T z )
    {
        _facing.set( x, y, z );
        calculate_cuboid_aligned();
    }
    attribute_flag  set_size_ret_flags(     T x, T y, T z );
    attribute_flag  set_size_ret_flags(     const size & s )
    {
        return set_size_ret_flags( s.x(), s.y(), s.z() );
    }
    void            set_size(                T x, T y, T z )
    {
        _size.set( x, y, z );
        calculate_cuboid_aligned();
        _radius_squared = -1;
        _radius = -1;
    }
    void set_all( 
        T cX, T cY, T cZ,
        T rX, T rY, T rZ,
        T uX, T uY, T uZ,
        T fX, T fY, T fZ,
        T sX, T sY, T sZ )
    {
        _center.set( cX, cY, cZ );
        _right .set( rX, rY, rZ );
        _up    .set( uX, uY, uZ );
        _facing.set( fX, fY, fZ );
        _size  .set( sX, sY, sZ );
        _radius_squared = -1;
        _radius = -1;
        calculate_cuboid_aligned();
    }
    void set_all( 
        const position & c,
        const vector   & r,
        const vector   & u,
        const vector   & f,
        const size     & s )
    {
        _center = c;
        _right  = r;
        _up     = u;
        _facing = f;
        _size   = s;
        _radius_squared = -1;
        _radius = -1;
        calculate_cuboid_aligned();
    }
    attribute_flag  set_alignment_ret_flags( T x, T y, T z )
    {
        return internal_rotate_global_ret_flags( x, y, z, true );
    }
    attribute_flag  set_alignment_ret_flags( const angles_rad & ar )
    {
        return set_alignment_ret_flags( ar.x(), ar.y(), ar.z() );
    }
    void            set_alignment(
        units x, units y, units z )
    {
        internal_rotate_global( x, y, z, true );
    }
    void            set_alignment(
        const angles_rad & ar )
    {
        set_alignment( ar.x(), ar.y(), ar.z() );
    }
    void set_orientation( 
        const vector & r,
        const vector & u,
        const vector & f )
    {
        _right  = r;
        _up     = u;
        _facing = f;
        calculate_cuboid_aligned();
    }
    void set_orientation( 
        const vector & u,
        const vector & f )
    {
        // cross product
        vector right( u, f );
        _right  = right;
        _up     = u;
        _facing = f;
        calculate_cuboid_aligned();
    }
    void normalize()
    {
        _right .normalize();
        _up    .normalize();
        _facing.normalize();
        calculate_cuboid_aligned();
    }
    //@}

    /// @name transformations
    //@{
    void            translate(
        const position & in_displacement )
    {
        _center += in_displacement;
        _cuboid_aligned.translate( in_displacement );
    }
    void            translate_local(
        const position & in_displacement )
    {
        position disp( in_displacement );
        matrix m( no_init );
        m.init_transform_basis_inverted(
            get_right(), get_up(), get_facing() );
        m.transform( disp );
        translate( disp );
    }
    attribute_flag  translate_ret_flags(
        const position & in_displacement );

    void            rotate_global(
        units x, units y, units z )
    {
        internal_rotate_global( x, y, z, false );
    }
    attribute_flag  rotate_global_ret_flags(
        units x, units y, units z )
    {
        return internal_rotate_global_ret_flags( x, y, z, false );
    }
    void rotate( const vector & inAxis, T inRadians )
    {   ///< rotation around local origin
        matrix m( inAxis, inRadians );
        m.transform( _right  );
        m.transform( _up     );
        m.transform( _facing );
        calculate_cuboid_aligned();
    }
    void rotate( typename vector::axis_enum in_axis, T inRadians )
    {   /// rotation around local origin
        matrix m( in_axis, inRadians );
        m.transform( _right  );
        m.transform( _up     );
        m.transform( _facing );
        calculate_cuboid_aligned();
    }
    void rotate( const matrix & inMatrix )
    {   /// rotation around local origin
        inMatrix.transform( _right  );
        inMatrix.transform( _up     );
        inMatrix.transform( _facing );
        calculate_cuboid_aligned();
    }
    void scale( const size & inFactor )
    {
        _size *= inFactor;
        calculate_cuboid_aligned();
    }
    /// transform this the same as transforming in_cuboid to the origin
    void change_basis( const cuboid & in_cuboid );

    /// transform this globally as if in_cuboid is a local coordinate system
    void transform_to_basis( const cuboid & in_cuboid );

#if 0 // ### THIS DOESN'T QUITE WORK RIGHT
    void face( const vector & in_direction )
    {
        units right_dot = _right.dot_product( in_direction );
        if ( right_dot > 0.5 )
        {
            _right = _up.cross_product( in_direction );
            _up    = in_direction.cross_product( _right );
        }
        else if ( right_dot < -0.5 )
        {
            _right =    _up.cross_product( in_direction );
            _up    = _right.cross_product( in_direction );
        }
        else
        {
            units up_dot = _up.dot_product( in_direction );
            if ( up_dot > 0 )
            {
                _up    = in_direction.cross_product( _right );
                _right = _up.cross_product( in_direction );
            }
            else
            {
                _up    = in_direction.cross_product( _right );
                _right = in_direction.cross_product( _up );
            }
        }
        _facing = in_direction;
    }
#endif

    attribute_flag expand_to_enclose_cuboid( ///< may change size
        const cuboid & in_cuboid,
        position *  inout_center_offset );
        ///< if not 0, actual center may be changed and offset is returned
    //@}

    /// @name geometry applications
    //@{
    void make_basis_change_matrix( matrix & out_matrix ) const
    {
        // using Gem (I) by Steve Cunningham
        // "3D Viewing and Rotation Using Orthonormal Bases"
        out_matrix.set( 
            _right.x(), _up.x(), _facing.x(), 0,
            _right.y(), _up.y(), _facing.y(), 0,
            _right.z(), _up.z(), _facing.z(), 0,
            - _right .x() * _center.x()
            - _right .y() * _center.y()
            - _right .z() * _center.z(),
            - _up    .x() * _center.x()
            - _up    .y() * _center.y()
            - _up    .z() * _center.z(),
            - _facing.x() * _center.x()
            - _facing.y() * _center.y()
            - _facing.z() * _center.z(),
            1 );
    }
    T calc_distance_center_to_radius_squared( const cuboid & rhs ) const
    {
        return _center.distance_squared( rhs._center ) - rhs.get_radius_squared();
    }
    T calc_distance_radius_to_radius_squared( const cuboid & rhs ) const
    {
        return calc_distance_center_to_radius_squared( rhs ) - get_radius_squared();
    }
    boolean intersects_unit_cube(
        const position &    in_unit_cube_translation,
        const matrix   &    in_transform_unit_cube_basisation ) const;

    boolean intersects( const cuboid<T> & that,
        const matrix *  in_unit_cube_vertex_transformation = 0,
        const matrix *  in_unit_cube_axis_transformation   = 0 ) const;
        
    /** determine which side of a plane the cuboid lies on
     *  returns: 1 == positive side, -1 == negative side, 0 == both */
    integer side_of_plane( const vector & in_normal ) const;
    //@}

    ///@ name conversions
    //@{ 
    stringex make_formatted_string( boolean in_cdl_format = false ) const;
    //@}

    int operator ==( const cuboid & rhs ) const
    {
         return (   (this->_center  == rhs._center)
                 && (this->_right   == rhs._right )
                 && (this->_up      == rhs._up )
                 && (this->_facing  == rhs._facing )
                 && (this->_size    == rhs._size ) );
    }
    int operator !=( const cuboid & rhs ) const
    {
        return ! operator==( rhs );
    }

private:

    void calculate_cuboid_aligned();
    void calculate_radius_squared() const;
    void calculate_radius()         const;

    void            internal_rotate_global(
        units           in_x_radians,
        units           in_y_radians,
        units           in_z_radians,
        boolean         in_do_set_alignment );

    attribute_flag  internal_rotate_global_ret_flags(
        units           in_x_radians,
        units           in_y_radians,
        units           in_z_radians,
        boolean         in_do_set_alignment );

    position        _center;
    vector          _right;
    vector          _up;
    vector          _facing;
    size            _size;
    cuboid_aligned  _cuboid_aligned;
    mutable T       _radius_squared;
    mutable T       _radius;
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_CUBOID
