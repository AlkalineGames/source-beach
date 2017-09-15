#if !defined(BEACH_NOTIFICATION_EVENT)
#define      BEACH_NOTIFICATION_EVENT
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/stringex.hpp>
#include <chain/extension_typed.hpp>

namespace notification
{
    class event;
    class event_channel;
    using atoms::stringex;
    using atoms::text;
    using chain::extension;

//--------------------------------------

/// abstract superclass for an event extension
/**
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
class event_extension
    : public chain::extension_typed<event>
{
public:

    event_extension( class_identity in_class_id, event & in_owner );
    virtual void update_owner_changed() = 0;
};

//--------------------------------------

/// event

class event
{
public:

    BEACH_ALLOCATION_OPERATORS

    event(const text * in_event_name,void * in_affected_object);

    virtual ~event();

    const stringex &            get_name()          const { return _event_name; }

    event_channel *             get_event_channel() const {return _event_channel;}
    void                        set_event_channel( event_channel & in_event_channel );

    extension::class_identity   get_class_id()      const { return _class_id; }
    const stringex &            get_class_name()    const { return _class_name; }

    void                        set_class_id(       extension::class_identity );
    void                        set_class_name(     const text * in_name );

    // @name extension object (degenerate)
    //@{
    const event_extension *     get_extension_const() const { return _extension; }
          event_extension *     get_extension()             { return _extension; }
    void                        set_extension( event_extension * ); ///< destroys existing extension
    //@}

private:

    /// @event copy operations not implemented
    //@{
    event(               const event & );
    event & operator = ( const event & );
    //@}

    extension::class_identity  _class_id;
    stringex                   _class_name;
    stringex                   _event_name;
    event_channel *            _event_channel;
    void *                     _affected_object;
    event_extension *          _extension;

}; // end of class event

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_EVENT
