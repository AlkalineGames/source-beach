#if !defined(BEACH_COLLECTION_REF_MAP_BY_INTEGER)
#define      BEACH_COLLECTION_REF_MAP_BY_INTEGER
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_map_by_integer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/pointer_map_by_integer.hpp>

namespace collection
{

//--------------------------------------

/// map of references to a single type, keyed by integer
/**
 *  Uses the common pointer list superclass to
 *  eliminate generated template bodies code
 *  for each unique subclass.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <typename T>
class ref_map_by_integer
    : public pointer_map_by_integer
{
public:

    typedef const T *               const_ptr_type;
    typedef const T &               const_ref_type;
    typedef T *                     ptr_type;
    typedef T &                     ref_type;
    typedef pointer_map_by_integer  superclass;

    class const_iterator
        : public superclass::const_iterator
    {
    public:

        typedef superclass::const_iterator super_iterator;

        BEACH_ALLOCATION_OPERATORS

        const_iterator( const super_iterator & rhs )
          : super_iterator( rhs )
        {}
        const key_type & get_key() const
        {
            return super_iterator::operator->()->first;
        }
        const_ptr_type get_ptr() const
        {
            return static_cast<const_ptr_type>(
                (super_iterator::operator->())->second);
        }
        const_ptr_type operator->() const
        {
            return this->get_ptr();
        }
        const_ref_type operator*() const
        {
            return *(this->get_ptr());
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
        const key_type & get_key() const
        {
            return super_iterator::operator->()->first;
        }
        ptr_type get_ptr() const
        {
            return const_cast<ptr_type>(
                static_cast<const_ptr_type>(
                    (super_iterator::operator->())->second));
        }
        ptr_type operator->() const
        {
            return this->get_ptr();
        }
        ref_type operator*() const
        {
            return *(this->get_ptr());
        }
    };

    /// construction of non-owning collection
    ref_map_by_integer()
      : superclass()
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    ref_map_by_integer( const atoms::destroyer_typed<T> & d )
      : superclass( d )
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
    bool erase_first(
        const_ref_type ref )
    {
        return superclass::erase_first( &ref ); 
    }
    const_ptr_type find_ref_const(
        const key_type & key ) const
    {
        const_iterator i( this->find( key ) );
        return ((i != this->end()) ? i.get_ptr() : 0);
    }
    ptr_type find_ref(
        const key_type & key )
    {
        iterator i( this->find( key ) );
        return ((i != this->end()) ? i.get_ptr() : 0);
    }
    void add(           ///< synonym
        key_type key,
        ref_type ref )
    {
        superclass::insert( value_type( key, &ref ) );
    }
    void insert(
        key_type key,
        ref_type ref )
    {
        superclass::insert( value_type( key, &ref ) );
    }
    void replace(
        key_type key,
        ref_type ref )
    {
        superclass::replace( value_type( key, &ref ) );
    }

}; // end of template class ref_map_by_integer<>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_MAP_BY_INTEGER
