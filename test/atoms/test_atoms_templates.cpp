//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_atoms_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

#include <deque>
#include <string>

//--------------------------------------
//  template instantiations
//--------------------------------------

template class std::deque<std::string>;

//----------------------------------------------------------
// (end of file)
