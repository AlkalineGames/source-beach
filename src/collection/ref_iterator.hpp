#if !defined(BEACH_COLLECTION_REF_ITERATOR)
#define      BEACH_COLLECTION_REF_ITERATOR
//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_iterator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace collection
{
    using atoms::boolean;
    using atoms::size_type;

//--------------------------------------

/// interface for polymorphic iterators of references
/**
 *  Instantiators should provide type T without the & reference syntax.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <class T>
class ref_iterator
{
public:

    typedef T & ref;
    typedef T * ptr;
    typedef T   value;

    /// @name standard pattern operations
    //@{
    virtual void    first()     = 0;
    virtual void    next()      = 0;
    virtual boolean is_valid()  const = 0;
    virtual ref     retrieve()  const = 0;
    //@}

    /// @name additional operations
    //@{
    ptr retrieve_ptr() const
    {
        return is_valid() ? &(retrieve()) : 0;
    }
    virtual size_type   get_index() const = 0; ///< may be meaningless

    virtual void        insert( ref )   = 0;
    virtual void        remove()        = 0; ///< no-op if ! is_valid()
    //@}
};

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_ITERATOR
