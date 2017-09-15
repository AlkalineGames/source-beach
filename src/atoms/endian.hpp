#if !defined(BEACH_ATOMS_ENDIAN)
#define      BEACH_ATOMS_ENDIAN
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       endian.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace atoms
{

//--------------------------------------

template <class T>
inline
T
inverse_endian(
    T value )
{
    const size_type n = sizeof(value);
    byte * bytes = reinterpret_cast<byte*>(&value);
    for ( integer i = 0; i < (n>>1); i++ )
    {
        byte temp = bytes[i];
        bytes[i] = bytes[n-i-1];
        bytes[n-i-1] = temp;
    }
    return value;
}

//----------------------------------------------------------

template <class T>
inline
void
invert_endian(
    T & value )
{
    const size_type n = sizeof(value);
    byte * bytes = reinterpret_cast<byte*>(&value);
    for ( integer i = 0; i < (n>>1); i++ )
    {
        byte temp = bytes[i];
        bytes[i] = bytes[n-i-1];
        bytes[n-i-1] = temp;
    }
}

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_ENDIAN
