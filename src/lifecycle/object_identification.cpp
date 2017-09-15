//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification.hpp>

#include <atoms/primitives.hpp>
#include <atoms/stream_string.hpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

#include <iomanip>

namespace lifecycle
{
    using namespace atoms;
        
//--------------------------------------
//  internal methods
//--------------------------------------

static const text this_class_name[]
    = "object_identification";

static const text text_regex_id[]
    = "[0-9]+";

static const text text_regex_name[]
    = ".+";

static const text text_separator_id_name[]
    = "-";

static const text text_name_undefined_name[]
    = "beach::lifecycle::object_identification::undefined_name";

static const object_identification::id_value
    undefined_id = 0;

static object_identification::name *
    undefined_name_cached = 0;

//--------------------------------------
//  public methods
//--------------------------------------

// static
object_identification::id_value
object_identification::get_undefined_id()
{
    return undefined_id;
}

//--------------------------------------

// static
const object_identification::name &
object_identification::get_undefined_name()
{
    return lifecycle::object_catalog_utility<object_identification::name,object_identification::name>
            ::acquire_object( text_name_undefined_name, &undefined_name_cached );
}
    
//--------------------------------------

// virtual 
object_identification::~object_identification()
{}

//--------------------------------------

// virtual
object_identification::id_value
object_identification::get_id() const
{
    return get_undefined_id();
}

//--------------------------------------

// virtual
const object_identification::name &
object_identification::get_name() const
{
    return get_undefined_name();
}

//--------------------------------------

// virtual
boolean
object_identification::has_id() const
{
    return false;
}

//--------------------------------------

// virtual
boolean
object_identification::has_name() const
{
    return false;
}
    
//--------------------------------------

boolean
object_identification::matches(
    const object_identification &   rhs,
    boolean                         rhs_name_is_regex ) const
{
    static const text this_method_name[]
        = "matches(...)";

    boolean doesmatch;
    do
    {
        boolean isidmatchdefined;
        if ( (! has_id()) || (! rhs.has_id()) )
        {
            isidmatchdefined = false;
        }
        else
        {
            id_value lhsid = get_id();
            id_value rhsid = rhs.get_id();
            if (   (lhsid == undefined_id) 
                || (rhsid == undefined_id) )
            {
                isidmatchdefined = false;
            }
            else if ( lhsid == rhsid )
            {
                isidmatchdefined = true;
            }
            else
            {
                doesmatch = false;
                break;
            }
        }
        if ( (! has_name()) || (! rhs.has_name()) )
        {
            doesmatch = isidmatchdefined;
            break;
        }
        const name & lhsname = get_name();
        const name & rhsname = rhs.get_name();
        if (   (lhsname == get_undefined_name())
            || (rhsname == get_undefined_name()) )
        {
            doesmatch = isidmatchdefined;
            break;
        }
        if ( rhs_name_is_regex )
        {
            expression::SPString spstr( get_name() );
            doesmatch = (spstr.m( rhsname, "i" ) != 0);
        }
        else
        {
            doesmatch = (lhsname == rhsname);
        }
    }
    while ( false );
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        stringex logmsg( "ident <" );
        logmsg += this->make_formatted_string( false );
        logmsg += "> ";
        logmsg += doesmatch ? "MATCHES" : "DOES NOT MATCH";
        logmsg += " <";
        logmsg += rhs.make_formatted_string( rhs_name_is_regex );
        logmsg += ">";
        log.log_trace( this_class_name, this_method_name, logmsg );
    }
    return doesmatch;
}

//--------------------------------------

boolean 
object_identification::regex_name_matches(
    const name & in_name ) const
{
    expression::SPString spstr( in_name );
    boolean doesmatch = (spstr.m( get_name(), "i" ) != 0);
    return doesmatch;
}

//--------------------------------------

// virtual
void
object_identification::set_id(
    id_value )
{
    // do nothing; intended for override
}

//--------------------------------------

// virtual
void
object_identification::set_id_name(
    id_value        in_id,
    const name &    in_name )
{
    set_id(         in_id );
    set_name(       in_name );
}

//--------------------------------------

// virtual
void
object_identification::set_name(
    const name & )
{
    // do nothing; intended for override
}

//--------------------------------------

stringex
object_identification::make_formatted_string(
    boolean in_use_regex ) const
{
    stream_string_o sso;
    boolean hasid   = has_id();
    boolean hasname = has_name();
    if ( hasid )
    {
        id_value id = get_id();
        if ( (id == 0) && in_use_regex )
        {
            sso << text_regex_id;
        }
        else
        {
            sso << std::setiosflags(
                    std::ios_base::right )
                << std::setfill( '0' )
                << std::setw( 10 ) // single-digit billions
                << id;
        }
        if ( hasname )
        {
            sso << text_separator_id_name;
        }
    }
    if ( hasname )
    {            
        const stringex & nam = get_name();
        if ( ! nam.is_empty() )
        {
            sso << nam;
        }
        else if ( in_use_regex )
        {
            sso << text_regex_name;
        }
    }        
    return sso.str();
}

//--------------------------------------

void
object_identification::parse_formatted_string(
    const stringex & in_formatted_string )
{
    id_value id;
    name nam; 
    boolean hasid   = has_id();
    boolean hasname = has_name();
    expression::SPString regexstr;
    if ( hasid )
    {            
        regexstr += "(";
        regexstr += text_regex_id;
        regexstr += ")";
        if ( hasname )
        {
            regexstr += text_separator_id_name;
        }
    }
    if ( hasname )
    {            
        regexstr += "(";
        regexstr += text_regex_name;
        regexstr += ")";
    }
    expression::SPString parsingstring(
        in_formatted_string );
    expression::SPStringList parsedlist;
    parsingstring.m(
        regexstr, parsedlist );

    if ( hasid && (parsedlist.count() > 1) )
    {
        std::istringstream iss(
            stringex( parsedlist[1] ).get_text() );
        iss >> id;
    }            
    else
    {
        id = undefined_id;        
    }        
    if ( hasname && (parsedlist.count() > 1) )
    {
        if ( parsedlist.count() > 2 )
        {
            nam = parsedlist[2];
        } 
        else
        {
            nam = parsedlist[1];
        } 
    }
    else
    {
        nam = get_undefined_name();
    }
    set_id_name( id, nam );
}

//--------------------------------------
//  protected methods
//--------------------------------------

object_identification::object_identification()
{}

//--------------------------------------

object_identification::object_identification(
    const object_identification & )
{}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
