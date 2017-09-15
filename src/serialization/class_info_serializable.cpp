//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_info_serializable.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/class_info_serializable.hpp> // this header

#include <serialization/reader.hpp>
#include <serialization/serializable_source.hpp>
#include <serialization/writer.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace serialization
{
    using namespace atoms;
    using lifecycle::object_identifier;
    using lifecycle::class_catalog;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const class_identifier this_class_id
    = 1; // !!! SPECIAL RESERVED ID VALUE

static const text this_class_name[]
    = "class_info";

static const text * selector_names[class_info_serializable::selector_count] =
{
    0, // selector_all
    0, // selector identity
    "class_id",
    "class_name",
    "last_object_id"
};

//--------------------------------------

static const class_info * this_class_info = 0;

struct class_info_serializable_selectors
{
    selector _array[class_info_serializable::selector_count];
    selector & operator[]( int i ) { return _array[i]; }
};
static class_info_serializable_selectors * selectors = 0;

//--------------------------------------
//  public methods
//--------------------------------------

// static
class_identifier
class_info_serializable::get_class_id()
{
    if ( this_class_info == 0 )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        this_class_info = &(catalog.register_class(
            this_class_id, this_class_name, 0 ));
    }
    return this_class_info->get_class_id();
}

//--------------------------------------

class_info_serializable::class_info_serializable(
    class_info & in_owner )
  :
    class_info_extension( get_class_id(), in_owner ),
    _is_reading( false )
{}

//--------------------------------------

// virtual
class_info_serializable::~class_info_serializable()
{}

//--------------------------------------

// virtual
void
class_info_serializable::update_owner_changed()
{
    if ( (! _is_reading) && (get_serializable_source() != 0) )
    {
        get_serializable_source()->add_dirty_flags(
            serializable_source::dirty_objects_changed );
    }
}

//--------------------------------------

// virtual
const selector &
class_info_serializable::get_selector_all()
{
    return get_selector(selector_all);
}

//--------------------------------------

// static
const selector &
class_info_serializable::get_selector(
    whole in_index )
{
    if ( selectors == 0 )
    {
        register_selectors();
    }
    if ( in_index < selector_count )
    {
        return (*selectors)[in_index];
    }
    else
    {
        return (*selectors)[selector_all];
    }
}

//--------------------------------------

// static
void
class_info_serializable::register_selectors()
{
    lifecycle::object_catalog_utility<class_info_serializable_selectors,class_info_serializable_selectors>
        ::acquire_object( this_class_name, &selectors );

    class_identifier cid = get_class_id();

    (*selectors)[selector_class_id]        .set_value( cid + selector_class_id );
    (*selectors)[selector_class_name]      .set_value( cid + selector_class_name );
    (*selectors)[selector_last_object_id]  .set_value( cid + selector_last_object_id );

    (*selectors)[selector_identity] = (*selectors)[selector_class_id];

    (*selectors)[selector_all]  = (*selectors)[selector_class_id];
    (*selectors)[selector_all] += (*selectors)[selector_class_name];
    (*selectors)[selector_all] += (*selectors)[selector_last_object_id];
}

//--------------------------------------

boolean
class_info_serializable::read_from(
    reader & in_reader )
{
    _is_reading = true;
    class_info & owner = get_owner_nc();

    class_identifier cid;
    if ( in_reader.read_whole16(
            &(get_selector(selector_class_id)),
            selector_names[selector_class_id],
            cid ) )
    {
        owner.set_class_id( cid );
    }
    stringex cname;
    if ( in_reader.read_string(
            &(get_selector(selector_class_name)),
            selector_names[selector_class_name],
            cname ) )
    {
        owner.set_class_name( cname );
    }
    object_identifier lastoid;
    if ( in_reader.read_whole64(
            &(get_selector(selector_last_object_id)),
            selector_names[selector_last_object_id],
            lastoid ) )
    {
        owner.set_last_object_id( lastoid );
    }
    _is_reading = false;
    return true;
}

//--------------------------------------

void
class_info_serializable::write_to(
    writer &            in_writer,
    const selector *    in_selector )
{
    const class_info & owner = get_owner();
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
    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_last_object_id) )) )
    {
        in_writer.write_whole64(
            &(get_selector(selector_last_object_id)),
            selector_names[selector_last_object_id],
            owner.get_last_object_id() );
    }
}

//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<serialization::class_info_serializable_selectors>;

//----------------------------------------------------------
// (end of file)
