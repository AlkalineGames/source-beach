#if !defined(BEACH_ATOMS_VIRTUAL_OBJECT)
#define      BEACH_ATOMS_VIRTUAL_OBJECT
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       virtual_object.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace atoms
{

//--------------------------------------

/// virtual object superclass
/**
 *  Common superclass for all objects that are virtual
 *  so that they can reveal their class through RTTI.
 */
class virtual_object
{
protected:

    virtual_object();
    virtual ~virtual_object();

}; // end of class virtual_object

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_VIRTUAL_OBJECT
