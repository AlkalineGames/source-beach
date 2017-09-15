#if !defined(BEACH_ATOMS_STRINGEX_CONVERSION)
#define      BEACH_ATOMS_STRINGEX_CONVERSION
//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stringex_conversion.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace atoms
{

//--------------------------------------

/// string conversion utility
/**
 *  Numeric conversions support a base of
 *  2 (binary), 8 (octal), 10 (decimal), or 16 (hexidecimal).
 */
class stringex_conversion
{
public:

    static stringex         from(   integer8        , whole8 in_base = 10 );
    static stringex         from(   integer16       , whole8 in_base = 10 );
    static stringex         from(   integer32       , whole8 in_base = 10 );
    static stringex         from(   integer64       , whole8 in_base = 10 );
    static stringex         from(   integer_machine , whole8 in_base = 10 );
    static stringex         from(   whole8          , whole8 in_base = 10 );
    static stringex         from(   whole16         , whole8 in_base = 10 );
    static stringex         from(   whole32         , whole8 in_base = 10 );
    static stringex         from(   whole64         , whole8 in_base = 10 );
    static stringex         from(   whole_machine   , whole8 in_base = 10 );
    static stringex         from(   pointer         , whole8 in_base = 16 );
    static stringex         from(   pointer_to_const, whole8 in_base = 16 );
    static stringex         from(   real32          , whole8 in_base = 10 );
    static stringex         from(   real64          , whole8 in_base = 10 );
    static stringex         from(   real80          , whole8 in_base = 10 );
    static stringex         from(   boolean         , boolean in_as_number = false, boolean in_as_letter = false );
                        
    static integer8         to(     integer8         &, const text *, whole8 in_base = 10 );
    static integer16        to(     integer16        &, const text *, whole8 in_base = 10 );
    static integer32        to(     integer32        &, const text *, whole8 in_base = 10 );
    static integer64        to(     integer64        &, const text *, whole8 in_base = 10 );
    static integer_machine  to(     integer_machine  &, const text *, whole8 in_base = 10 );
    static whole8           to(     whole8           &, const text *, whole8 in_base = 10 );
    static whole16          to(     whole16          &, const text *, whole8 in_base = 10 );
    static whole32          to(     whole32          &, const text *, whole8 in_base = 10 );
    static whole64          to(     whole64          &, const text *, whole8 in_base = 10 );
    static whole_machine    to(     whole_machine    &, const text *, whole8 in_base = 10 );
    static pointer          to(     pointer          &, const text *, whole8 in_base = 16 );
    static pointer_to_const to(     pointer_to_const &, const text *, whole8 in_base = 16 );
    static real32           to(     real32           &, const text *, whole8 in_base = 10 );
    static real64           to(     real64           &, const text *, whole8 in_base = 10 );
    static real80           to(     real80           &, const text *, whole8 in_base = 10 );
    static boolean          to(     boolean          &, const text *, whole8 in_base = 10 );

}; // end of class stringex

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_STRINGEX_CONVERSION
