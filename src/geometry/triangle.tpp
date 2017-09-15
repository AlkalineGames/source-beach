//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       triangle.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/triangle.hpp> // this header

namespace geometry
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
triangle_xyz<T>::vector
triangle_xyz<T>::calculate_surface_normal() const
{
    vector edge0and1( _vertices[1]-_vertices[0] );
    vector edge0and2( _vertices[2]-_vertices[0] );
    vector cross( edge0and1, edge0and2 );
    return cross.normalize();
}

//--------------------------------------

template <class T>
triangle_xyz_referenced<T>::vector
triangle_xyz_referenced<T>::calculate_surface_normal() const
{
    vector edge0and1( *_vertices[1]-*_vertices[0] );
    vector edge0and2( *_vertices[2]-*_vertices[0] );
    vector cross( edge0and1, edge0and2 );
    return cross.normalize();
}

//--------------------------------------

template <class T, class I>
triangle_xyz_indexed<T,I>::vector
triangle_xyz_indexed<T,I>::calculate_surface_normal(
    vertex in_vertices[] ) const
{
    vector edge0and1( 
        in_vertices[_vertex_indices[1]]
       -in_vertices[_vertex_indices[0]] );
    vector edge0and2(
        in_vertices[_vertex_indices[2]]
       -in_vertices[_vertex_indices[0]] );
    vector cross( edge0and1, edge0and2 );
    return cross.normalize();
}

//--------------------------------------

template <class T, class I>
triangle_xyz_indexed<T,I>::vector
triangle_xyz_indexed<T,I>::triangle_xyz_indexed( 
    index v0,
    index v1,
    index v2 )
{
    _vertex_indices[0] = v0;
    _vertex_indices[1] = v1;
    _vertex_indices[2] = v2;
}

//--------------------------------------

// virtual
template <class T, class I>
triangle_xyz_indexed<T,I>::index
triangle_xyz_indexed<T,I>::operator[](
    whole n ) const
{
    return _vertex_indices[n];
}

//--------------------------------------

// virtual
template <class T, class I>
triangle_xyz_indexed<T,I>::index &
triangle_xyz_indexed<T,I>::operator[](
    whole n )
{
    return _vertex_indices[n];
}

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
