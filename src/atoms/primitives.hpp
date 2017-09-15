#if !defined(BEACH_ATOMS_PRIMITIVES)
#define      BEACH_ATOMS_PRIMITIVES
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       primitives.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/standard.hpp>

#include <cstddef>

/// Beach Atoms Framework
namespace atoms
{

//--------------------------------------

typedef int                 integer;    ///< integer  -2,147,483,648..2,147,483,647
typedef char                integer8;   ///< integer            -128..127
typedef short               integer16;  ///< integer         -32,768..32,767
typedef int                 integer32;  ///< integer  -2,147,483,648..2,147,483,647
typedef long long           integer64;  ///< integer  (really small)..(really big)
typedef long                integer_machine;    ///< -(machine size)..(machine size)

typedef unsigned int        whole;      ///< whole number 0..4,294,967,295
typedef unsigned char       whole8;     ///< whole number 0..255
typedef unsigned short      whole16;    ///< whole number 0..65,535
typedef unsigned int        whole32;    ///< whole number 0..4,294,967,295
typedef unsigned long long  whole64;    ///< whole number 0..(really big)
typedef unsigned long       whole_machine;      ///<      0..(machine size)

typedef void *              pointer;
typedef const void *        pointer_to_const;

typedef float               real;       ///< real number (machine size)
typedef float               real32;     ///< real number 32 bits == 3.4 x 10^+/-38
typedef double              real64;     ///< real number 64 bits == 1.7 x 10^+/-308
typedef long double         real80;     ///< real number 80 bits == 3.4 x 10^+/-4932

typedef char                text;           ///< default text character type
typedef wchar_t             text_wide;      ///< wide    text character type
typedef char                text_ascii;     ///< ASCII   text character type
typedef unsigned short      text_unicode;   ///< UNICODE text character type

typedef bool                boolean;    ///< Standard C++ equivalent
typedef whole8              byte;
typedef unsigned int        size_type;          ///< !!! 32-bit
typedef std::size_t         size_type_machine;  ///< !!! may be 64-bit

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_PRIMITIVES
