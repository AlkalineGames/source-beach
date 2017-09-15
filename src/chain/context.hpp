#if !defined(BEACH_ATOMS_CALL_CONTEXT)
#define      BEACH_ATOMS_CALL_CONTEXT
//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       context.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/linked.hpp>

namespace chain
{
    class context_linked;

//--------------------------------------

/// encapsulated context for any purpose
/**
 *  A linked-list of subclassed objects provides all of the context. 
 *
 *  Originally designed for an encapsulated context parameter 
 *  passed across method calls, a context can be used for anything.
 * 
 *  @note   design patterns applied:
 *              - Encapsulated Context [PLoP5]
 */
class context
{
public:

    BEACH_ALLOCATION_OPERATORS

    context()                            : _first( 0 ) {}
    context( context_linked & in_first ) : _first( &in_first ) {}

    const context_linked * find_first() const { return _first; } 
          context_linked * find_first_nc()    { return _first; } 

    const context_linked * find(    linked::class_identity cid ) const;
          context_linked * find_nc( linked::class_identity cid )
    {
        return const_cast<context_linked*>(find( cid ));
    }
    void append( context_linked & in_context_linked );

private:

    context_linked * _first;

}; // end of class template context

//--------------------------------------

/// abtract superclass for linked context objects
/**
 *  @note   design patterns applied:
 *              - Encapsulated Context [PLoP5]
 */
class context_linked
    : public linked
{
public:

    /// @name templates for the subclassing protocol
    //@{
    template <class T> static const T * cast_from(
        const linked & in_linked )
    {
        return (in_linked.get_class_id() == T::acquire_class_id())
            ? static_cast<const T*>(&in_linked) : 0;
    }
    template <class T> static T * cast_from_nc(
        linked & in_linked )
    {
        return const_cast<T*>(T::cast_from( in_linked ));
    }
    template <class T> static const T * find_in(
        const context & in_context )
    {
        return static_cast<const T*>(
            in_context.find( T::acquire_class_id() ));
    }
    template <class T> static T * find_in_nc(
        context & in_context )
    {
        return const_cast<T*>(T::find_in( in_context ));
    }
    //@}

    /// @name subtyped overloads
    //@{
    const context_linked *  get_next() const                            { return static_cast<const context_linked*>(linked::get_next()); }
          context_linked *  get_next_nc()                               { return static_cast<      context_linked*>(linked::get_next_nc()); }
    const context_linked &  get_last() const                            { return static_cast<const context_linked&>(linked::get_last()); }
          context_linked &  get_last_nc()                               { return static_cast<      context_linked&>(linked::get_last_nc()); }
    const context_linked *  find(           class_identity cid ) const  { return static_cast<const context_linked*>(linked::find( cid )); }
          context_linked *  find_next_nc(   class_identity cid )        { return static_cast<      context_linked*>(linked::find_nc( cid )); }
    void                    append(         context_linked & cl )       { linked::append( cl ); }
    //@}

    context_linked( class_identity );
    
}; // end of class context_linked

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_ATOMS_CALL_CONTEXT
