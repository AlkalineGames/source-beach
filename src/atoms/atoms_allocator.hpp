#if !defined(BEACH_ATOMS_ATOMS_ALLOCATOR)
#define      BEACH_ATOMS_ATOMS_ALLOCATOR
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       allocator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

//--------------------------------------

/// allocator replacement for the C++ standard library
/*
 *  @note: objects using this allocator must not be declared with
 *          static storage duration if the allocation_center 
 *          and lifecycle_manager are used because the
 *          lifecycle_manager will be destroyed before
 *          the destructor of any such static declared objects.
 */
template <typename T>
class atoms_allocator
{
public:

    typedef const T*        const_pointer;
    typedef const T&        const_reference;
    typedef std::ptrdiff_t  difference_type;
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef std::size_t     size_type;

    template <class U> struct rebind
    {
        typedef atoms_allocator<U> other;
    };
    BEACH_ALLOCATION_OPERATORS

    atoms_allocator()
    {}
    atoms_allocator( const atoms_allocator & )
    {}
    template <class U> atoms_allocator( const atoms_allocator<U> & other )
    {}
    ~atoms_allocator()
    {}
    T * allocate( size_type n )
    {
        return reinterpret_cast<T*>(::operator new( n BEACH_COMMA_ALLOCATION ));
    }
    void * deallocate( T *p, size_type n )
    {
        ::operator delete( p BEACH_COMMA_ALLOCATION );
    }
    size_type max_size() const
    {
        return size_type(-1) / sizeof(value_type);
    }

}; // end of class atoms_allocator

//--------------------------------------

template <typename T, typename U>
inline
bool
operator ==(
    const atoms_allocator<T> &,
    const atoms_allocator<U> & )
{
    return true;
}

//--------------------------------------

template <typename T, typename U>
inline
bool
operator !=(
    const atoms_allocator<T> &,
    const atoms_allocator<U> & )
{
    return false;
}

//----------------------------------------------------------
#endif // BEACH_ATOMS_ATOMS_ALLOCATOR
