//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       vector.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/vector.hpp> // this header

namespace geometry
{

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_x_neg()
{
    static vector_xyz<T> negXaxis( -1, 0, 0 );
    return negXaxis;
}

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_y_neg()
{
    static vector_xyz<T> negYaxis( 0, -1, 0 );
    return negYaxis;
}

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_z_neg()
{
    static vector_xyz<T> negZaxis( 0, 0, -1 );
    return negZaxis;
}

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_x_pos()
{
    static vector_xyz<T> posXaxis( 1, 0, 0 );
    return posXaxis;
}

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_y_pos()
{
    static vector_xyz<T> posYaxis( 0, 1, 0 );
    return posYaxis;
}

//--------------------------------------

//static
template <class T>
const vector_xyz<T> &
vector_xyz<T>::get_axis_z_pos()
{
    static vector_xyz<T> posZaxis( 0, 0, 1 );
    return posZaxis;
}

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
