//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       lifecycle_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/object_catalog.hpp>

template class std::map<atoms::stringex,lifecycle::object_catalog::binding*>;
template class invocation::command_kill<atoms::stringex>;

//----------------------------------------------------------
// (end of file)
