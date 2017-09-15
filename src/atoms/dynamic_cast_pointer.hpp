#if !defined(BEACH_ATOMS_DYNAMIC_CAST_POINTER)
#define      BEACH_ATOMS_DYNAMIC_CAST_POINTER
//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       dynamic_cast_pointer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <typeinfo>

/// macro to fix the GCC bug doing dynamic_cast<> across shared objects
/// !!! NOTE THAT THIS WILL ONLY DOWNCAST TO THE FINAL SUBTYPE
/// !!! NOT INTERMEDIATE SUBTYPES

#define DYNAMIC_CAST_POINTER(DOWNCAST_PTR,DOWNCAST_TYPE,OBJECT_PTR)\
if (   (OBJECT_PTR != 0)\
    && (atoms::stringex( typeid(*OBJECT_PTR  ).name() )\
                      == typeid(DOWNCAST_TYPE).name() ) )\
{\
    DOWNCAST_PTR = static_cast<DOWNCAST_TYPE*>(OBJECT_PTR);\
}\
else\
{\
    DOWNCAST_PTR = 0;\
}
 
//----------------------------------------------------------
#endif // BEACH_ATOMS_DYNAMIC_CAST_POINTER
