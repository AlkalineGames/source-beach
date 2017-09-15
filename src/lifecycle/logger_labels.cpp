//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       logger_labels.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/logger_labels.hpp> // this header

#include <atoms/primitives.hpp>
#include <lifecycle/logger.hpp>

namespace lifecycle
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text * labels[] =
{
    "channel",
    "class_catalog",
    "class_info",
    "command_distributed_group",
    "event_manager",
    "object_catalog",
    "object_identification",
    "observable_list_of_string",
    "property_catalog",
    "reader_packeted",
    "romp_recv",
    "romp_send",
    "serializable",
    "serializable_manager",
    "text_stream_appender",
    "writer_forwarded",
    0
};

//--------------------------------------
//  public methods
//--------------------------------------

void
logger_labels::install()
{
    logger::get_singleton().add_labels( labels );
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
