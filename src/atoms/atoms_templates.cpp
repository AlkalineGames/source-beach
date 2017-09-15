//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       string_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/atoms_allocator.hpp>
#include <atoms/standard.hpp>

template class atoms_allocator<char>;

#include <string>

template class std::basic_string<char,std::char_traits<char>,atoms_allocator<char> >;

#include <sstream>

template class std::basic_istringstream<char,std::char_traits<char>,atoms_allocator<char> >;
template class std::basic_ostringstream<char,std::char_traits<char>,atoms_allocator<char> >;
template class std::basic_stringstream<char,std::char_traits<char>,atoms_allocator<char> >;

template
std::basic_ostream<char,std::char_traits<char> > &
std::operator <<(
    std::basic_ostream<char,std::char_traits<char> >&,
    std::basic_string<char,std::char_traits<char>,atoms_allocator<char> > const&);

//--------------------------------------

#if defined(STLPORT)

// !!! STLport: this code was based on src/string.cpp

_STLP_BEGIN_NAMESPACE

_STLP_MOVE_TO_PRIV_NAMESPACE

template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<char*, char, atoms_allocator<char> >;
template class _STLP_CLASS_DECLSPEC _String_base<char, atoms_allocator<char> >;

_STLP_MOVE_TO_STD_NAMESPACE

template class _STLP_CLASS_DECLSPEC basic_string<char, char_traits<char>, atoms_allocator<char> >;

// !!! STLport: this code was based on src/ostream.cpp

template
bool
_STLP_CALL __stlp_string_fill(
    basic_ostream<char, char_traits<char> > &,
    basic_streambuf<char, char_traits<char> > *,
    streamsize );

template
basic_ostream<char, char_traits<char> > &
_STLP_CALL operator<<(
    basic_ostream<char, char_traits<char> > &,
    const basic_string<char, char_traits<char>, allocator<char> > & );

template
basic_istream<char, char_traits<char> > &
_STLP_CALL operator >>(
    basic_istream<char, char_traits<char> > &,
    basic_string<char, char_traits<char>, allocator<char> > & );

template
basic_istream<char, char_traits<char> > &
_STLP_CALL getline(
    basic_istream<char, char_traits<char> > &,
    basic_string<char, char_traits<char>, allocator<char> > &,
    char );

#ifndef _STLP_NO_WCHAR_T

template
bool
_STLP_CALL __stlp_string_fill(
    basic_ostream<wchar_t, char_traits<wchar_t> > &,
    basic_streambuf<wchar_t, char_traits<wchar_t> > *,
    streamsize );

template
basic_ostream<wchar_t, char_traits<wchar_t> > & _STLP_CALL
operator<<(basic_ostream<wchar_t, char_traits<wchar_t> > &,
           const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > & );

template
basic_istream<wchar_t, char_traits<wchar_t> > & _STLP_CALL
operator>>(basic_istream<wchar_t, char_traits<wchar_t> > &,
           basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > & );

template
basic_istream<wchar_t, char_traits<wchar_t> > & _STLP_CALL
getline(basic_istream<wchar_t, char_traits<wchar_t> > &,
        basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > &,
        wchar_t );

#endif

_STLP_END_NAMESPACE

//--------------------------------------

#endif // defined(STLPORT)

//----------------------------------------------------------
// (end of file)
