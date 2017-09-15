#if !defined(BEACH_ATOMS_CLAMP)
#define      BEACH_ATOMS_CLAMP
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       clamp.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, Shawn Barham
 */
//----------------------------------------------------------

namespace atoms
{

//--------------------------------------

/// clamp value to the specified range

template <class T>
inline T 
clamp(     T value, T min, T max )
{
    return ((value <  min) ? min
         : ((value >  max) ? max
         :   value));
}

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_CLAMP
