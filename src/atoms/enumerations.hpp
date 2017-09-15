#if !defined(BEACH_ATOMS_ENUMERATIONS)
#define      BEACH_ATOMS_ENUMERATIONS
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       enumerations.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace atoms
{

//--------------------------------------

/// basis for change

enum change_basis
{
    no_change_basis,
    change_basis_added,
    change_basis_modified,
    change_basis_removed,
    change_basis_count
};

//--------------------------------------

/// invalid index value (inappropriate for unsigned)

enum { no_index = -1 };

//--------------------------------------

/// argument for non-initializing constructors

enum no_init_type { no_init };

//--------------------------------------

/// indicator of ownership of an object's lifetime
/**
 *  The owners are responsible for destroying objects.
 *  This is usually used as a parameter/attribute to indicate
 *  that the invoked object should take/does have ownership
 *  of some relevant object.
 */
enum ownership
{
    not_own_it, leave_ownership = not_own_it, ///< 0
    own_it,     take_ownership  = own_it      ///< 1
};

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_ENUMERATIONS
