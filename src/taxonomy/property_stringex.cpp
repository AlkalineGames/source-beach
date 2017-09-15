//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_stringex.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_stringex.hpp> // this header

#include <atoms/stringex_conversion.hpp>

namespace taxonomy
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

property_stringex::property_stringex(
    const stringex & in_name,
    const stringex & in_default_value )
  :
    property_imp( in_name )
{
    _value = in_default_value;
}

//--------------------------------------

// virtual
property_stringex::~property_stringex()
{}

//--------------------------------------

// virtual
const stringex &
property_stringex::get_string(
    whole in_index ) const
{
    return _value;
}

//--------------------------------------

boolean 
property_stringex::to_boolean() const 
{ 
    return (       (_value.compare( "false" ) != 0)
            && (   (_value.compare( "true"  ) == 0)
                || (_value.compare( "TRUE"  ) == 0)
                || (_value.compare( "t"     ) == 0)
                || (_value.compare( "T"     ) == 0)
                || (_value.compare( "1"     ) == 0) ) );
}

//--------------------------------------

integer 
property_stringex::to_integer() const 
{ 
    integer result;
    stringex_conversion::to( result, _value );
    return result;
}

//--------------------------------------

real 
property_stringex::to_real() const 
{ 
    real result;
    stringex_conversion::to( result, _value );
    return result;
}

//--------------------------------------

whole 
property_stringex::to_whole() const 
{ 
    whole result;
    stringex_conversion::to( result, _value );
    return result;
}

//--------------------------------------

}; // end namespace taxonomy

//----------------------------------------------------------
// (end of file)
