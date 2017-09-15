#if !defined(BEACH_COLLECTION_ITERATOR)
#define      BEACH_COLLECTION_ITERATOR
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       iterator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

/// Beach Collection Framework
/**
 *  A framework that provides collections
 *  (also known as containers) which extend
 *  the functionality of the STL containers
 *  --or features not found at all in STL.
 *  Compatability and consistency with STL
 *  are maintained as much as is effective.
 */
namespace collection
{
    using atoms::boolean;

//--------------------------------------

/// interface for polymorphic iterators
/**
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <class T>
class iterator
{
public:

    typedef T item;

    virtual void    first()     = 0;
    virtual void    next()      = 0;
    virtual boolean is_valid()  = 0;
    virtual T       retrieve()  = 0;
};

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_ITERATOR
