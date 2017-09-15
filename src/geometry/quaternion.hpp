#if !defined(BEACH_GEOMETRY_QUATERNION)
#define      BEACH_GEOMETRY_QUATERNION
//----------------------------------------------------------
//  Copyright 1998-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       quaternion.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/vector.hpp>

namespace geometry
{

//--------------------------------------

/// quaternion, left-handed

template <class T>
struct quaternion
{
    typedef vector_xyz<T>   axis_type;
    typedef T               angle_type;

    quaternion()
      : _axis( axis_type::axis_y ), _angle( 0 )
    {}
    quaternion( const axis_type & in_axis, angle_type in_angle )
      : _axis( in_axis ), _angle( in_angle )
    {}
    quaternion( typename axis_type::axis_enum in_axis, angle_type in_radians )
      : _axis( in_axis ), _angle( in_radians )
    {}
    quaternion( const quaternion & rhs )
      : _axis( rhs._axis ), _angle( rhs._angle )
    {}
    quaternion( no_init_type )
      : _axis( atoms::no_init )
    {}

    quaternion & operator =( const quaternion & rhs )
    {   _axis = rhs._axis; _angle = rhs._angle; return *this; }

    void set( const axis_type & in_axis, angle_type in_angle )
    {   _axis = in_axis; _angle = in_angle; }

    const axis_type &   axis() const            { return _axis; }
          axis_type &   axis()                  { return _axis; }
    angle_type          angle() const           { return _angle; }
    void                angle( angle_type a )   { _angle = a; }

    int operator ==( const quaternion & rhs ) const { return ((_axis == rhs._axis) && (_angle == rhs._angle)); }
    int operator !=( const quaternion & rhs ) const { return ((_axis != rhs._axis) || (_angle != rhs._angle)); }

private:

    axis_type  _axis;
    angle_type _angle;

}; // end of template quaternion<T>

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_QUATERNION
