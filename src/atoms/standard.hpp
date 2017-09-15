#if !defined(BEACH_ATOMS_STANDARD)
#define      BEACH_ATOMS_STANDARD
//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       standard.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 *
 *  Provide necessary corrections prior to inclusion of any
 *  C++ Standard library headers.
 */
//----------------------------------------------------------

#undef ios // !!! iOS SDKs define this macro that collides with streams

//----------------------------------------------------------
#endif // BEACH_ATOMS_STANDARD
