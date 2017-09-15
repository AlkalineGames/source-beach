//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_geometry_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <geometry/constants.tpp>
#include <geometry/coordinates.tpp>
#include <geometry/cuboid_aligned.tpp>
#include <geometry/vector.tpp>

//--------------------------------------
//  template instantiations
//--------------------------------------

template class geometry::constants<atoms::real>;
template class geometry::coordinates_xyz<atoms::real>;
template class geometry::cuboid_aligned<atoms::real>;
template class geometry::vector_xyz<atoms::real>;

//----------------------------------------------------------
// (end of file)
