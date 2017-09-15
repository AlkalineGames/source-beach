#if !defined(CLASS_ID_BEACH)
#define      CLASS_ID_BEACH
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_id_beach.h
 *  @note       platform independent, Standard C++
 *  @author     Christopher Thames
 */
//----------------------------------------------------------

/// beach's ranges of static class ids

enum class_id_beach
{
    class_id_beach_first    = 20001, ///< !!! arbitrary value, below lifecycle's class_identifier_generation_offset
    class_id_beach_next     = class_id_beach_first + 1000
};

//----------------------------------------------------------
#endif // CLASS_ID_BEACH
