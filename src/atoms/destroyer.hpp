#if !defined(BEACH_ATOMS_DESTROYER)
#define      BEACH_ATOMS_DESTROYER
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       destroyer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

namespace atoms
{

//--------------------------------------

/// interface for the concrete destroyer templates
/**
 *  @note   design patterns applied:
 *              - Prototype [GoF]
 */
class destroyer_interface
{
public:

    BEACH_ALLOCATION_OPERATORS

    virtual destroyer_interface * clone() const = 0;
    virtual void destroy( void * ) = 0;
};

//--------------------------------------

/// template interface for the concrete destroyer templates
/**
 *  @note   design patterns applied:
 *              - Prototype [GoF]
 */
template <typename T>
class destroyer_typed
    : public destroyer_interface
{};

//--------------------------------------

/// template for a destroyer of another object that calls its destructor
/**
 *  @note   design patterns applied:
 *              - Prototype [GoF]
 */
template <typename T>
class destroyer
    : public destroyer_typed<T>
{
public:

    destroyer() {}

    /// @name interface implementation
    //@{
    virtual destroyer * clone() const
    {
        return new destroyer<T>;
    }
    virtual void destroy( void * ptr )
    {
        if ( ptr != 0 )
        {
            BEACH_DELETE(T,static_cast<T*>(ptr));
        }
    }
    //@}
};

//--------------------------------------

/// template for a destroyer of another object that calls a destruction function
/**
 *  @note   design patterns applied:
 *              - Prototype [GoF]
 */
template <typename T>
class destroyer_function
    : public destroyer_typed<T>
{
public:

    typedef void (*function_pointer)( T & );

    destroyer_function( function_pointer fp )
        : _function_pointer( fp ) {}

    /// @name interface implementation
    //@{
    virtual destroyer_function * clone() const
    {
        return new destroyer_function<T>( *this );
    }
    virtual void destroy( void * ptr )
    {
        if ( ptr != 0 )
        {
            (*_function_pointer)( *static_cast<T*>(ptr) );
        }
    }
    //@}

private:

    function_pointer _function_pointer;
};

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_DESTROYER
