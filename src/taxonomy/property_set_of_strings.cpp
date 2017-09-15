//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_set_of_strings.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_set_of_strings.hpp> // this header

#include <atoms/destroyer.hpp>
#include <atoms/stream_string.hpp>
#include <collection/ref_vector.hpp>
#include <lifecycle/logger.hpp>
#include <taxonomy/property_stringex.hpp>

#include <cstring>

namespace taxonomy
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

typedef const text * const_text_pointer;
typedef class collection::ref_vector<property_stringex> properties;

//--------------------------------------

class property_set_of_strings_rep
{
public:

    property_set_of_strings_rep()
      :
        _property_names( 0 ),
        _properties( destroyer<property_stringex>() )
    {}
    ~property_set_of_strings_rep()
    {
        delete [] _property_names;
    }
    const_text_pointer *    _property_names;
    properties              _properties;
};

//--------------------------------------

static const text this_class_name[]
    = "property_set_of_strings";

static const text error_invalid_property_index[]
    = "invalid property index";

//--------------------------------------
//  public methods
//--------------------------------------

property_set_of_strings::property_set_of_strings()
  :
    _rep( *(new property_set_of_strings_rep) )
{}

//--------------------------------------

// virtual
property_set_of_strings::~property_set_of_strings()
{
    delete &_rep;
}

//--------------------------------------

property_stringex &
property_set_of_strings::create_property(
    const stringex & in_name,
    const stringex & in_value )
{
    static const text name_this_method[]
        = "create_property(...)";

    // ensure property doesn't already exist
    for ( properties::iterator
          i  = _rep._properties.begin();
          i != _rep._properties.end();
          ++i )
    {
        property_stringex & prop = *i;
        if ( prop.get_name().compare_case_insensitive(
                in_name.get_text() ) == 0 )
        {
            stringex msg( "property already exists with name '" );
            msg += prop.get_name();
            msg += "'";
            logger::get_singleton().log_error(
                this_class_name, name_this_method, msg );
            return prop;
        }
    }
    property_stringex * prop =
        new property_stringex(
            in_name.get_text(), in_value );
    _rep._properties.add( *prop );

    // reallocate array of text pointers
    whole newcount = _rep._properties.size();
    whole oldcount = newcount - 1;
    const_text_pointer * newarray
        = new const_text_pointer[newcount];
    if ( _rep._property_names != 0 )
    {
        memcpy( newarray, _rep._property_names,
            oldcount*sizeof(const_text_pointer) );
        delete [] _rep._property_names;
    }
    _rep._property_names = newarray;
    _rep._property_names[oldcount] = prop->get_name();
    return *prop;
}

//--------------------------------------

// virtual
whole
property_set_of_strings::get_property_count() const
{
    return _rep._properties.size();
}

//--------------------------------------

// virtual
const text **
property_set_of_strings::get_property_names() const
{
    return _rep._property_names;
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
stringex
property_set_of_strings::get_property_value(
    property_index in_index ) const
{
    if ( (in_index == 0) || (in_index > _rep._properties.size()) )
    {
        return stringex::get_empty_text();
    }
    return _rep._properties[in_index-1].get_value();
}

//--------------------------------------

// virtual
boolean
property_set_of_strings::set_property_value(
    property_index  in_index,
    const text *    in_value,
    stringex *      out_error_message )
{
    if ( (in_index == 0) || (in_index > _rep._properties.size()) )
    {
        if ( out_error_message != 0 )
        {
            *out_error_message = error_invalid_property_index;
        }
        return false;
    }
    _rep._properties[in_index-1].set_value( in_value );
    return true;
}

//--------------------------------------

// virtual
real
property_set_of_strings::get_property_value_scalar(
    property_index in_index ) const
{
    if ( (in_index == 0) || (in_index > _rep._properties.size()) )
    {
        return 0;
    }
    stream_string_i ssi( _rep._properties[in_index-1].get_value() );
    real value;
    ssi >> value;
    return value;
}

//--------------------------------------

}; // end of namespace taxonomy

//--------------------------------------
//  template instantiations
//--------------------------------------

template class atoms::destroyer_typed<taxonomy::property_stringex>;
template class atoms::destroyer<taxonomy::property_stringex>;

//----------------------------------------------------------
// (end of file)
