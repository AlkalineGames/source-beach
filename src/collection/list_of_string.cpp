//----------------------------------------------------------
//  Copyright 1999-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       list_of_string.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <collection/list_of_string.hpp> // this header

#include <cstring>

namespace collection
{

//--------------------------------------
//  internal methods
//--------------------------------------

static
bool 
parse_quoted_text( 
    const char *    text,
    int &           start,
    int &           len )
{
    start = 0;
    len = 0;

    const char * str = text;
    while ( (*str == ' ') || (*str == 9) ||
            (*str == 10)  || (*str == 13) ) str++;

    char quote_char = *str;
    if ( (quote_char != '\'') && (quote_char != '"') )
    {
        return false;
    }
    str++;
    const char * end = ::strchr( str, quote_char );
    if ( !end )
    {
        return false;
    }
    start = ( str - text );
    len = ( end - text ) - start;
    return true;
}

//--------------------------------------
//  public methods
//--------------------------------------

list_of_string::list_of_string() 
{}

//--------------------------------------

list_of_string::list_of_string(
    const list_of_string & rhs ) 
{ 
    *this = rhs; 
}

//--------------------------------------

const list_of_string & 
list_of_string::operator =(
    const list_of_string & rhs )
{
    *this = rhs;
}

//--------------------------------------

void 
list_of_string::add_parsed_list(
    const stringex & s )
{
    const char * text = s.c_str();
    while ( *text )
    {
        while ( (*text == ' ') || (*text == 9) || 
                (*text == ',') ) text++;

        // is it a quoted string?
        const char * end = 0;
        int start, len;
        int qtlen = 0;
        if ( parse_quoted_text( text, start, len ) )
        {
            text += start;
            end = text + len - 1;
            qtlen = 2;
        }
        if ( end == 0 )
            end = ::strchr(text,',');
        if ( end == 0 )
            end = ::strchr(text,' ');
        if ( end == 0 )
            end = text + ::strlen(text);
        const char * nb_end = end;
        while ( ( ( *nb_end == 0 ) || ( *nb_end == ' ') || 
                  ( *nb_end == 9 ) || (*nb_end == ',') ) &&
                (nb_end > text) ) nb_end--;
        stringex item(text,(nb_end-text+1));
        push_back( item );
        text = end + qtlen;
    }
}

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
// (end of file)
