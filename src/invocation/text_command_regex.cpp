//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_command_regex.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/text_command_regex.hpp> // this header

namespace invocation
{
    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
text_command_regex::~text_command_regex()
{
    if ( _owns_expression )
    {
        delete _regular_expression;
    }
}

//--------------------------------------

// virtual
boolean
text_command_regex::try_execute( // text_command override
    const text *    in_text,
    stringex &      out_result )
{
    if ( in_text == 0 )
    {
        return false;
    }
    SPString unparsed( in_text );
    SPStringList parsed; // !!! CONST CAST
    unparsed.m( const_cast<regular_expression&>(*_regular_expression), parsed );
    if ( parsed.count() > 1 )
    {
        execute_parsed( parsed, out_result );
        return true;
    }
    return false;
}

//--------------------------------------
//  protected methods
//--------------------------------------

text_command_regex::text_command_regex(
    const text *                in_name,
    const text *                in_help,
    const regular_expression &  in_command_expression )
 :
    text_command(               in_name, in_help ),
    _regular_expression(        &in_command_expression ),
    _owns_expression(           false )
{}

//--------------------------------------

text_command_regex::text_command_regex(
    const text *    in_name,
    const text *    in_help,
    const text *    in_regular_expression_text )
 :
    text_command( in_name, in_help ),
    _regular_expression(
        new regular_expression(
                in_regular_expression_text == 0 ? ""
              : in_regular_expression_text,
        regular_expression::nocase ) ),
    _owns_expression( true )
{}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
