//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       allocation.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp> // this header

#include <atoms/primitives.hpp>

//--------------------------------------
//  global operators
//--------------------------------------

// disable any new redefinition by OCEAN_DEBUG_NEW
#if defined(new)
#define BEACH_NEW_REDEFINITION new
#undef new
#endif

//--------------------------------------

void *
operator new(
    std::size_t                 in_size,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    void * pointer = new atoms::byte[in_size];
    return pointer;
}

//--------------------------------------

void *
operator new[](
    std::size_t                 in_size,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    void * pointer = new atoms::byte[in_size];
    return pointer;
}

//--------------------------------------

void
operator delete(
    void *                      in_pointer,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    if ( in_pointer != 0 )
    {
        delete [] static_cast<atoms::byte*>(in_pointer);
    }
}

//--------------------------------------

void
operator delete[](
    void *                      in_pointer,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    if ( in_pointer != 0 )
    {
        delete [] static_cast<atoms::byte*>(in_pointer);
    }
}

//--------------------------------------

#if defined(BEACH_NEW_REDEFINITION)
#define new BEACH_NEW_REDEFINITION
#endif

//----------------------------------------------------------
// (end of file)
