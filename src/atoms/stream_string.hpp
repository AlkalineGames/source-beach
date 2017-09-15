#if !defined(BEACH_ATOMS_STREAM_STRING)
#define      BEACH_ATOMS_STREAM_STRING
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stream_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/atoms_allocator.hpp>
#include <atoms/standard.hpp>

#include <sstream>

namespace atoms
{

//--------------------------------------

/// input string stream using our allocator and compatible with stringex's superclass
typedef std::basic_istringstream<char,std::char_traits<char>,atoms_allocator<char> >
    stream_string_i;

/// output string stream using our allocator and compatible with stringex's superclass
typedef std::basic_ostringstream<char,std::char_traits<char>,atoms_allocator<char> >
    stream_string_o;

/// bidirectional string stream using our allocator and compatible with stringex's superclass
typedef std::basic_stringstream<char,std::char_traits<char>,atoms_allocator<char> >
    stream_string_io;

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_STREAM_STRING
