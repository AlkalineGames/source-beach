//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_channel_serializable.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <serialization/event_channel_serializable.hpp> // this header

#include <serialization/event_manager.hpp>
#include <serialization/reader.hpp>
#include <serialization/serializable_source.hpp>
#include <serialization/writer.hpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/logger.hpp>
#include <notification/event_channel.hpp>
#include <notification/event_handler.hpp>

//--------------------------------------

namespace serialization
{
    using namespace atoms;
    using lifecycle::class_catalog;
    using lifecycle::class_info;
    using lifecycle::logger;
    using lifecycle::object_identifier;
    using notification::event_channel;
    using notification::event_handler;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "event_channel";

static const text * selector_names[event_channel_serializable::selector_count] =
{
    0, // selector_all
    0, // selector identity
    "class_id",
    "event_channel_type",
    "event_handler_name"
};

//--------------------------------------

static const class_info * this_class_info = 0;

static selector selectors[event_channel_serializable::selector_count];

//--------------------------------------
//  public methods
//--------------------------------------

// static
class_identifier
event_channel_serializable::get_class_id()
{
    if ( this_class_info == 0 )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        this_class_info = catalog.resolve_class_by_name(
            this_class_name, false ); // cannot fail
    }
    return this_class_info->get_class_id();
}

//--------------------------------------

event_channel_serializable::event_channel_serializable(
    event_channel & in_owner )
  :
    event_channel_extension( get_class_id(), in_owner )
{}

//--------------------------------------

// virtual
event_channel_serializable::~event_channel_serializable()
{}

//--------------------------------------

// virtual
void
event_channel_serializable::update_owner_changed()
{
    if (get_serializable_source() != 0 )
    {
        get_serializable_source()->add_dirty_flags(
            serializable_source::dirty_objects_changed );
    }
}

//--------------------------------------

// virtual
const selector &
event_channel_serializable::get_selector_all()
{
    return get_selector(selector_all);
}

//--------------------------------------

// static
const selector &
event_channel_serializable::get_selector(
    whole in_index )
{
    if ( selectors[selector_all].is_empty() )
    {
        register_selectors();
    }
    if ( in_index < selector_count )
    {
        return selectors[in_index];
    }
    else
    {
        return selectors[selector_all];
    }
}

//--------------------------------------

// static
void
event_channel_serializable::register_selectors()
{
    class_identifier cid = get_class_id();

    selectors[selector_class_id]    .set_value( cid + selector_class_id );
    selectors[selector_channel_type].set_value( cid + selector_channel_type );
    selectors[selector_handler_name].set_value( cid + selector_handler_name );

    selectors[selector_identity] = selectors[selector_class_id];

    selectors[selector_all]  = selectors[selector_class_id];
    selectors[selector_all] += selectors[selector_channel_type];
    selectors[selector_all] += selectors[selector_handler_name];
}

//--------------------------------------

boolean
event_channel_serializable::read_from(
    reader & in_reader )
{
    static const text this_method_name[]
        = "readFrom(...)";

    event_channel & owner = get_owner_nc();

    // use owners class_id (which is event_channel)
    /*
    class_identifier cid;
    if ( in_reader.read_whole16(
            &(get_selector(selector_class_id)),
            selector_names[selector_class_id],
            cid ) )
    {
        owner.set_class_id( cid );
    }
    */
    stringex channelname;
    if ( in_reader.read_string(
            &(get_selector(selector_channel_type)),
            selector_names[selector_channel_type],
            channelname ) )
    {
        owner.set_channel_type( channelname );
    }
    stringex classname;
    if ( in_reader.read_string(
            &(get_selector(selector_handler_name)),
            selector_names[selector_handler_name],
            classname ) )
    {
        const event_handler * eh =
            event_manager::acquire_singleton()
                .find_event_handler_by_name( classname );
        if ( eh != 0 )
        {
            event_handler * evs = const_cast<event_handler*>(eh);
            owner.attach_handler(*evs);
        }
        else
        {
            stringex msg( "!!! event_handler <" );
            msg += classname;
            msg += "> has not been registered";
            logger::get_singleton().log_error(
                this_class_name, "read_from", msg );
        }
    }
    return true;
}

//--------------------------------------

void
event_channel_serializable::write_to(
    writer &            in_writer,
    const selector *    in_selector )
{
    const event_channel & owner = get_owner();

    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_class_id) )) )
    {
        in_writer.write_whole16(
            &(get_selector(selector_class_id)),
            selector_names[selector_class_id],
            owner.get_class_id() );
    }

    /* NOT IMPLEMENTED YET */
    /*
    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_channel_type) )) )
    {
        in_writer.write_string(
            &(get_selector(selector_channel_type)),
            selector_names[selector_channel_type],
            owner.get_channel_type() );
             (needs to return a string)
    }
    */
    // @@@ TODO - selector_handler_name
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
