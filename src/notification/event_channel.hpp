#if !defined(BEACH_NOTIFICATION_EVENT_CHANNEL)
#define      BEACH_NOTIFICATION_EVENT_CHANNEL
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_channel.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson, Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/stringex.hpp>
#include <chain/extension_typed.hpp>
#include <collection/ref_list.hpp>
#include <notification/event_handler.hpp>

namespace atoms
{
    class virtual_object;
};

namespace notification
{
    using atoms::boolean;
    using atoms::text;
    using atoms::stringex;
    using atoms::virtual_object;
    using atoms::whole;
    using chain::extension;

//--------------------------------------

/// abstract superclass for an event channel extension
/**
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
class event_channel_extension
    : public chain::extension_typed<event_channel>
{
public:

    event_channel_extension( class_identity in_class_id, event_channel & in_owner );
    virtual void update_owner_changed() = 0;
};

//--------------------------------------

/// event channel

class event_channel
{
public:

    //MORE TO ADD hungy, excited, friendly, etc.
    enum channel_type
    {
        sync,   // 0 default
        async   // 1
    };

    BEACH_ALLOCATION_OPERATORS

    event_channel( const text * in_name );
    virtual ~event_channel();

//    void post_message_sync(event & in_event);
// @@@ TODO   post_message_async(event & in_event);  // @@@ add time parameter also

    const stringex &                get_name()      const { return _name; }
    extension::class_identity       get_class_id()  const { return _class_id; }
    const channel_type              get_channel_type()    { return _channel_type; }
                                   
    void                            set_class_id(       extension::class_identity );
    void                            set_channel_type(   const text *  );
                                   
    boolean                         post_event(
        const event &                   in_event,
        virtual_object *                in_subject );
                                   
    void                            attach_handler( event_handler & );
    void                            detach_handler( event_handler & );

    // @name extension object (degenerate)
    //@{
    const event_channel_extension * get_extension_const() const { return _extension; }
          event_channel_extension * get_extension()             { return _extension; }
    void                            set_extension( event_channel_extension * ); ///< destroys existing extension
    //@}

private:

    typedef collection::ref_list<event_handler> handlers;

    /// @event_channel copy operations not implemented
    //@{
    event_channel(               const event_channel & );
    event_channel & operator = ( const event_channel & );
    //@}

    extension::class_identity   _class_id;
    stringex                    _name;
    channel_type                _channel_type;
    event_channel_extension *   _extension;
    handlers                    _handlers;
};

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_EVENT_CHANNEL
