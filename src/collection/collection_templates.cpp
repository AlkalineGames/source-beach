//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       collection_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <collection/pointer_set.hpp>

#include <deque>
#include <list>
#include <map>
#include <set>
#include <vector>

template class std::deque<std::string>; // !!! only needed by cppunit
template class std::list<atoms::pointer_to_const>;
template class std::list<atoms::stringex>;
template class std::map<atoms::integer,atoms::pointer_to_const>;
template class std::map<atoms::stringex,atoms::pointer_to_const>;
template class std::map<atoms::stringex,atoms::boolean>;
template class std::set<atoms::pointer_to_const,collection::pointer_to_compare_pointers>;
template class std::vector<atoms::pointer_to_const>;

//----------------------------------------------------------
// (end of file)
