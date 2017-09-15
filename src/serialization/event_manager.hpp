#if !defined(BEACH_SERIALIZATION_EVENT_MANAGER)
#define      BEACH_SERIALIZATION_EVENT_MANAGER

//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <serialization/serializable_factory.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace atoms
{
    class virtual_object;
};

namespace notification
{
    class event;
    class event_channel;
    class event_handler;
};

namespace serialization
{
    using atoms::boolean;
    using atoms::text;
    using atoms::virtual_object;
    using notification::event;
    using notification::event_channel;
    using notification::event_handler;

//--------------------------------------

/// singleton manager of events
/**
 *  This class is coded as a public interface with an
 *  internal implementation subclass. Linkage is only
 *  required for code that calls the static methods.
 *
 *  @note   design patterns applied:
 *              - Linkage Liberty   [WF]
 *              - Manager           [PLoP3]
 *              - Null Object       [PLoP3]
 *              - Serializer        [PLoP3]
 *              - Singleton         [GoF]
 */      
class event_manager
    : public serializable_factory
{
public:

    /// @name linkage required
    //@{
    static event_manager & acquire_singleton(); ///< via the object_catalog
    //@}
    static event_manager * find_singleton()
    {
        return lifecycle::object_catalog_utility<event_manager,event_manager>
                ::find_object( "event_manager", 0 );
    }
    static event_manager & get_singleton() ///< !!! assumes already acquired
    {
        return *find_singleton();
    }
    /// @@@ TODO - RESPONSE FROM POST_EVENT
    virtual boolean                 post_event(
                                        const event & ) = 0;
    virtual boolean                 post_event(
                                        const text *     in_name,
                                        virtual_object * in_subject = 0 ) = 0;

    virtual const event_channel &   register_event_channel(
                                        const text * in_name ) = 0;
    virtual const event_channel *   find_event_channel_by_name_const(
                                        const text * in_name ) = 0;
    virtual       event_channel *   find_event_channel_by_name(
                                        const text * in_name ) = 0;

	virtual const event &           register_event(
                                        const text * in_name ) = 0;
	virtual const event *           find_event_by_name_const(
                                        const text * in_name ) = 0;
    virtual       event *           find_event_by_name(
                                        const text * in_name ) = 0;

    virtual void                    register_event_handler(
                                        event_handler & ) = 0;
    virtual void                    unregister_event_handler(
                                        event_handler & ) = 0;
    virtual const event_handler *   find_event_handler_by_name(
                                        const text * in_event_name ) = 0;
        ///< if name is not registered, returns 0 or null event handler if it is installed
    virtual void                    install_event_handler_null() = 0;

}; // end of class event_manager

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_EVENT_MANAGER
