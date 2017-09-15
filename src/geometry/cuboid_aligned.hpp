#if !defined(BEACH_GEOMETRY_CUBOID_ALIGNED)
#define      BEACH_GEOMETRY_CUBOID_ALIGNED
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       cuboid_aligned.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <geometry/vector.hpp>

namespace geometry
{
    using atoms::boolean;
    using atoms::integer;
    using atoms::whole;

//--------------------------------------

/// template for an axis-aligned cuboid
/**
 *  An axis-aligned cuboid is defined by
 *  minimum coordinate and a maximum coordinate.
 *
 *  Values such as center, size, and radius, are
 *  calculated when requested; making this object
 *  space efficient rather than execution efficient.
 */
template <class T>
class cuboid_aligned
{
public:

    typedef T                   units;
    typedef coordinates_xyz<T>  position;
    typedef coordinates_xyz<T>  size;
    typedef vector_xyz<T>       vector;

    cuboid_aligned<T>( atoms::no_init_type )
      :
        _minimum( atoms::no_init ),
        _maximum( atoms::no_init )
    {}
    /// default creates cuboid of 1 unit radius around the origin
    cuboid_aligned( 
        T minx = -1, T miny = -1, T minz = -1,
        T maxx =  1, T maxy =  1, T maxz =  1 )
      :
        _minimum( minx, miny, minz ),
        _maximum( maxx, maxy, maxz )
    {
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    cuboid_aligned( 
        const position & in_minimum,
        const position & in_maximum )
      :
        _minimum( in_minimum ),
        _maximum( in_maximum )
    {
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    cuboid_aligned( 
        const size & in_size )
      :
        _minimum( in_size * -0.5 ),
        _maximum( in_size *  0.5 )
    {}

    // comparisons
    //@{
    bool operator ==( const cuboid_aligned & rhs ) const
    {   return (_minimum == rhs._minimum) && (_maximum == rhs._maximum); } 

    bool operator !=( const cuboid_aligned & rhs ) const
    {   return (_minimum != rhs._minimum) || (_maximum != rhs._maximum); } 
    //@}

    /// @name primary attributes
    //@{
    const position & get_minimum() const { return _minimum; }
    const position & get_maximum() const { return _maximum; }
    //@}

    /// @name derived attributes
    //@{
    size get_size() const
    {
        // cost == 3 additions, 1 set
        return _maximum - _minimum;
    }
    size get_size_half() const
    {
        // cost == 3 multiplies, 3 additions, 1 set
        return get_size() * 0.5; // ### DOESN'T WORK FOR INTEGER units
    }
    position get_center() const
    {
        // cost == 3 multiplies, 6 additions, 1 set
        return _maximum - get_size_half();
    }
    units get_radius_squared() const
    {
        // cost == 6 multiplies, 8 additions, 2 sets
        size hypo( get_size_half() );
        return hypo.x()*hypo.x()
             + hypo.y()*hypo.y()
             + hypo.z()*hypo.z();
    }
    units get_radius() const
    {
        // cost == 1 square root, 6 multiplies, 8 additions, 2 sets
        return sqrt( get_radius_squared() );
    }
    //@}

    /// @name validity
    //@{
    boolean is_valid() const
    {
        return _minimum.is_valid()
            && _maximum.is_valid();
    }
    //@}

    /// @name mutators
    //@{
    void set_minimum( 
        T x, T y, T z )
    {
        _minimum.set( x, y, z );
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void set_minimum( 
        const position & in_minimum )
    {
        _minimum = in_minimum;
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void set_maximum( 
        T x, T y, T z )
    {
        _maximum.set( x, y, z );
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void set_maximum( 
        const position & in_maximum )
    {
        _maximum = in_maximum;
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void set_minimumMaximum( 
        T minx, T miny, T minz,
        T maxx, T maxy, T maxz )
    {
        _minimum.set( minx, miny, minz );
        _maximum.set( maxx, maxy, maxz );
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void set_minimumMaximum( 
        const position & in_minimum,
        const position & in_maximum )
    {
        _minimum = in_minimum;
        _maximum = in_maximum;
    /*
        ### SHOULD SWAP MIN AND MAX IF MIN > MAX
    */
    }
    void include_point(
        const position & in_point )
    {
        if ( in_point.x() < _minimum.x() )
        {
            _minimum.x( in_point.x() );
        }
        if ( in_point.y() < _minimum.y() )
        {
            _minimum.y( in_point.y() );
        }
        if ( in_point.z() < _minimum.z() )
        {
            _minimum.z( in_point.z() );
        }
        if ( in_point.x() > _maximum.x() )
        {
            _maximum.x( in_point.x() );
        }
        if ( in_point.y() > _maximum.y() )
        {
            _maximum.y( in_point.y() );
        }
        if ( in_point.z() > _maximum.z() )
        {
            _maximum.z( in_point.z() );
        }
    }
    //@}

    /// @name transformations
    //@{
    void translate( 
        const vector & in_displacement )
    {
        _maximum += in_displacement;
        _minimum += in_displacement;
    }
    void translate( 
        T x, T y, T z )
    {
        _maximum.add( x, y, z );
        _minimum.add( x, y, z );
    }
    void scale( 
        const size & in_factor )
    {
        _maximum *= in_factor;
        _minimum *= in_factor;
    }
    void scale( 
        T x, T y, T z )
    {
        _maximum.multiply( x, y, z );
        _minimum.multiply( x, y, z );
    }
    //@}

    /// @name intersection tests
    //@{
    boolean
    includes_point(
        const position & in_point ) const
    {
        return(
            in_point.x() >= _minimum.x()
         && in_point.y() >= _minimum.y()
         && in_point.z() >= _minimum.z()
         && in_point.x() <= _maximum.x() 
         && in_point.y() <= _maximum.y()
         && in_point.z() <= _maximum.z() );
    }
    boolean
    intersects(
        const cuboid_aligned & rhs ) const
    {
        return(
            _minimum.x() < rhs._maximum.x()
         && _minimum.y() < rhs._maximum.y()
         && _minimum.z() < rhs._maximum.z()
         && _maximum.x() > rhs._minimum.x()
         && _maximum.y() > rhs._minimum.y()
         && _maximum.z() > rhs._minimum.z() );
    }
    boolean
    intersects_ray(
        const position &    in_origin,
        const vector &      in_direction,
        units               in_length,      ///< if 0, ray is infinite
        units *             out_intersection_length = 0,
        position *          out_intersection_point  = 0 ) const;
    //@}

    /// @name geometry applications
    //@{
    /** determine which side of a plane the cuboid lies on
     *  returns: 1 == positive side, -1 == negative side, 0 == both */
    integer side_of_plane( 
        const position &    in_displacement,
        const vector &      in_normal_plane ) const;
    //@}
    
private:

    position _minimum;
    position _maximum;
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_CUBOID_ALIGNED
