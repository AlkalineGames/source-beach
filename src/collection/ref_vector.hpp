#if !defined(BEACH_COLLECTION_REF_VECTOR)
#define      BEACH_COLLECTION_REF_VECTOR
//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_vector.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/pointer_vector.hpp>

namespace collection
{

//--------------------------------------

/// vector of references to a single type
/**
 *  Uses the common pointer vector superclass to
 *  eliminate generated template bodies code
 *  for each unique subclass.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <typename T>
class ref_vector
    : public pointer_vector
{
public:

    typedef const T *       const_ptr_type;
    typedef const T &       const_ref_type;
    typedef T *             ptr_type;
    typedef T &             ref_type;
    typedef pointer_vector  superclass;

#if 0 // !!! CANNOT USE SUBCLASS VERSIONS BECAUSE OF STLPORT
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
            return static_cast<ptr_type>(
                *(super_iterator::operator->()));
        }
        ref_type operator*() const
        {
            return *(this->operator->());
        }
    };
#endif
    class const_iterator
    {
    public:

        typedef superclass::const_iterator super_iterator;

        BEACH_ALLOCATION_OPERATORS

        const_iterator( const super_iterator & rhs )
          : _super_iterator( rhs )
        {}
        operator super_iterator()               { return _super_iterator; }
              super_iterator & super_nc()       { return _super_iterator; }
        const super_iterator & super()    const { return _super_iterator; }
        
        bool operator ==( const const_iterator & rhs ) const
        {
            return _super_iterator == rhs._super_iterator;
        }
        bool operator !=( const const_iterator & rhs ) const
        {
            return _super_iterator != rhs._super_iterator;
        }
        const_ptr_type operator->() const
        {
            return static_cast<const_ptr_type>(
                *_super_iterator);
        }
        const_ref_type operator*() const
        { 
            return *(this->operator->());
        }
        const_iterator & operator++()
        {
            ++_super_iterator;
            return *this;
        }
        const_iterator operator++( int )
        {
            const_iterator pre( *this );
            _super_iterator++;
            return pre;
        }
        const_iterator operator+=( size_type n )
        {
            _super_iterator += n;
            return *this;
        }
        const_iterator & operator--()
        {
            --_super_iterator;
            return *this;
        }
        const_iterator operator--( int )
        {
            const_iterator pre( *this );
            _super_iterator--;
            return pre;
        }
        const_iterator operator-=( size_type n )
        {
            _super_iterator -= n;
            return *this;
        }
    private:
        super_iterator _super_iterator;
    };
    class iterator
    {
    public:

        typedef superclass::iterator super_iterator;

        BEACH_ALLOCATION_OPERATORS

        iterator( const super_iterator & rhs )
          : _super_iterator( rhs )
        {}
        operator super_iterator()               { return _super_iterator; }
              super_iterator & super_nc()       { return _super_iterator; }
        const super_iterator & super()    const { return _super_iterator; }
        
        bool operator ==( const iterator & rhs ) const
        {
            return _super_iterator == rhs._super_iterator;
        }
        bool operator !=( const iterator & rhs ) const
        {
            return _super_iterator != rhs._super_iterator;
        }
        ptr_type operator->() const
        {
            return const_cast<ptr_type>(
                static_cast<const_ptr_type>(
                    *_super_iterator));
        }
        ref_type operator*() const
        {
            return *(this->operator->());
        }
        iterator & operator++()
        {
            ++_super_iterator;
            return *this;
        }
        iterator operator++( int )
        {
            iterator pre( *this );
            _super_iterator++;
            return pre;
        }
        iterator operator+=( size_type n )
        {
            _super_iterator += n;
            return *this;
        }
        iterator & operator--()
        {
            --_super_iterator;
            return *this;
        }
        iterator operator--( int )
        {
            iterator pre( *this );
            _super_iterator--;
            return pre;
        }
        iterator operator-=( size_type n )
        {
            _super_iterator -= n;
            return *this;
        }
    private:
        super_iterator _super_iterator;
    };
    class const_reverse_iterator
        : public superclass::const_reverse_iterator
    {
    public:

        typedef superclass::const_reverse_iterator super_reverse_iterator;

        BEACH_ALLOCATION_OPERATORS

        const_reverse_iterator( const super_reverse_iterator & rhs )
          : super_reverse_iterator( rhs )
        {}
        const_ptr_type operator->() const
        {
            return static_cast<const_ptr_type>(
                *(super_reverse_iterator::operator->()));
        }
        const_ref_type operator*() const
        {
            return *(this->operator->());
        }
    private:
        super_reverse_iterator _super_reverse_iterator;
    };
    class reverse_iterator
        : public superclass::reverse_iterator
    {
    public:

        typedef superclass::reverse_iterator super_reverse_iterator;

        BEACH_ALLOCATION_OPERATORS

        reverse_iterator( const super_reverse_iterator & rhs )
          : super_reverse_iterator( rhs )
        {}
        ptr_type operator->() const
        {
            return const_cast<ptr_type>(
                static_cast<const_ptr_type>(
                    *(super_reverse_iterator::operator->())));
        }
        ref_type operator*() const
        {
            return *(this->operator->());
        }
    private:
        super_reverse_iterator _super_reverse_iterator;
    };
    class wrapped_iterator
    {
    public:

        BEACH_ALLOCATION_OPERATORS

        wrapped_iterator( ref_vector & in_collection )
          :
            _collection( in_collection ),
            _iterator(   in_collection.begin() )
        {}
        wrapped_iterator( const wrapped_iterator & rhs )
          :
            _collection( rhs._collection ),
            _iterator(   rhs._iterator )
        {}
        bool operator ==( const wrapped_iterator & rhs ) const
        {
            return _iterator == rhs._iterator;
        }
        bool operator !=( const wrapped_iterator & rhs ) const
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
        wrapped_iterator & operator++()
        {
            ++_iterator;
            return *this;
        }
        wrapped_iterator operator++( int )
        {
            iterator pre( *this );
            _iterator++;
            return pre;
        }
        wrapped_iterator operator+=( size_type n )
        {
            _iterator += n;
            return *this;
        }
        wrapped_iterator & operator--()
        {
            --_iterator;
            return *this;
        }
        wrapped_iterator operator--( int )
        {
            iterator pre( *this );
            _iterator--;
            return pre;
        }
        wrapped_iterator operator-=( size_type n )
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
        ref_type operator[]( size_type i ) const
        {
            return _collection[i];
        }
        void add( ref_type ref ) ///< iterator position at added element
        {
            /// !!! collection::add(...) can invalidate the iterator
            _iterator = _collection.insert(
                _collection.end(), ref );
        }
        size_type index() const
        {
            return _iterator.super() - _collection.begin().super();
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
                _iterator += (siz - 1);
        }
        void locate( ref_type ref )
        {
            _iterator = _collection.find_iterator( ref );
        }
        void prev()
        {
            if ( ! is_begin() )
                --_iterator;
            else // make ! is_valid()
                _iterator = _collection.end();
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
        ref_vector &    _collection; 
        iterator        _iterator; 
    };
    class wrapped_iterator_const
    {
    public:

        BEACH_ALLOCATION_OPERATORS

        wrapped_iterator_const( const ref_vector & in_collection )
          :
            _collection( in_collection ),
            _iterator(   in_collection.begin() )
        {}
        wrapped_iterator_const( const wrapped_iterator_const & rhs )
          :
            _collection( rhs._collection ),
            _iterator(   rhs._iterator )
        {}
        bool operator ==( const wrapped_iterator_const & rhs ) const
        {
            return _iterator == rhs._iterator;
        }
        bool operator !=( const wrapped_iterator_const & rhs ) const
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
        wrapped_iterator_const & operator++()
        {
            ++_iterator;
            return *this;
        }
        wrapped_iterator_const operator++( int )
        {
            iterator pre( *this );
            _iterator++;
            return pre;
        }
        wrapped_iterator_const operator+=( size_type n )
        {
            _iterator += n;
            return *this;
        }
        wrapped_iterator_const & operator--()
        {
            --_iterator;
            return *this;
        }
        wrapped_iterator_const operator--( int )
        {
            iterator pre( *this );
            _iterator--;
            return pre;
        }
        wrapped_iterator_const operator-=( size_type n )
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
        const_ref_type operator[]( size_type i ) const
        {
            return _collection[i];
        }
        size_type index() const
        {
            return _iterator.super() - _collection.begin().super();
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
                _iterator += (siz - 1);
        }
        void locate( ref_type ref )
        {
            _iterator = _collection.find_const_iterator( ref );
        }
        void prev()
        {
            if ( ! is_begin() )
                --_iterator;
            else // make ! is_valid()
                _iterator = _collection.end();
        }
        size_type size() const { return _collection.size(); }
        //@}
    private:
        const ref_vector &  _collection; 
        const_iterator      _iterator; 
    };

    /// construction of non-owning collection
    ref_vector()
      : superclass()
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    ref_vector( const atoms::destroyer_typed<T> & d )
      : superclass( d )
    {}

    const_iterator          begin() const   { return superclass::begin(); }
    const_iterator          end()   const   { return superclass::end(); }
    
    iterator                begin()         { return superclass::begin(); }
    iterator                end()           { return superclass::end(); }

    const_reverse_iterator  rbegin() const  { return superclass::rbegin(); }
    const_reverse_iterator  rend()   const  { return superclass::rend(); }

    reverse_iterator        rbegin()        { return superclass::rbegin(); }
    reverse_iterator        rend()          { return superclass::rend(); }

    ref_type operator[]( size_type i )
    {
        return *const_cast<ptr_type>(
            static_cast<const_ptr_type>(
                superclass::operator[]( i )));
    }
    const_ref_type operator[]( size_type i ) const
    {
        return *static_cast<const_ptr_type>(
            superclass::operator[]( i ));
    }
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
    ptr_type find_at(
        int index )
    {
        return const_cast<ptr_type>(
            static_cast<const_ptr_type>(
                find_at( index )));
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
            this->add( ref );
    }
    iterator insert(
        ref_type ref )
    {
        return superclass::insert( begin(), &ref );
    }
    iterator insert(
            const_iterator position,
            ref_type ref) {
        return superclass::insert(position, &ref);
    }
    iterator insert(
            iterator position,
            ref_type ref) {
        // !!! need to convert iterator for fucking C++11
        superclass::const_iterator constpos = superclass::begin();
        constpos += position.super() - superclass::begin();
        return superclass::insert(constpos, &ref);
    }
    iterator insert_at(
        int index,
        ref_type ref )
    {
        return superclass::insert_at( index, &ref );
    }
    bool replace_at(
        int index,
        ref_type ref )
    {
        return superclass::replace_at( index, &ref );
    }

}; // end of template class ref_vector<>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_VECTOR
