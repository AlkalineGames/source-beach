//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_set.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_set.hpp> // this header

#include <atoms/destroyer.hpp>
#include <serialization/reader.hpp>
#include <serialization/serializable_spec.hpp>
#include <serialization/writer.hpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/logger.hpp>
#include <taxonomy/property.hpp>
#include <taxonomy/property_reals.hpp>
#include <taxonomy/property_stringex.hpp>
#include <taxonomy/taxonomy_manager.hpp>

namespace taxonomy
{
    using namespace atoms;
    using serialization::serializable_spec;
    using lifecycle::class_catalog;
    using lifecycle::class_info;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text name_this_class[]
    = "property_set";

enum property_type
{
    property_type_none,
    property_type_string,
    property_type_real,
    property_type_count
};

static const text * property_type_names[property_type_count] =
{
    "(none)",
    "string",
    "real"
};

static const text * selector_names[property_set::selector_count] =
{
    0, // selector_all
    0, // selector identity
    0, // selector_name
    "property",
    "type",
    "array",
    "value"
};

static whole count_array_max = 9999;

//--------------------------------------

static const class_info * class_info_this = 0;

static selector selectors[property_set::selector_count];

//--------------------------------------
//  public methods
//--------------------------------------

// static
class_identifier
property_set::get_class_id()
{
    if ( class_info_this == 0 )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        class_info_this = catalog.resolve_class_by_name(
            name_this_class, false ); // cannot fail
    }
    return class_info_this->get_class_id();
}

//--------------------------------------

property_set::property_set(
    const text * in_name )
  :
    _identification( in_name )
#if 0
    _collection()
#endif
{}

//--------------------------------------

// virtual
property_set::~property_set()
{}

//--------------------------------------

const property &
property_set::get_property(
    const text * in_name ) const
{
    stringex name( in_name );
    const property * prop = find_ref_const( name );
    if ( prop == 0 )
    {
        prop = &(taxonomy_manager::acquire_singleton().get_property_null());
    }
    return *prop;
}

//--------------------------------------

// virtual
const selector &
property_set::get_selector_all()
{
    return get_selector( selector_all );
}

//--------------------------------------

// static
const selector &
property_set::get_selector(
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
property_set::register_selectors()
{
    class_identifier cid = get_class_id();

    selectors[selector_name]    .set_value( cid + selector_name );
    selectors[selector_property].set_value( cid + selector_property );
    selectors[selector_type]    .set_value( cid + selector_type );
    selectors[selector_array]   .set_value( cid + selector_array );
    selectors[selector_value]   .set_value( cid + selector_value );

    selectors[selector_identity] = selectors[selector_name];

    selectors[selector_all]  = selectors[selector_property];
    selectors[selector_all] += selectors[selector_type];
    selectors[selector_all] += selectors[selector_array];
    selectors[selector_all] += selectors[selector_value];
}

//--------------------------------------

// virtual
boolean
property_set::read_from(
    context &   in_context,
    reader &    in_reader )
{
    static const text name_this_method[]
        = "read_from(...)";

    const text * errmsg = 0;
    stringex propname;
    while ( in_reader.read_string(
                &(get_selector(selector_property)),
                selector_names[selector_property],
                propname ) )
    {
        property * propnew = 0;
        property_type proptype = property_type_string; // default type
        integer value;       
        if ( in_reader.read_enum(
                &(get_selector(selector_type)),
                selector_names[selector_type],
                property_type_names,
                property_type_count,
                value ) )
        {
            proptype = property_type(value);
        }
        switch ( proptype )
        {
            case property_type_string :
            {
                stringex stringvalue;
                if ( ! in_reader.read_string(
                        &(get_selector(selector_value)),
                        selector_names[selector_value],
                        stringvalue ) )
                {
                    errmsg = "failed to read string";
                    break;
                }
                // ### REPLACING WHETHER IT EXISTS OR NOT
                propnew = new property_stringex( propname, stringvalue );
                break;
            }
            case property_type_real :
            {
                whole arraycount = 0;
                if ( in_reader.read_whole(
                        &(get_selector(selector_array)),
                        selector_names[selector_array],
                        arraycount ) )
                {
                    if (   (arraycount == 0)
                        || (arraycount > count_array_max) )
                    {
                        errmsg = "array count 0 or beyond maximum"; 
                        break;
                    }
                    real realvalues[arraycount];
                    if ( ! in_reader.read_ordered_real(
                            &(get_selector(selector_value)),
                            selector_names[selector_value],
                            realvalues, arraycount ) )
                    {
                        errmsg = "failed to read array of reals";
                        break;
                    }
                    // ### REPLACING WHETHER IT EXISTS OR NOT
                    propnew = new property_reals(
                        propname, arraycount, realvalues );
                }
                else
                {
                    real realvalue;
                    if ( ! in_reader.read_real(
                            &(get_selector(selector_value)),
                            selector_names[selector_value],
                            realvalue ) )
                    {
                        errmsg = "failed to read real";
                        break;
                    }
                    // ### REPLACING WHETHER IT EXISTS OR NOT
                    propnew = new property_reals(
                        propname, 1, &realvalue );
                }
                break;
            }
        }
        if ( propnew != 0 )
        {
            replace( propname, *propnew );
        }
    }
    if ( errmsg != 0 )
    {
        logger::get_singleton().log_error(
            name_this_class, name_this_method, errmsg );
    }
    return true;
}

//--------------------------------------

// virtual
void
property_set::write_to(
    context &           in_context,
    writer &            in_writer,
    const selector *    in_selector )
{
    static const text name_this_method[]
        = "write_to(...)";

    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_identity) )) )
    {
        // @@@ THIS SHOULD BE REFACTORED TO serializable
        serializable_spec spec(
            get_class_id(), name_this_class, 0, get_name().get_text() );
        in_writer.write_spec(
            &(get_selector(selector_identity)),
            0, spec );
    }
    // ### IMPLEMENT THE REST WHEN NEEDED
