//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       coordinates.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/coordinates.hpp> // this header

#include <atoms/stream_string.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

namespace geometry
{
    using namespace atoms;
    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text orderedAttributeSyntaxHead[]
    = "{([^/},]+)";

static const text orderedAttributeSyntaxExtra[]
    = "(/[^/},]+)?";

static const text orderedAttributeSyntaxTail[]
    = "}";

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
void
coordinates_xyz<T>::from_string(
    const stringex & in_string )
{
    zero();
    SPString parseString( in_string );
    SPStringList valueList;
    SPString syntax = orderedAttributeSyntaxHead;
    for ( whole i = 1; i < 3; i++ )
    {
        syntax += orderedAttributeSyntaxExtra;
    }
    syntax += orderedAttributeSyntaxTail;
    regular_expression re( syntax, regular_expression::nocase );
    parseString.m( re, valueList );
    whole parseCount = valueList.count();
    if ( parseCount > 1 )
    {
        --parseCount;
        for ( whole i = 0; (i < 3) && (i < parseCount); i++ )
        {            
            char strip;
            stringex value( valueList[i+1] );
            stream_string_i valueStream( value );
            if ( i > 0 ) // remove leading separator
            {
                valueStream >> strip;
            }
            if ( i == 0 )
            {
                valueStream >> _x;
            }
            else if ( i == 1 )
            {
                valueStream >> _y;
            }
            else 
            {
                valueStream >> _z;
            }
        }
    }
}

//--------------------------------------

template <class T>
stringex
coordinates_xyz<T>::make_formatted_string(
    boolean in_cdl_format ) const
{
    stream_string_o sso;
    if ( in_cdl_format )
    {
        sso << '{' << _x << '/' << _y << '/' << _z << '}' << std::flush;
    }
    else
    {
        sso << '(' << _x << ',' << _y << ',' << _z << ')' << std::flush;
    }
    return sso.str();
}

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
