#if !defined(BEACH_COLLECTION_POINTER_MAP_BY_STRING)
#define      BEACH_COLLECTION_POINTER_MAP_BY_STRING
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       pointer_map_by_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/destroyer.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

#include <map>

namespace collection
{

//--------------------------------------

/// map of pointers, keyed by string
/**
 *  This is intended as the superclass for the
 *  ref_map_by_string<T> template. This provides substitutability
 *  with the STL container type superclass, type safety
 *  for the reference template subclass, and minimal
 *  template code generation. This class is not virtual!
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
class pointer_map_by_string
    : public std::map<atoms::stringex,atoms::pointer_to_const>
{
public:

    typedef std::map<atoms::stringex,atoms::pointer_to_const> superclass;

    BEACH_ALLOCATION_OPERATORS

    /// construction of non-owning collection
    pointer_map_by_string()
      : superclass(), _destroyer( 0 )
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    pointer_map_by_string( const atoms::destroyer_interface & d )
      : superclass(), _destroyer( d.clone() )
    {}
    ~pointer_map_by_string()
    {
        if ( _destroyer != 0 )
        {
            for ( iterator i( this->begin() ),
                        iend( this->end() );
                   i != iend; i++ )
            {
                key_type k = i->first;
                mapped_type p = i->second;
                //_destroyer->destroy( k );
                _destroyer->destroy( 
                    const_cast<atoms::pointer>(
                        reinterpret_cast<const void*>(p)) );
            }                
            delete _destroyer;
        }
    }
    bool contains(
        mapped_type ptr ) const
    {
        return this->find_const_iterator( ptr ) != this->end(); 
    }
    bool contains_key(
        const key_type & key ) const
    {
        return this->find( key ) != this->end();
    }
    const_iterator find_const_iterator(
        mapped_type ptr ) const
    {
        const_iterator i( this->begin() );
        for ( const_iterator iend( this->end() );
              i != iend; i++ )
        {
            const mapped_type p = i->second;
            if ( p == ptr )
            {
                break;
            }
        }
        return i;
    }
    iterator find_iterator(
        mapped_type ptr )
    {
        iterator i( this->begin() );
        for ( iterator iend( this->end() );
              i != iend; i++ )
        {
            const mapped_type p = i->second;
            if ( p == ptr )
            {
                break;
            }
        }
        return i;
    }
    bool erase(
        iterator i )
    {
        if ( i == this->end() )
        {
            return false;
        }
        if ( _destroyer != 0 )
        {
            mapped_type ptr = i->second;
            _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
        }
        this->superclass::erase( i );
        return true;
    }
    void erase(
        iterator first,
        iterator last )
    {
        iterator i    = first;
        iterator iend = this->end();
        while ( i != iend )
        {
            iterator current = i;
            ++i; // !!! ASSUMED SAFE BASED ON C++ STANDARD [cat]
            this->erase( current );
            if ( i == last )
            {
                break;
            }
        }
    }
    bool erase(
        const key_type & key )
    {
        return this->erase( this->find( key ) );
    }
    bool erase_first(
        mapped_type ptr )
    {
        return this->erase( this->find_iterator( ptr ) );
    }
    void clear()
    {
        this->erase( this->begin(), this->end() );
    }
    void replace(
        value_type value )
    {
        iterator iter = find( value.first );
        if ( iter != end() )
        {
            if ( iter->second == value.second )
            {
                return;
            }
            erase( iter ); 
        }
        insert( value );
    }

private:

    atoms::destroyer_interface * _destroyer;

}; // end of template class pointer_map_by_string<T>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_POINTER_MAP_BY_STRING
