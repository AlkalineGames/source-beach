#if !defined(BEACH_NOTIFICATION_EVENT_HANDLER)
#define      BEACH_NOTIFICATION_EVENT_HANDLER
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_handler.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson, Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <notification/event.hpp>

namespace atoms
{
    class virtual_object;
};

namespace notification
{
    using atoms::boolean;
    using atoms::stringex;
    using atoms::text;
    using atoms::virtual_object;

//--------------------------------------

/// superclass for an event handler

class event_handler
{
public:

    BEACH_ALLOCATION_OPERATORS

    event_handler( const text * in_name );
    virtual ~event_handler();

    const stringex & get_name() const { return _name; }

    virtual boolean handle_event( ///< overrideable
        const event &       in_event,
        virtual_object *    in_subject );

private:

    stringex _name;

}; // end of class event_handler

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_EVENT_HANDLER
