//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       invocation_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/destroyer.hpp>
#include <invocation/command.hpp>
#include <invocation/text_command.hpp>

template class atoms::destroyer_typed<invocation::command>;
template class atoms::destroyer<invocation::command>;
template class atoms::destroyer_typed<invocation::text_command>;
template class atoms::destroyer<invocation::text_command>;

//----------------------------------------------------------
// (end of file)
