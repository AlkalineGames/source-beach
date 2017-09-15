#if !defined(BEACH_NOTIFICATION_OBSERVER_FLAGS)
#define      BEACH_NOTIFICATION_OBSERVER_FLAGS

//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observer_flags.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>    

//--------------------------------------

namespace notification
{

//--------------------------------------

/// type that is binary compatible with enum.
/** actually a combination of bitwise enum values. */
typedef atoms::integer observer_flags;

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// $Log: observer_flags.hpp,v $
// Revision 1.2  2005/08/30 16:12:16  cat
// renamed sanddune to beach
//
// Revision 1.1  2003/07/30 02:12:36  cat
// extracted from observable.hpp into separate file
//----------------------------------------------------------

#endif // BEACH_NOTIFICATION_OBSERVER_FLAGS
