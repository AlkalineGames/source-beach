#if !defined(BEACH_NOTIFICATION_OBSERVABLE_ATOMS)
#define      BEACH_NOTIFICATION_OBSERVABLE_ATOMS

//----------------------------------------------------------
//  Copyright 2003-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_atoms.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <notification/observable_value.hpp>
#include <notification/observable_value_copycat.hpp>

//--------------------------------------

namespace notification
{
    using atoms::boolean;

//--------------------------------------

/// boolean that is observable
/**
 *  @note   design patterns applied:
 *              - Observer [GoF]
 */      
typedef observable_value<boolean> observable_boolean;

/// copycat of boolean that is observable
/**
 *  @note   design patterns applied:
 *              - Observer [GoF]
 */      
typedef observable_value_copycat<boolean> observable_boolean_copycat;

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// $Log: observable_atoms.hpp,v $
// Revision 1.5  2008/10/14 14:54:14  cat
// observable_boolean_copycat added
//
// Revision 1.4  2005/08/30 16:12:16  cat
// renamed sanddune to beach
//
// Revision 1.3  2003/07/30 02:16:13  cat
// renaming of all observer classes to lowercase+underscore naming convention
//
// Revision 1.2  2003/03/27 23:35:51  cat
// made observable string its own class
//
// Revision 1.1  2003/03/27 04:10:06  cat
// first writing
//----------------------------------------------------------

#endif // BEACH_NOTIFICATION_OBSERVABLE_ATOMS
