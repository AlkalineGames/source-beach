//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       reader.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/reader.hpp> // this header

#include <lifecycle/logger.hpp>

namespace serialization
{
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "reader";

//--------------------------------------
//  internal methods
//--------------------------------------

static
void
log_error_called(
    const text * in_method_name )
{
    logger::get_singleton().log_error(
        this_class_name, in_method_name,
        "abstract method should not be called." );
}

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
reader::~reader()
{}

//--------------------------------------

// virtual
boolean
reader::read_boolean(
    const selector *,
    const text *,
    boolean & )
{
    log_error_called( "read_boolean(...)" );
    return false;
}


//--------------------------------------

// virtual
boolean
reader::read_enum(
    const selector *,
    const text *,
    const text * [],
    whole,
    integer & )
{
    log_error_called( "read_enum(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_integer(
    const selector *,
    const text *,
    integer & )
{
    log_error_called( "read_integer(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_integer32(
    const selector *,
    const text *,
    integer32 & )
{
    log_error_called( "read_integer32(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_ordered_real(
    const selector *,
    const text *,
    real[],
    whole,
    whole )
{
    log_error_called( "read_ordered_real(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_ordered_whole(
    const selector *,
    const text *,
    whole[],
    whole )
{
    log_error_called( "read_ordered_whole(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_real(
    const selector *,
    const text *,
    real &,
    whole in_position_count)
{
    log_error_called( "read_ordered_real(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_string(
    const selector *,
    const text *,
    stringex &,
    whole in_position_count)
{
    log_error_called( "read_string(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_text(
    const selector *,
    const text *,
    text *,
    size_type )
{
    log_error_called( "read_text(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_whole(
    const selector *,
    const text *,
    whole & )
{
    log_error_called( "read_whole(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_whole16(
    const selector *,
    const text *,
    whole16 & )
{
    log_error_called( "read_whole16(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_whole32(
    const selector *,
    const text *,
    whole32 & )
{
    log_error_called( "read_whole32(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_whole64(
    const selector *,
    const text *,
    whole64 & )
{
    log_error_called( "read_whole64(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_object(
    const selector *,
    const text *,
    serializable * &,
    whole in_position_count)
{
    log_error_called( "read_object(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_root(
    serializable * &,
    serializable_source * )
{
    log_error_called( "read_root(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_root(
    context &,
    serializable * &,
    serializable_source * )
{
    log_error_called( "read_root(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_all(
    serializable & )
{
    log_error_called( "read_all(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_spec(
    const selector *,
    const text *,
    serializable_spec & )
{
    log_error_called( "read_spec(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_state(
    serializable & )
{
    log_error_called( "read_state(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_statement(
    serializable & )
{
    log_error_called( "read_statement(...)" );
    return false;
}

//--------------------------------------

// virtual
boolean
reader::read_value(
    const selector *,
    const text *,
    serializable & )
{
    log_error_called( "read_value(...)" );
    return false;
}

//--------------------------------------

// virtual
void
reader::add_dependency(
    serializable & )
{
    log_error_called( "add_dependency(...)" );
}

//--------------------------------------

// virtual
boolean
reader::has_field(
    const selector *,
    const text * )
{
    log_error_called( "had_field(...)" );
    return false;
}

//--------------------------------------

// @@@ SHOULD BE MADE INTO GENERIC PROPERTIES
//  ... get_properties() const
// virtual
boolean
reader::is_importing() const
{
    log_error_called( "is_importing(...)" );
    return false;
}

//--------------------------------------
//  protected methods
//--------------------------------------

reader::reader(
    const stringex * in_base_directory )
  :
    _base_directory( in_base_directory == 0 ? stringex::get_empty_string() : *in_base_directory )
{}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
