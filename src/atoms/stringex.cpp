//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stringex.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp> // this header

#include <atoms/destroyer.hpp>

#include <cstring>

namespace atoms
{

//--------------------------------------
//  public methods
//--------------------------------------

int
stringex::compare_case_insensitive(
    const value_type * s ) const
{
    size_type len = length();
    int index = 0;
    for ( ; index < len; index++ )
    {
        value_type lhschar = tolower( at( index ) );
        value_type rhschar = tolower( s[index] );
        if ( rhschar == 0 )
        {
            // matches all the way up to the length of rhs
            return (len-index); // positive value, difference in lengths    
        }
        if ( lhschar != rhschar )
        {
            // mismatch, return what basic_string<T>::compare should return
            //return traits_type::compare( &lhschar, &rhschar, 1 );
            return (lhschar-rhschar);
        }
    } 
    if ( s[index] != 0 )
    {
        // matches all the way up to the length of lhs, but rhs is longer
        return -1; 
    } 
    return 0;
}

//--------------------------------------

integer
stringex::starts_with(
    const char * in_text ) const
{
   //whole __len = std::min(get_size(),strlen(in_text));
   whole __len=(get_size()<strlen(in_text))?get_size():strlen(in_text);
   whole m = memcmp(get_text(), in_text, __len);
   if (m) return m;
   return 0;
}

//--------------------------------------

integer
stringex::starts_with(
    const stringex & n ) const
{
   //whole __len = std::min(get_size(),n.get_size());
   whole __len=(get_size()<n.get_size())?get_size():n.get_size();
   whole m = memcmp(get_text(), n.get_text(), __len);
   if (m) return m;
   return 0;
}

//--------------------------------------

stringex
stringex::right(
    size_t in_length ) const
{
    size_t totallen = get_size();
    if ( in_length >= totallen )
    {
        return *this;
    }
    stringex scopy( *this );
    scopy.erase( 0, totallen-in_length );
    return scopy;
}

//--------------------------------------

stringex &
stringex::to_lower()
{
    // first copy the data so that other
    // strings with the same data pointer
    // do not get modified.
    stringex temp;
    temp.assign( data(), get_length() );

    text * txt = temp.get_text_nc();
    for ( whole count = get_size();
          count > 0; count-- )
    {
        if ( (*txt >= 'A') && (*txt <= 'Z' ) )
        {
            *txt = (*txt - 'A') + 'a';
        }
        ++txt;
    }
    *this = temp;
    return *this;
}

//--------------------------------------

stringex &
stringex::to_upper()
{
    // first copy the data so that other
    // strings with the same data pointer
    // do not get modified.
    stringex temp;
    temp.assign( data(), get_length() );

    text * txt = temp.get_text_nc();
    whole count = get_size();
    while ( count > 0 )
    {
        if ( (*txt >= 'a') && (*txt <= 'z' ) )
        {
            *txt = (*txt - 'a') + 'A';
        }
        ++txt;
        --count;
    }
    *this = temp;
    return *this;
}

//--------------------------------------

stringex &
stringex::erase_leading_blanks()
{
    text * txt = get_text_nc();
    int count = 0;
    while ( *txt++ == ' ' ) count++;

    if ( count > 0 )
    {
        stringex temp;
        temp.assign( data(), get_length() );
        temp.erase( 0, count );
        *this = temp;
    }
    return *this;
}

//--------------------------------------

stringex &
stringex::erase_leading_whitespace()
{
    int count = 0;
    const char * str = c_str();
    while ( (*str == ' ') || (*str == 9) ||
            (*str == 10)  || (*str == 13) )
    {
        count++;
        str++;
    }
    if ( count > 0 )
    {
        stringex temp;
        temp.assign( data(), get_length() );
        temp.erase( 0, count );
        *this = temp;
    }
    return *this;
}

//--------------------------------------

stringex &
stringex::erase_trailing_blanks()
{
    int n = length();
    const char * str = c_str();
    while ( n )
    {
        if ( *(str + n - 1) == ' ' )
        {
            n--;
        }
        else
        {
            break;
        }
    }
    int spaces = length() - n;
    if ( spaces > 0 )
    {
        stringex temp;
        temp.assign( data(), get_length() );
        temp.erase( length() - spaces, spaces );
        *this = temp;
    }
    n = length();
    str = c_str();
    return *this;
}

//--------------------------------------

stringex &
stringex::erase_trailing_whitespace()
{
    int count = 0;
    const char * start = c_str();
    const char * str = start + length() - 1;
    while ( str >= start )
    {
        if ( (*str == ' ') || (*str == 9) ||
             (*str == 10)  || (*str == 13) )
        {
            count++;
            str--;
        }
        else
        {
            break;
        }
    }
    if ( count > 0 )
    {
        stringex temp;
        temp.assign( data(), get_length() );
        temp.erase( length() - count, count );
        *this = temp;
    }
    return *this;
}

//--------------------------------------

stringex &
stringex::find_erase(
    const stringex &    in_string,
    size_type           in_pos )
{
    size_type pos = find( in_string, in_pos );
    if ( pos != npos )
    {
        erase( pos, in_string.length() );
    }
}
    
//--------------------------------------

stringex
stringex::extract_prefix(
    text in_separator )
{
    stringex prefix;
    size_type pos = find( in_separator );
    if ( pos != npos )
    {
        prefix = substr( 0, pos );
        erase( 0, pos );
    }
    return prefix;
}

//--------------------------------------

}; // end of namespace atoms

//--------------------------------------
//  template instantiations
//--------------------------------------

template class atoms::destroyer_typed<atoms::stringex>;
template class atoms::destroyer<atoms::stringex>;

//----------------------------------------------------------
// (end of file)
