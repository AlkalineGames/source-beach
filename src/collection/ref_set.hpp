#if !defined(BEACH_COLLECTION_REF_SET)
#define      BEACH_COLLECTION_REF_SET
//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_set.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/pointer_set.hpp>

namespace collection
{

//--------------------------------------

/// compare values pointed at rather than the pointers
template <typename T>
static
pointer_to_compare_pointers::result_type
compare_pointed(
    const pointer_to_compare_pointers::first_argument_type  lhs,
    const pointer_to_compare_pointers::second_argument_type rhs )
{
    return (*reinterpret_cast<const T*>(lhs))
         < (*reinterpret_cast<const T*>(rhs));
}

//--------------------------------------

/// set of references to a single type
/**
 *  Uses the common pointer set superclass to
 *  eliminate generated template bodies code
 *  for each unique subclass.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <typename T>
class ref_set
    : public pointer_set
{
public:

    typedef const T *   const_ptr_type;
    typedef const T &   const_ref_type;
    typedef T *         ptr_type;
    typedef T &         ref_type;
    typedef pointer_set superclass;

    class const_iterator
        : public superclass::const_iterator
    {
    public:

        typedef superclass::const_iterator super_iterator;

        BEACH_ALLOCATION_OPERATORS

        const_iterator( const super_iterator & rhs )
          : super_iterator( rhs )
        {}
        const_ptr_type operator->() const
        {
            return static_cast<const_ptr_type>(
                *(super_iterator::operator->()));
        }
        const_ref_type operator*() const
        {
            return *(this->operator->());
        }
    };
    class iterator
        : public superclass::iterator
    {
    public:

        typedef superclass::iterator super_iterator;

        BEACH_ALLOCATION_OPERATORS

        iterator( const super_iterator & rhs )
          : super_iterator( rhs )
        {}
        ptr_type operator->() const
        {
            return const_cast<ptr_type>(
                static_cast<const_ptr_type>(
                    *(super_iterator::operator->())));
        }
        ref_type operator*() const
        {
            return *(this->operator->());
        }
    };

    /// construction of non-owning collection
    ref_set(
        const value_compare & comp
        = pointer_to_compare_pointers(&compare_pointed<T>) )
      : superclass( comp )
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    ref_set(
        const atoms::destroyer_typed<T> & d,
        const value_compare & comp
        = pointer_to_compare_pointers(&compare_pointed<T>) )
      : superclass( d, comp )
    {}

    const_iterator  begin() const   { return superclass::begin(); }
    const_iterator  end()   const   { return superclass::end(); }

    iterator        begin()         { return superclass::begin(); }
    iterator        end()           { return superclass::end(); }

    bool contains(
        const_ref_type ref ) const
    {
        return superclass::contains( &ref );
    }
    const_iterator find_const_iterator(
        const_ref_type ref ) const
    {
        return superclass::find_const_iterator( &ref );
    }
    iterator find_iterator(
        const_ref_type ref )
    {
        return superclass::find_iterator( &ref );
    }
    void add(           ///< synonym
        ref_type ref )
    {
        superclass::insert( &ref );
    }
    void insert(
        ref_type ref )
    {
        superclass::insert( &ref );
    }

}; // end of template class ref_set<>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_SET
