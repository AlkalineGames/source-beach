#if !defined(BEACH_GEOMETRY_RECTANGLE)
#define      BEACH_GEOMETRY_RECTANGLE
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       rectangle.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <geometry/coordinates.hpp>

namespace geometry
{
    using atoms::boolean;

//--------------------------------------

/// 2-dimensional rectangle defined by minimum and maximum corners

template <class T>
class rectangle
{
public:

    typedef T                   units;
    typedef coordinates_xy<T>   displacement;
    typedef coordinates_xy<T>   position;
    typedef atoms::real         ratio;
    typedef atoms::integer      side;
    typedef coordinates_xy<T>   size;

    rectangle() 
      :
        _minimum( 0, 0 ),
        _maximum( 1, 1 )
    {}
    rectangle( 
        T maxx, T maxy )
      :
        _minimum( 0, 0 ),
        _maximum( maxx, maxy )
    {}
    rectangle( 
        T minx, T miny,
        T maxx, T maxy )
      :
        _minimum( minx, miny ),
        _maximum( maxx, maxy )
    {}
    rectangle( 
        const position & in_maximum )
      :
        _minimum( 0, 0 ),
        _maximum( in_maximum )
    {}
    rectangle( 
        const position & in_minimum,
        const position & in_maximum )
      :
        _minimum( in_minimum ),
        _maximum( in_maximum )
    {}

    // comparisons
    //@{
    bool operator ==( const rectangle & rhs ) const
    {   return (_minimum == rhs._minimum) && (_maximum == rhs._maximum); } 

    bool operator !=( const rectangle & rhs ) const
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
        // cost == 2 additions, 1 set
        return _maximum - _minimum + 1;
    }
    size get_size_half() const
    {
        // cost == 2 divides, 2 additions, 1 set
        return get_size() / 2;
    }
    position get_center() const
    {
        // cost == 2 divides, 4 additions, 1 set
        return _maximum - get_size_half();
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
        T x, T y )
    {
        _minimum.set( x, y );
    }
    void set_minimum( 
        const position & in_minimum )
    {
        _minimum = in_minimum;
    }
    void set_maximum( 
        T x, T y )
    {
        _maximum.set( x, y );
    }
    void set_maximum( 
        const position & in_maximum )
    {
        _maximum = in_maximum;
    }
    void set_minimum_maximum( 
        T minx, T miny,
        T maxx, T maxy )
    {
        _minimum.set( minx, miny );
        _maximum.set( maxx, maxy );
    }
    void set_minimum_and_maximum( 
        const position & in_minimum,
        const position & in_maximum )
    {
        _minimum = in_minimum;
        _maximum = in_maximum;
    }
    void set_minimum_and_size( 
        const position & in_minimum,
        const position & in_size )
    {
        _minimum = in_minimum;
        _maximum = in_minimum + in_size - 1;
    }
    void set_minimum_and_size( 
        T minx, T miny,
        T sizx, T sizy )
    {
        _minimum.set( minx, miny );
        _maximum.set( minx + sizx - 1, miny + sizy - 1 );
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
        if ( in_point.x() > _maximum.x() )
        {
            _maximum.x( in_point.x() );
        }
        if ( in_point.y() > _maximum.y() )
        {
            _maximum.y( in_point.y() );
        }
    }
    //@}

