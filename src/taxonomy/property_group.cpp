//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_group.hpp> // this header

#include <atoms/stream_string.hpp>
#include <atoms/string.hpp>

namespace taxonomy
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text text_boolean_true[]   = "true";
static const text text_boolean_false[]  = "false";

static const text error_invalid_boolean_value[]
    = "invalid boolean value, valid values are: 'true','false', 't', 'f', '1', or '0'";

static const text error_cannot_change_property[]
    = "cannot change property";

static const text error_invalid_property_index[]
    = "invalid property index";

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
whole
property_group::get_property_count() const
{
    // !!! shouldn't be called, intended for override
    return 0;
}

//--------------------------------------

// virtual
const text **
property_group::get_property_names() const
{
    // !!! shouldn't be called, intended for override
    return 0;
}

//--------------------------------------

// virtual
stringex
property_group::get_property_value() const
{
    stream_string_o sso;
    sso << get_property_count() << " properties" << std::flush;
    return sso.str();
}

//--------------------------------------
//  protected methods
//--------------------------------------

property_group::property_group()
{}

//--------------------------------------

// virtual
property_group::~property_group()
{}

//--------------------------------------

// virtual
const property_group *
property_group::get_property_group(
    property_index ) const
{
    // !!! optional override
    return 0;
}

//--------------------------------------

// virtual
stringex
property_group::get_property_value(
    property_index ) const
{
    // !!! shouldn't be called, intended for override
    return 0;
}

//--------------------------------------

// virtual
boolean
property_group::set_property_value(
    property_index  in_index,
    const text *    in_value,
    stringex *      out_error_message )
{
    // !!! shouldn't be called, intended for override
    if ( out_error_message != 0 )
    {
        *out_error_message =
            "property_group::set_property_value(...) must be overridden.";
    }
    return false;
}

//--------------------------------------

// virtual
pointer
property_group::get_property_value_pointer(
    property_index in_index ) const
{
    // !!! can be overriden to improve performance
    // if not, convert from string value
    pointer value = 0;
    stream_string_i ssi( get_property_value( in_index ) );
    ssi >> value;
    return value;
}

//--------------------------------------

// virtual
real
property_group::get_property_value_scalar(
    property_index in_index ) const /// @deprecated
{
    // !!! can be overriden to improve performance
    // if not, convert from string value
    real value = 0;
    stream_string_i ssi( get_property_value( in_index ) );
    ssi >> value;
    return value;
}

//--------------------------------------

// virtual
boolean
property_group::set_property_value_pointer(
    property_index  in_index,
    pointer         in_value,
    stringex *      out_error_message )
{
    // !!! can be overriden to improve performance
    // if not, convert to string value
    stream_string_o sso;
    sso << std::hex << in_value;
    set_property_value( in_index, sso.str().c_str(), out_error_message );
    return true;
}

//--------------------------------------

const text *
property_group::get_boolean_text(
    boolean in_value ) const
{
    return in_value ? text_boolean_true : text_boolean_false;
}

//--------------------------------------

boolean
property_group::set_boolean_value(
    const text *    in_value,
    boolean &       out_value,
    stringex *      out_error_message ) const
{
    boolean succeeded;
    stringex value( in_value );
    value.to_lower();
    if (   (value.compare( "1"               ) == 0)
        || (value.compare( "t"               ) == 0)
        || (value.compare( text_boolean_true ) == 0) )
    {
        out_value = true;
        succeeded = true;
    }
    else if (   (value.compare( "0"                ) == 0)
             || (value.compare( "f"                ) == 0)
             || (value.compare( text_boolean_false ) == 0) )
    {
        out_value = false;
        succeeded = true;
    }
    else
    {
        if ( out_error_message != 0 )
        {
            *out_error_message = error_invalid_boolean_value;
        }
        succeeded = false;
    }
    return succeeded;
}

//--------------------------------------

void
property_group::set_error_cannot_change_property(
    stringex * out_error_message ) const
{
    if ( out_error_message != 0 )
    {
        *out_error_message = error_cannot_change_property;
    }
}

//--------------------------------------

void
property_group::set_error_invalid_property_index(
    stringex * out_error_message ) const
{
    if ( out_error_message != 0 )
    {
        *out_error_message = error_invalid_property_index;
    }
}

//--------------------------------------
//  private methods
//--------------------------------------

property_index
property_group::get_property_index(
    const text * in_name ) const
{
    whole count = get_property_count();
    const text ** names = get_property_names();
    for ( whole i = 0; i < count; i++ )
    {
        
        if ( strcasecmp( in_name, names[i] ) == 0 )
        {
            return i+1;
        }
    }
    return 0;
}

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
// (end of file)
