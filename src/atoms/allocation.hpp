#if !defined(BEACH_ATOMS_ALLOCATION)
#define      BEACH_ATOMS_ALLOCATION
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       allocation.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <new>

//--------------------------------------

namespace atoms
{
    enum allocation_placement { allocation };
};

//--------------------------------------

/// disable any new redefinition by OCEAN_DEBUG_NEW
#if defined(new)
#define BEACH_NEW_REDEFINED
#undef new
#endif

#ifndef BEACH_ALLOCATION_DEFAULT
#define BEACH_ALLOCATION (atoms::allocation,__FILE__,__LINE__)
#else
#define BEACH_ALLOCATION
#endif

#ifndef BEACH_ALLOCATION_DEFAULT
#define BEACH_COMMA_ALLOCATION ,atoms::allocation,__FILE__,__LINE__
#else
#define BEACH_COMMA_ALLOCATION
#endif

#ifndef BEACH_ALLOCATION_DEFAULT
#define BEACH_DELETE(TYPE,POINTER) if (POINTER!=0) POINTER->~TYPE(); ::operator delete(POINTER,BEACH_ALLOCATION);
#define BEACH_DELETE_WITHOUT_DESTRUCT(POINTER) ::operator delete(POINTER,BEACH_ALLOCATION);
#else
#define BEACH_DELETE(TYPE,POINTER) delete POINTER
#define BEACH_DELETE_WITHOUT_DESTRUCT(POINTER) delete POINTER
#endif

#ifndef BEACH_ALLOCATION_DEFAULT
/// @name global placement new operators
/**
 *  Alternatives to the standard non-placement new and delete operators.
 *
 *  Programs that do not use the Lifecycle framework, must link the
 *  additional atoms_allocation library that provides implementations
 *  for these operators, which simply allocate and deallocate bytes
 *  through calls to standard new and delete.
 *
 *  Programs that use the Lifecycle framework should NOT link the 
 *  additional atoms_allocation library as the the Lifecycle framework
 *  provides implementations for these operators that make use of the
 *  allocation_center.
 *
 *  This is achieved by EITHER:
 *
 *      client code calling placement new( BEACH_ALLOCATION ) X
 *      followed by its 'placement' delete via BEACH_DELETE(T,X)
 *  OR
 *      classes providing their own new and delete operators
 *      by declaring the macro BEACH_ALLOCATION_OPERATORS.
 */
//@{
void * operator new(
    std::size_t                     in_size,
    atoms::allocation_placement,
    const char *                    in_file,
    int                             in_line );

void * operator new[](
    std::size_t                     in_size,
    atoms::allocation_placement,
    const char *                    in_file,
    int                             in_line );
//@}

/// @name global 'placement' delete operators
/**
 *  These 'placement' delete operators merely match
 *  the placement new operators, they are NEVER called
 *  through normal use of global ::delete X. They 
 *  are only called by the class-based delete operators
 *  or via the BEACH_DELETE(T,X) macro */ 
//@{
void operator delete(
    void *                          in_pointer,
    atoms::allocation_placement,
    const char *                    in_file,
    int                             in_line );

void operator delete[](
    void *                          in_pointer,
    atoms::allocation_placement,
    const char *                    in_file,
    int                             in_line );
//@}
#endif // ! BEACH_ALLOCATION_DEFAULT

//--------------------------------------

#ifndef BEACH_ALLOCATION_DEFAULT

#define BEACH_ALLOCATION_OPERATOR_PLACEMENT_NEW_SINGLE \
void * operator new(\
    std::size_t                 n,\
    atoms::allocation_placement a,\
    const char *                file,\
    int                         line )\
{\
    return ::operator new( n, a, file, line );\
}
#define BEACH_ALLOCATION_OPERATOR_PLACEMENT_NEW_ARRAY \
void * operator new[](\
    std::size_t                 n,\
    atoms::allocation_placement a,\
    const char *                file,\
    int                         line )\
{\
    return ::operator new[]( n, a, file, line );\
}
#define BEACH_ALLOCATION_OPERATOR_NEW_SINGLE \
void * operator new( std::size_t n ) { return ::operator new( n, BEACH_ALLOCATION ); }

#define BEACH_ALLOCATION_OPERATOR_NEW_ARRAY \
void * operator new[]( std::size_t n ) { return ::operator new[]( n, BEACH_ALLOCATION ); }

#define BEACH_ALLOCATION_OPERATOR_DELETE_SINGLE \
void operator delete( void * p ) { ::operator delete( p, BEACH_ALLOCATION ); }

#define BEACH_ALLOCATION_OPERATOR_DELETE_ARRAY \
void operator delete[]( void * p ) { ::operator delete[]( p, BEACH_ALLOCATION ); }

#define BEACH_ALLOCATION_OPERATORS \
BEACH_ALLOCATION_OPERATOR_PLACEMENT_NEW_SINGLE \
BEACH_ALLOCATION_OPERATOR_PLACEMENT_NEW_ARRAY \
BEACH_ALLOCATION_OPERATOR_NEW_SINGLE \
BEACH_ALLOCATION_OPERATOR_NEW_ARRAY \
BEACH_ALLOCATION_OPERATOR_DELETE_SINGLE \
BEACH_ALLOCATION_OPERATOR_DELETE_ARRAY

#else // ! BEACH_ALLOCATION_DEFAULT

#define BEACH_ALLOCATION_OPERATORS

#endif // ! BEACH_ALLOCATION_DEFAULT

//--------------------------------------

#if 0 // !!! BREAKS COMPILATION 
#if defined(BEACH_NEW_REDEFINED)
#define new DEBUG_NEW 
#undef BEACH_NEW_REDEFINED
#endif
#endif

//----------------------------------------------------------
#endif // BEACH_ATOMS_ALLOCATION
