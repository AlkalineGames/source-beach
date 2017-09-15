//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_serializable.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <serialization/event_serializable.hpp> // this header

#include <serialization/reader.hpp>
#include <serialization/serializable_source.hpp>
#include <serialization/writer.hpp>
#include <serialization/event_channel_serializable.hpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/logger.hpp>
#include <notification/event.hpp>
#include <notification/event_channel.hpp>

namespace serialization
{
    using namespace atoms;
    using lifecycle::object_identifier;
    using lifecycle::class_catalog;
    using lifecycle::class_info;
    using lifecycle::logger;
    using notification::event;
    using notification::event_channel;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "event";

static const text * selector_names[event_serializable::selector_count] =
{
    0, // selector_all
    0, // selector identity
    "class_id",
    "class_name",
    "event_channel"
};

//--------------------------------------

static const class_info * this_class_info = 0;

static selector selectors[event_serializable::selector_count];

//--------------------------------------
//  public methods
//--------------------------------------

// static
class_identifier
event_serializable::get_class_id()
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

event_serializable::event_serializable(
    event & in_owner )
  :
    event_extension( get_class_id(), in_owner )
{}

//--------------------------------------

// virtual
event_serializable::~event_serializable()
{}

//--------------------------------------

// virtual
void
event_serializable::update_owner_changed()
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
event_serializable::get_selector_all()
{
    return get_selector(selector_all);
}

//--------------------------------------

// static
const selector &
event_serializable::get_selector(
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
event_serializable::register_selectors()
{
    class_identifier cid = get_class_id();

    selectors[selector_class_id]      .set_value( cid + selector_class_id );
    selectors[selector_class_name]    .set_value( cid + selector_class_name );
    selectors[selector_event_channel] .set_value( cid + selector_event_channel );

    selectors[selector_identity]  = selectors[selector_class_id];

    selectors[selector_all]   = selectors[selector_class_id];
    selectors[selector_all]  += selectors[selector_class_name];
    selectors[selector_all]  += selectors[selector_event_channel];
}

//--------------------------------------

boolean
event_serializable::read_from(
    reader & in_reader )
{
    static const text this_method_name[]
        = "readFrom(...)";

    event & owner = get_owner_nc();

    /* use owners class_id
    class_identifier cid;
    if ( in_reader.read_whole16(
            &(get_selector(selector_class_id)),
            selector_names[selector_class_id],
            cid ) )
    {
        owner.set_class_id( cid );
    }
    */
    stringex cname;
    if ( in_reader.read_string(
            &(get_selector(selector_class_name)),
            selector_names[selector_class_name],
            cname ) )
    {
        owner.set_class_name( cname );
    }
    serializable * ser;
    if ( in_reader.read_object(
            &(get_selector(selector_event_channel)),
            selector_names[selector_event_channel],
            ser ) )
    {
        event_channel_serializable * ecser
            = dynamic_cast<event_channel_serializable*>(ser);
        if ( ecser !=0 )
        {
            owner.set_event_channel(ecser->get_owner_nc());
        }
    }
    else
    {
        stringex msg( "!!! event_channel for event " );
        msg += owner.get_name();
        msg += "has not been registered";
        logger::get_singleton().log_error(
            this_class_name, this_method_name , msg );
    }
    return true;
}

//--------------------------------------

void
event_serializable::write_to(
    writer &            in_writer,
    const selector *    in_selector )
{
    const event & owner = get_owner();

    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_class_id) )) )
    {
        in_writer.write_whole16(
            &(get_selector(selector_class_id)),
            selector_names[selector_class_id],
            owner.get_class_id() );
    }
    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_class_name) )) )
    {
        in_writer.write_string(
            &(get_selector(selector_class_name)),
            selector_names[selector_class_name],
            owner.get_class_name() );
    }
    // @@@ TODO - event_channel
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
