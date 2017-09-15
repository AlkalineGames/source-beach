#if !defined(BEACH_GEOMETRY_TRIANGLE)
#define      BEACH_GEOMETRY_TRIANGLE
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       triangle.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/polygon.hpp>

namespace geometry
{

//--------------------------------------

/// template for an interface to a 3-D triangle

template <class T>
class triangle_xyz
    : public polygon_xyz<T>
{
public:

    enum { vertex_count = 3 };

    triangle_xyz( 
        const vertex & v0,
        const vertex & v1,
        const vertex & v2 )
    {
        _vertices[0] = v0;
        _vertices[1] = v1;
        _vertices[2] = v2;
    }
    const vertex & operator[]( whole n ) const  { return _vertices[n]; }
          vertex & operator[]( whole n )        { return _vertices[n]; }

    vector calculate_surface_normal() const; ///< normalized

private:

    vertex _verticies[vertex_count];

}; // end of triangle_xyz<T>

//--------------------------------------

/// template for an interface to a 3-D triangle with references to vertices

template <class T>
class triangle_xyz_referenced
    : public polygon_xyz<T>
{
public:

    enum { vertex_count = 3 };

    triangle_xyz_referenced(
        vertex & v0,
        vertex & v1,
        vertex & v2 )
    {
        _vertices[0] = &v0;
        _vertices[1] = &v1;
        _vertices[2] = &v2;
    }
    const vertex & operator[]( whole n ) const  { return *_vertices[n]; }
          vertex & operator[]( whole n )        { return *_vertices[n]; }

    vector calculate_surface_normal() const; /// normalized

private:

    vertex * _vertices[vertex_count];

}; // end of triangle_xyz_referenced<T>

//--------------------------------------

/// template for an interface to a 3-D triangle, indexed

template <class T, class I>
class triangle_xyz_indexed
    : public polygon_xyz_indexed<T,I>
{
public:

    enum { vertex_count = 3 };

    triangle_xyz_indexed( 
        index v0,
        index v1,
        index v2 )
    {
        _vertex_indices[0] = v0;
        _vertex_indices[1] = v1;
        _vertex_indices[2] = v2;
    }
    /// @name overrides
    //@{
    virtual index   operator[]( whole n ) const;
    virtual index & operator[]( whole n );
    //@}

    vector calculate_surface_normal(
        vertex in_vertices[] ) const; ///< normalized

private:

    index _vertex_indices[vertex_count];

}; // end of triangle_xyz_indexed<T>

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_TRIANGLE
