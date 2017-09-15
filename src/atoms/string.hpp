#if !defined(BEACH_ATOMS_STRING)
#define      BEACH_ATOMS_STRING
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>

#include <cstring> // ANSI C equivalent library

//--------------------------------------

// our implementation of POSIX <strings.h> strcasecmp(...)
 
inline int
strcasecmp(
    const char * s1,
    const char * s2 )
{
    size_t i = 0;
    int c1, c2;
    do
    {
        c1 = tolower( s1[i] );
        c2 = tolower( s2[i] );
        i++;
        if ( c1 < c2 )
        {
            return -i;
        }
        if ( c1 > c2 )
        {
            return i;
        }
    }
    while( c1 != 0 );
    return 0;
}

//--------------------------------------

// our implementation of POSIX <strings.h> strncasecmp(...)

inline int
strncasecmp(
    const char * s1,
    const char * s2,
    size_t       n )
{
    size_t i = 0;
    int c1, c2;
    do
    {
        c1 = tolower( s1[i] );
        c2 = tolower( s2[i] );
        i++;
        if ( c1 < c2 )
        {
            return -i;
        }
        if ( c1 > c2 )
        {
            return i;
        }
    }
    while ( (c1 != 0) && (i < n) );
    return 0;
}

//--------------------------------------

/// replacement for dangerous strncmp()

inline char *
strncpyex(
    char *          dest,
    const char *    source,
    size_t          count )
{
    char * ptr = ::strncpy( dest, source, count );
    dest[count-1] = '\0';
    return ptr;
}

//--------------------------------------

/// deprecated synonym (in global namespace)

typedef atoms::stringex String;

//----------------------------------------------------------
#endif // BEACH_ATOMS_STRING
