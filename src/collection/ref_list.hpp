#if !defined(BEACH_COLLECTION_REF_LIST)
#define      BEACH_COLLECTION_REF_LIST
//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_list.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/pointer_list.hpp>

namespace collection
{

//--------------------------------------

/// list of references to a single type
/**
 *  Uses the common pointer list superclass to
 *  eliminate generated template bodies code
 *  for each unique subclass.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <typename T>
class ref_list
    : public pointer_list
{
public:

    typedef const T *       const_ptr_type;
    typedef const T &       const_ref_type;
    typedef T *             ptr_type;
    typedef T &             ref_type;
    typedef pointer_list    superclass;

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
    class iterator_wrapped
    {
    public:

        BEACH_ALLOCATION_OPERATORS

        iterator_wrapped( ref_list & in_collection )
          :
            _collection( in_collection ),
            _iterator(   in_collection.begin() )
        {}
        iterator_wrapped( const iterator_wrapped & rhs )
          :
            _collection( rhs._collection ),
            _iterator(   rhs._iterator )
        {}
        bool operator ==( const iterator_wrapped & rhs ) const
        {
            return _iterator == rhs._iterator;
        }
        bool operator !=( const iterator_wrapped & rhs ) const
        {
            return _iterator != rhs._iterator;
        }
        ptr_type operator->() const
        {
            return &(*_iterator);
        }
        ref_type operator*() const
        {
            return *_iterator;
        }
        iterator_wrapped & operator++()
        {
            ++_iterator;
            return *this;
        }
        iterator_wrapped operator++( int )
        {
            iterator pre( *this );
            _iterator++;
            return pre;
        }
        iterator_wrapped operator+=( size_type n )
        {
            _iterator += n;
            return *this;
        }
        iterator_wrapped & operator--()
        {
            --_iterator;
            return *this;
        }
        iterator_wrapped operator--( int )
        {
            iterator pre( *this );
            _iterator--;
            return pre;
        }
        iterator_wrapped operator-=( size_type n )
        {
            _iterator -= n;
            return *this;
        }
        /// @name GoF Iterator operations
        //@{
        void first()
        {
            _iterator = _collection.begin();
        }
        void next()
        {
            ++_iterator;
        }
        bool is_valid() const
        {
            return (_iterator != _collection.end());
        }
        ref_type retrieve() const
        {
            return *_iterator;
        }
        //@}
        /// @name non-standard enhancements
        //@{
        void add( ref_type ref ) ///< iterator position at added element
        {
            /// !!! collection::add(...) can invalidate the iterator
            _iterator = _collection.insert( _collection.end(), ref );
        }
        void insert( ref_type ref )
        {
            _iterator = _collection.insert( _iterator, ref );
        }
        bool is_begin() const
        {
            return (_iterator == _collection.begin());
        }
        void last()
        {
            _iterator = _collection.begin();
            size_type siz = size();
            if ( siz > 1 )
            {   
                _iterator += (siz - 1);
            }
        }
        void locate( ref_type ref )
        {
            _iterator = _collection.find_iterator( ref );
        }
        void prev()
        {
            if ( ! is_begin() )
            {
                --_iterator;
            }
            else // make ! is_valid()
            {
                _iterator = _collection.end();
            }
        }
        void remove()
        {
            _iterator = _collection.erase( _iterator );
        }
        size_type size() const
        {
            return _collection.size();
        }
        //@}
    private:
        ref_list &  _collection; 
        iterator    _iterator; 
    };
    class iterator_wrapped_const
    {
    public:

        BEACH_ALLOCATION_OPERATORS

        iterator_wrapped_const( const ref_list & in_collection )
          :
            _collection( in_collection ),
            _iterator(   in_collection.begin() )
        {}
        iterator_wrapped_const( const iterator_wrapped_const & rhs )
          :
            _collection( rhs._collection ),
            _iterator(   rhs._iterator )
        {}
        bool operator ==( const iterator_wrapped_const & rhs ) const
        {
            return _iterator == rhs._iterator;
        }
        bool operator !=( const iterator_wrapped_const & rhs ) const
        {
            return _iterator != rhs._iterator;
        }
        const_ptr_type operator->() const
        {
            return &(*_iterator);
        }
        const_ref_type operator*() const
        {
            return *_iterator;
        }
        iterator_wrapped_const & operator++()
        {
            ++_iterator;
            return *this;
        }
        iterator_wrapped_const operator++( int )
        {
            iterator pre( *this );
            _iterator++;
            return pre;
        }
        iterator_wrapped_const operator+=( size_type n )
        {
            _iterator += n;
            return *this;
        }
        iterator_wrapped_const & operator--()
        {
            --_iterator;
            return *this;
        }
        iterator_wrapped_const operator--( int )
        {
            iterator pre( *this );
            _iterator--;
            return pre;
        }
        iterator_wrapped_const operator-=( size_type n )
        {
            _iterator -= n;
            return *this;
        }
        /// @name GoF Iterator operations
        //@{
        void first()
        {
            _iterator = _collection.begin();
        }
        void next()
        {
            ++_iterator;
        }
        bool is_valid() const
        {
            return (_iterator != _collection.end());
        }
        const_ref_type retrieve() const
        {
            return *_iterator;
        }
        //@}
        /// @name non-standard enhancements
        //@{
        bool is_begin() const
        {
            return (_iterator == _collection.begin());
        }
        void last()
        {
            _iterator = _collection.begin();
            size_type siz = size();
            if ( siz > 1 )
            {   
                _iterator += (siz - 1);
            }
        }
        void locate( ref_type ref )
        {
            _iterator = _collection.find_const_iterator( ref );
        }
        void prev()
        {
            if ( ! is_begin() )
            {
                --_iterator;
            }
            else // make ! is_valid()
            {
                _iterator = _collection.end();
            }
        }
        size_type size() const
        {
            return _collection.size();
        }
        //@}
    private:
        const ref_list &    _collection; 
        const_iterator      _iterator; 
    };

    /// construction of non-owning collection
    ref_list()
      : superclass()
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    ref_list( const atoms::destroyer_typed<T> & d )
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
    void push_back(
        ref_type ref )
    {
        superclass::push_back( &ref );
    }
    void add(           ///< synonym
        ref_type ref )
    {
        superclass::push_back( &ref );
    }
    void add_uniquely(
        ref_type ref )
    {
        if ( ! this->contains( ref ) )
        {
            this->add( ref );
        }
    }
    iterator insert(
        ref_type ref )
    {
        return superclass::insert( begin(), &ref );
    }
    iterator insert(
        const iterator &    it,
        ref_type            ref )
    {
        return superclass::insert( it, &ref );
    }

}; // end of template class ref_list<>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_LIST
