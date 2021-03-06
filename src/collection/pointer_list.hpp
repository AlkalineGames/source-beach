#if !defined(BEACH_COLLECTION_POINTER_LIST)
#define      BEACH_COLLECTION_POINTER_LIST
//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       pointer_list.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/destroyer.hpp>
#include <atoms/primitives.hpp>

#include <list>

namespace collection
{

//--------------------------------------

/// list of pointers
/**
 *  This is intended as the superclass for the
 *  ref_list<T> template. This provides substitutability
 *  with the STL container type superclass, type safety
 *  for the reference template subclass, and minimal
 *  template code generation. This class is not virtual!
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
class pointer_list
    : public std::list<atoms::pointer_to_const>
{
public:

    typedef std::list<atoms::pointer_to_const> superclass;

    BEACH_ALLOCATION_OPERATORS

    /// construction of non-owning collection
    pointer_list()
      : superclass(), _destroyer( 0 )
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    pointer_list( const atoms::destroyer_interface & d )
      : superclass(), _destroyer( d.clone() )
    {}
    ~pointer_list()
    {
        if ( _destroyer != 0 )
        {
            iterator endi( this->end() );
            for ( iterator i( this->begin() ); i != endi; i++ )
            {
                value_type ptr = *i;
                _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
            }                
            delete _destroyer;
        }
    }
    bool contains(
        value_type value ) const
    {
        return this->find_const_iterator( value ) != this->end(); 
    }
    const_iterator find_const_iterator(
        value_type value ) const
    {
        const_iterator i( this->begin() );
        for ( const_iterator iend( this->end() );
              i != iend; i++ )
        {
            const value_type ptr = *i;
            if ( ptr == value )
            {
                break;
            }
        }
        return i;
    }
    iterator find_iterator(
        value_type value )
    {
        iterator i( this->begin() );
        for ( iterator iend( this->end() );
              i != iend; i++ )
        {
            const value_type ptr = *i;
            if ( ptr == value )
            {
                break;
            }
        }
        return i;
    }
    iterator erase(
        iterator position )
    {
        if ( _destroyer != 0 )
        {
            if ( position == this->end() )
            {
                return position;
            }
            value_type ptr = *position;
            _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
        }
        return this->superclass::erase( position );
    }
    iterator erase(
        iterator first,
        iterator last )
    {
        if ( _destroyer != 0 )
        {
            for ( iterator i( first );
                  (i != last) && (i != this->end());
                  i++ )
            {
                value_type ptr = *i;
                _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
            }
        }
        return this->superclass::erase( first, last );
    }
    bool erase_at(
        iterator i )
    {
        if ( i == this->end() )
        {
            return false;
        }
        erase( i ); // $$$ repeats the comparison above
        return true;
    }
    bool erase_first(
        value_type value )
    {
        return this->erase_at( this->find_iterator( value ) );
    }
    void clear()
    {
        this->erase( this->begin(), this->end() );
    }

private:

    atoms::destroyer_interface * _destroyer;

}; // end of template class pointer_list<T>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_POINTER_LIST
