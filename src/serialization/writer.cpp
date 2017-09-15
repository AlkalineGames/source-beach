//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       writer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/writer.hpp> // this header

#include <lifecycle/logger.hpp>

namespace serialization
{
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "writer";

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
writer::~writer()
{}

//--------------------------------------

// virtual
void
writer::write_boolean(
    const selector *,
    const text *,
    boolean )
{
    log_error_called( "write_boolean(...)" );
}

//--------------------------------------

// virtual
void
writer::write_enum(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_names[],
    whole               in_name_count,
    integer             in_value )
{
    log_error_called( "write_enum(...)" );
}

//--------------------------------------

// virtual
void
writer::write_integer(
    const selector *,
    const text *,
    integer )
{
    log_error_called( "write_integer(...)" );
}

//--------------------------------------

// virtual
void
writer::write_integer32(
    const selector *,
    const text *,
    integer32 )
{
    log_error_called( "write_integer32(...)" );
}

//--------------------------------------

// virtual
void
writer::write_ordered_real(
    const selector *,
    const text *,
    const real[],
    whole )
{
    log_error_called( "write_ordered_real(...)" );
}

//--------------------------------------

// virtual
void
writer::write_ordered_whole( 
    const selector *,
    const text *,
    const whole[],
    whole )
{
    log_error_called( "write_ordered_whole(...)" );
}

//--------------------------------------

// virtual
void
writer::write_real(
    const selector *,
    const text *,
    real )
{
    log_error_called( "write_real(...)" );
}

//--------------------------------------

// virtual
void
writer::write_string(
    const selector *,
    const text *,
    const stringex & )
{
    log_error_called( "write_string(...)" );
}

//--------------------------------------

// virtual
void
writer::write_text(
    const selector *,
    const text *,
    const text * )
{
    log_error_called( "write_text(...)" );
}

//--------------------------------------

// virtual
void
writer::write_whole(
    const selector *,
    const text *,
    whole )
{
    log_error_called( "write_whole(...)" );
}

//--------------------------------------

// virtual
void 
writer::write_whole16(
    const selector *,
    const text *,
    whole16 )
{
    log_error_called( "write_whole16(...)" );
}

//--------------------------------------

// virtual
void
writer::write_whole32(
    const selector *,
    const text *,
    whole32 )
{
    log_error_called( "write_whole32(...)" );
}

//--------------------------------------

// virtual
void
writer::write_whole64( 
    const selector *,
    const text *,
    whole64 )
{
    log_error_called( "write_whole64(...)" );
}

//--------------------------------------

// virtual
void
writer::write_object(
    const selector *,
    const selector *,
    const text *,
    serializable * )
{
    log_error_called( "write_object(...)" );
}

//--------------------------------------

// virtual
void
writer::write_root(
    const selector *,
    serializable & )
{
    log_error_called( "write_root(...)" );
}

//--------------------------------------

// virtual
void
writer::write_root(
    context &,
    const selector *,
    serializable & )
{
    log_error_called( "write_root(...)" );
}

//--------------------------------------

// virtual
void
writer::write_all( 
    const selector *,
    serializable & )
{
    log_error_called( "write_all(...)" );
}

//--------------------------------------

// virtual
void
writer::write_spec( 
    const selector *,
    const text *,
    const serializable_spec & )
{
    log_error_called( "write_spec(...)" );
}

//--------------------------------------

// virtual
void
writer::write_value(
    const selector *,
    const selector *,
    const text *,
    serializable & )
{
    log_error_called( "write_value(...)" );
}

//--------------------------------------

// virtual
boolean
writer::write_newline()
{
    return false; // okay to call
}

//--------------------------------------
//  protected methods
//--------------------------------------

writer::writer()
{}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