    /// @name reshaping within parent rectangle
    /**
     *  offset side indicates which side of the rectangle is the offset point;
     *      < 0, left/bottom side of rectangle from left/bottom     side of parent
     *     == 0, center           of rectangle from the left/bottom side of parent
     *      > 0, right/top side   of rectangle from right/top       side of parent
     */      
    //@{
    void reshape_within_parent( 
        const size &            in_parent_size,
        const size &            in_size,
        const displacement &    in_offset,
        side                    in_offset_side_x,
        side                    in_offset_side_y )
    {
        units thisoffsetx = in_offset.x();
        units thisoffsety = in_offset.y();
        if ( in_offset_side_x == 0 )
        {
            thisoffsetx -= (in_size.x() >> 1);
        }
        else if ( in_offset_side_x > 0 )
        {
            thisoffsetx = in_parent_size.x() - thisoffsetx - in_size.x();
        }
        if ( in_offset_side_y == 0 )
        {
            thisoffsety -= (in_size.y() >> 1);
        }
        else if ( in_offset_side_y > 0 )
        {
            thisoffsety = in_parent_size.y() - thisoffsety - in_size.y();
        }
        _minimum.set( thisoffsetx, thisoffsety );
        _maximum = _minimum + in_size - 1;
    }
    void reshape_within_parent( 
        const size &    in_parent_size,
        const size &    in_size,
        ratio           in_offset_x,
        ratio           in_offset_y,
        side            in_offset_side_x,
        side            in_offset_side_y )
    {
        ratio parentsizex  = ratio(in_parent_size.x());
        ratio parentsizey  = ratio(in_parent_size.y());
        ratio thisoffsetx  = parentsizex * in_offset_x;
        ratio thisoffsety  = parentsizey * in_offset_y;
        if ( in_offset_side_x == 0 )
        {
            thisoffsetx -= (in_size.x() >> 1);
        }
        else if ( in_offset_side_x > 0 )
        {
            thisoffsetx = parentsizex - thisoffsetx - in_size.x();
        }
        if ( in_offset_side_y == 0 )
        {
            thisoffsety -= (in_size.y() >> 1);
        }
        else if ( in_offset_side_y > 0 )
        {
            thisoffsety = parentsizey - thisoffsety - in_size.y();
        }
        _minimum.set( thisoffsetx, thisoffsety );
        _maximum = _minimum + in_size - 1;
    }
    void reshape_within_parent( 
        const size &    in_parent_size,
        ratio           in_width,
        ratio           in_height,
        ratio           in_offset_x,
        ratio           in_offset_y,
        side            in_offset_side_x,
        side            in_offset_side_y )
    {
        ratio parentsizex  = ratio(in_parent_size.x());
        ratio parentsizey  = ratio(in_parent_size.y());
        ratio thissizex    = parentsizex * in_width;
        ratio thissizey    = parentsizey * in_height;
        ratio thisoffsetx  = parentsizex * in_offset_x;
        ratio thisoffsety  = parentsizey * in_offset_y;
        if ( in_offset_side_x == 0 )
        {
            thisoffsetx -= (thissizex * 0.5);
        }
        else if ( in_offset_side_x > 0 )
        {
            thisoffsetx = parentsizex - thisoffsetx - thissizex;
        }
        if ( in_offset_side_y == 0 )
        {
            thisoffsety -= (thissizey * 0.5);
        }
        else if ( in_offset_side_y > 0 )
        {
            thisoffsety = parentsizey - thisoffsety - thissizey;
        }
        _minimum.set( thisoffsetx, thisoffsety );
        _maximum.set( thisoffsetx + thissizex - 1,
                      thisoffsety + thissizey - 1 );
    }
    //@}

    /// @name transformations
    //@{
    void translate( 
        const displacement & in_displacement )
    {
        _maximum += in_displacement;
        _minimum += in_displacement;
    }
    void translate( 
        T x, T y )
    {
        _maximum.add( x, y );
        _minimum.add( x, y );
    }
    void scale( 
        const size & in_factor )
    {
        _maximum *= in_factor;
        _minimum *= in_factor;
    }
    void scale( 
        T x, T y )
    {
        _maximum.multiply( x, y );
        _minimum.multiply( x, y );
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
         && in_point.x() <= _maximum.x() 
         && in_point.y() <= _maximum.y() );
    }
    boolean
    intersects(
        const rectangle & rhs ) const
    {
        return(
            _minimum.x() < rhs._maximum.x()
         && _minimum.y() < rhs._maximum.y()
         && _maximum.x() > rhs._minimum.x()
         && _maximum.y() > rhs._minimum.y() );
    }
    //@}

private:

    position _minimum;
    position _maximum;
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_RECTANGLE
