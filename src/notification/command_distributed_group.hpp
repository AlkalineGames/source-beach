#if !defined(BEACH_NOTIFICATION_DISTRIBUTED_COMMAND_GROUP)
#define      BEACH_NOTIFICATION_DISTRIBUTED_COMMAND_GROUP
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_distributed_group.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/ref_list.hpp>
#include <notification/channel_identifier.hpp>

namespace notification
{
    class channel;
    class command_distributed;
    class packet;
    using atoms::text;

//--------------------------------------

typedef collection::ref_list<command_distributed>
    command_distributed_group_collection;

//--------------------------------------

/// collection of distributed commands

class command_distributed_group
    : public command_distributed_group_collection
{
public:

    BEACH_ALLOCATION_OPERATORS

    command_distributed_group();
    ~command_distributed_group(); ///< !!! only needed for debugging

    /// overload of collection superclass add(...), takes ownership
    void add(
        command_distributed &,
        const text * in_name_prefix );

    /// clone command from packet (returns 0 if command not found)
    command_distributed *   spawn( 
        const packet &          in_packet,
        channel *               in_channel,
        channel_identifier      in_source,
        channel_identifier      in_destination );

}; // end of class command_distributed_group

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_DISTRIBUTED_COMMAND_GROUP
