//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_list_of_string.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stream_string.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/logger.hpp>
#include <notification/observable_list.tpp>
#include <notification/observable_list_of_string.hpp>

namespace notification
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "observable_list_of_string";

//--------------------------------------
//  public methods
//--------------------------------------

observable_list_of_string::observable_list_of_string()
  :
    observable_list_of_string_superclass()
{}

//--------------------------------------

observable_list_of_string::observable_list_of_string(
    ownership in_ownership )
  :
    observable_list_of_string_superclass( in_ownership )
{}

//--------------------------------------

// virtual
observable_list_of_string::~observable_list_of_string()
{}

//--------------------------------------

stringex
observable_list_of_string::to_string()
{
    stringex str;
    for ( list::iterator i( _list.begin() ); i != _list.end(); i++ )
    {
        str += *i;
        str += "\n";
    }
    return str;
}

//--------------------------------------

void
observable_list_of_string::parse_string_into_elements(
    const stringex & in_string )
{
    static const text this_method_name[]
        = "parse_string_into_elements(...)";

    boolean isdone = false;
    int startpos = 0;
    do
    {
        int stoppos = in_string.find_first_of( "\r\n", startpos );
        if ( stoppos < 0 )
        {
            isdone = true;
            stoppos = in_string.length();
        }
        if ( startpos < stoppos )
        {
            stringex * slice = new stringex(
                in_string.substr( startpos, (stoppos - startpos) ) );
            add( *slice );
            logger & log = logger::get_singleton();
            if ( log.is_including( this_class_name ) )
            {
                stream_string_o sso;
                sso << "size==" << _list.size()
                    << ", added \"" << *slice << '"';
                log.log_trace( this_class_name, this_method_name,
                    sso.str().c_str() );
           }
        }
        startpos = stoppos+1;
    }
    while ( ! isdone );
}

//--------------------------------------

}; // end of namespace notification

//--------------------------------------
//  template instantiations
//--------------------------------------

template class notification::observable_list<atoms::stringex>;

//----------------------------------------------------------
// (end of file)
