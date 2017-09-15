#if !defined(BEACH_NOTIFICATION_PACKET_HANDLER)
#define      BEACH_NOTIFICATION_PACKET_HANDLER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_handler.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <notification/channel_identifier.hpp>

namespace notification
{
    class channel;
    class packet;
    using atoms::boolean;
    using atoms::text;

//--------------------------------------

/// interface for a packet handler

class packet_handler
{
public:

    virtual const text *    get_name() const = 0;

    virtual boolean         handle_packet(  ///< true if handled
        const packet &,
        channel *,
        channel_identifier in_source,
        channel_identifier in_destination ) = 0;

}; // end of class packet_handler

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKET_HANDLER
