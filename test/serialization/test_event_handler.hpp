#if !defined(BEACH_SERIALIZATION_TEST_EVENT_HANDLER)
#define      BEACH_SERIALIZATION_TEST_EVENT_HANDLER
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event_handler.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <collection/ref_list.hpp>
#include <notification/event.hpp>
#include <notification/event_handler.hpp>

#include "test_event.hpp"

namespace invocation
{
    template <class T> class command_kill;
};

namespace lifecycle
{
    template <class abstract_type, class concrete_type> class object_catalog_utility;
};

namespace serialization
{
    using atoms::boolean;
    using notification::event_handler;

//--------------------------------------

/// event handler for testing
    
class test_event_handler
   : public event_handler
{
friend class invocation::command_kill<test_event_handler>;
friend class lifecycle::object_catalog_utility<test_event_handler,test_event_handler>;
public:

    static test_event_handler & acquire_singleton(); ///< via the object catalog

    test_event_handler();
    virtual ~test_event_handler();

    /// @event_handler overrides
    //@{
    virtual boolean handle_event( const event & );
    //@

protected:

    typedef collection::ref_list<test_event> test_events;

private:

    /// @name copy operations not implemented
    //@{
    test_event_handler(              const test_event_handler & );
    test_event_handler & operator =( const test_event_handler & );
    //@}
/*
    media_event *       find_media_event_by_name(const text * in_media_event_name );
    media_event_ref     acquire_media_event(media_event::Id in_id, const text * in_name);
    media_event &       new_media_event(media_event::Id in_id,const text * in_name );

    media_manager  *    _media_manager;
*/
    test_events         _test_events;

}; // end of class test_event_handler

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEST_EVENT_HANDLER
