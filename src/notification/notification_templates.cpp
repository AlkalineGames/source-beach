//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       notification_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/destroyer.hpp>
#include <chain/extension_typed.tpp>
#include <invocation/command_kill.tpp>
#include <notification/command_distributed.hpp>
#include <notification/event.hpp>
#include <notification/event_channel.hpp>
#include <notification/menu.hpp>
#include <notification/packet_factory.hpp>
#include <notification/packet_handler.hpp>

template class atoms::destroyer_typed<notification::command_distributed>;
template class atoms::destroyer<notification::command_distributed>;
template class atoms::destroyer_typed<notification::event>;
template class atoms::destroyer<notification::event>;
template class atoms::destroyer_typed<notification::event_channel>;
template class atoms::destroyer<notification::event_channel>;
template class atoms::destroyer_typed<notification::menu>;
template class atoms::destroyer<notification::menu>;
template class atoms::destroyer_typed<notification::packet_factory::handler_registration>;
template class atoms::destroyer<notification::packet_factory::handler_registration>;
template class atoms::destroyer_typed<notification::packet_handler>;
template class atoms::destroyer<notification::packet_handler>;
template class chain::extension_typed<notification::event>;
template class chain::extension_typed<notification::event_channel>;
template class invocation::command_kill<notification::packet_factory>;

//----------------------------------------------------------
// (end of file)
