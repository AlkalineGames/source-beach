#if !defined(BEACH_COLLECTION_POINTER_SET)
#define      BEACH_COLLECTION_POINTER_SET
//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       pointer_set.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/destroyer.hpp>
#include <atoms/primitives.hpp>

#include <set>

namespace collection
{

//--------------------------------------

/// indirection to support comparing other than the pointer values 
typedef std::pointer_to_binary_function<atoms::pointer_to_const,atoms::pointer_to_const,bool>
    pointer_to_compare;

/// based on std::pointer_to_binary_function which used to work (above)
/// but not anymore because it not longer provides a default constructor
class pointer_to_compare_pointers
    : public std::binary_function<atoms::pointer_to_const,atoms::pointer_to_const,bool>
{
protected:
    result_type (*pfunc)(first_argument_type,second_argument_type);
public:
    explicit pointer_to_compare_pointers(
        result_type (*f)(first_argument_type,second_argument_type) = nullptr)
      : pfunc(f)
    {}
    result_type operator() (first_argument_type x, second_argument_type y) const {
        return pfunc ? pfunc(x,y) : x < y; // !!! equivalent to default for set: less
    }
};

//--------------------------------------

/// set of pointers
/**
 *  This is intended as the superclass for the
 *  ref_set<T> template. This provides substitutability
 *  with the STL container type superclass, type safety
 *  for the reference template subclass, and minimal
 *  template code generation. This class is not virtual!
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
class pointer_set
    : public std::set<atoms::pointer_to_const,pointer_to_compare_pointers>
{
public:

    typedef std::set<atoms::pointer_to_const,pointer_to_compare_pointers> superclass;

    BEACH_ALLOCATION_OPERATORS

    /// construction of non-owning collection
    pointer_set(
        const value_compare & comp /* = value_compare() @@@ NO LONGER WORKS */)
      : superclass(comp), _destroyer(0)
    {}
    /// construction of owning collection
    /** client must provide destroyer object for the element type */
    pointer_set(
        const atoms::destroyer_interface & d,
        const value_compare & comp /* = value_compare() @@@ NO LONGER WORKS */)
      : superclass(comp), _destroyer(d.clone())
    {}
    ~pointer_set() {
        if ( _destroyer != 0 ) {
            iterator endi( this->end() );
            for ( iterator i( this->begin() ); i != endi; i++ ) {
                value_type ptr = *i;
                _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
            }                
            delete _destroyer;
        }
    }
    bool contains(
            value_type value) const {
        return this->find_const_iterator(value) != this->end(); 
    }
    const_iterator find_const_iterator(
            value_type value) const {
        const_iterator i(this->begin());
        for ( const_iterator iend(this->end()); i != iend; i++) {
            const value_type ptr = *i;
            if (ptr == value) {
                break;
            }
        }
        return i;
    }
    iterator find_iterator(
        value_type value)
    {
        iterator i(this->begin());
        for ( iterator iend(this->end()); i != iend; i++) {
            const value_type ptr = *i;
            if (ptr == value) {
                break;
            }
        }
        return i;
    }
    iterator erase(
        iterator position)
    {
        if (_destroyer != 0) {
            if (position == this->end()) {
                return position;
            }
            value_type ptr = *position;
            _destroyer->destroy(const_cast<atoms::pointer>(ptr));
        }
        this->superclass::erase(position);
    }
    iterator erase(
        iterator first,
        iterator last)
    {
        if (_destroyer != 0) {
            for (iterator i(first); (i != last) && (i != this->end()); i++) {
                value_type ptr = *i;
                _destroyer->destroy( const_cast<atoms::pointer>(ptr) );
            }
        }
        this->superclass::erase(first, last);
    }
    void clear() {
        this->erase(this->begin(), this->end());
    }

private:

    atoms::destroyer_interface * _destroyer;

}; // end of template class pointer_set<T>

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_POINTER_SET