#if 0    
    if ( in_selector->includes( get_selector(selector_read_exclusive) ) )
    {
        in_writer.write_boolean(
            &(get_selector(selector_read_exclusive)),
            selector_names[selector_read_exclusive],
            true );
    }
    const text * errmsg = 0;
    whole assoccount = 0;
    if (   (in_selector == 0)
        || (in_selector->includes( get_selector(selector_association) ) ) )
    {
        const body_association * assoc =
            static_cast<const body_association*>(
                _associations.getFirstLink());
        while ( assoc != 0 )
        {
            if ( assoccount++ > max_associations )
            {
                errmsg = text_error_maximum_associations_exceeded;
                break;
            }
            if ( assoccount > 1 )
            {
                get_owner_nc().write_newline_for_extension(
                    in_writer, *this );
            }
            body_association::Side sidethis =
                assoc->get_side( get_owner_nc() );
            body_association::Side sidepeer =
                body_association::calcOppositeSide( sidethis );
            const body & peerbod = assoc->getMember( sidepeer );
            in_writer.write_object(
                &(get_selector(selector_association)),
                &(const_cast<body&>(peerbod).get_selector_identity()),
                selector_names[selector_association],
                const_cast<body*>(&peerbod) );
            in_writer.write_whole(
                &(get_selector(selector_qualifier)),
                selector_names[selector_qualifier],
                assoc->getQualifier() );
            box_serializable_adapter bsathis(
                const_cast<cuboid&>(assoc->get_location( sidethis )) );
            box_serializable_adapter bsapeer(
                const_cast<cuboid&>(assoc->get_location( sidepeer )) );
            box_serializable_adapter * bsaleft =
                sidethis == body_association::LeftSide ? &bsathis : &bsapeer;
            box_serializable_adapter * bsaright =
                sidethis == body_association::LeftSide ? &bsapeer : &bsathis;
            //bsathis.write_to( in_writer, 0 ); // !!! no selector to write all
            in_writer.write_value(
                &(get_selector(selector_location_left)),
                &(bsathis.get_selector_all()),
                selector_names[selector_location_left],
                *bsaleft );
            //bsapeer.write_to( in_writer, 0 ); // !!! no selector to write all
            in_writer.write_value(
                &(get_selector(selector_location_right)),
                &(bsathis.get_selector_all()),
                selector_names[selector_location_right],
                *bsaright );
            in_writer.write_whole(
                &(get_selector(selector_constraint_kind)),
                selector_names[selector_constraint_kind],
                assoc->get_constraint_kind() );
            const angles_deg & constraintangles
                = assoc->get_constraint_angles();
            real values[3] = // $$$ DIRECT ACCESS WOULD BE FASTER
            {
                constraintangles.x(),
                constraintangles.y(),
                constraintangles.z()
            };
            in_writer.write_ordered_real(
                &(get_selector(selector_constraint_angles)),
                selector_names[selector_constraint_angles],
                values, 3 );
            in_writer.write_real(
                &(get_selector(selector_constraint_tensile)),
                selector_names[selector_constraint_tensile],
                assoc->get_constraint_tensile() );
            assoc = static_cast<const body_association*>(
                assoc->findNextLink( get_owner_nc() ));
/*
            if ( assoc != 0 )
            {
                get_owner_nc().write_newline_for_extension(
                    in_writer, *this, true ); // force extension id
            }
*/
        }
    }
    if ( errmsg != 0 )
    {
        logger::get_singleton().log_error(
            name_this_class, name_this_method, errmsg );
    }
#endif
}

//--------------------------------------

// virtual
object_identification &
property_set::get_identification_nc()
{
    return _identification;
}

//--------------------------------------

}; // end of namespace taxonomy

//--------------------------------------
//  template instantiations
//--------------------------------------

template class atoms::destroyer_typed<taxonomy::property_set>;
template class atoms::destroyer<taxonomy::property_set>;

//----------------------------------------------------------
// (end of file)
