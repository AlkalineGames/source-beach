//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_atoms.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_value.tpp>
#include <notification/observable_value_copycat.tpp>
#include <notification/observable_atoms.hpp>

namespace notification
{

//--------------------------------------

template class observable_value<boolean>;
template class observable_value_copycat<boolean>;

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
