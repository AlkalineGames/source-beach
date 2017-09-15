#if !defined(BEACH_GEOMETRY_POLYGON)
#define      BEACH_GEOMETRY_POLYGON
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       polygon.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/vector.hpp>

namespace geometry
{

//--------------------------------------

/// template for an interface to a 3-D polygon
template <class T>
class polygon_xyz
{
public:
    typedef T                   units;
    typedef coordinates_xyz<T>  vertex;
    typedef vector_xyz<T>       vector;
};

//--------------------------------------

/// template for an interface to an 3-D polygon, indexed
template <class T, class I>
class polygon_xyz_indexed
    : public polygon_xyz<T>
{
public:
    typedef I index;
};

//--------------------------------------

/// template for an interface to an 3-D polygon, indexed, with polymorphic accessors
template <class T, class I>
class polygon_xyz_indexed_virtual
    : public polygon_xyz_indexed<T,I>
{
public:
    virtual whole           get_vertex_count()  const = 0;
    virtual index           operator[]( whole ) const = 0;
    virtual index &         operator[]( whole )       = 0;
};

//--------------------------------------

/// template for an interface to a 3-D polygon with polymorphic accessors
template <class T>
class polygon_xyz_virtual
    : public polygon_xyz<T>
{
public:
    virtual whole           get_vertex_count()  const = 0;
    virtual const vertex &  operator[]( whole ) const = 0;
    virtual       vertex &  operator[]( whole )       = 0;
};

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_POLYGON
