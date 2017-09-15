#if !defined(BEACH_COLLECTION_REF_ITERATOR_COUNTED_IMP)
#define      BEACH_COLLECTION_REF_ITERATOR_COUNTED_IMP
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_iterator_counted.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/ref_iterator_counted.hpp>

namespace lifecycle
{
    using atoms::boolean;
    using atoms::size_type;

//--------------------------------------

/// implementation of a polymorphic iterator of references
/**
 *  Instantiators should provide type T without the & reference syntax.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
template <class T, class C, class I>
class ref_iterator_counted_imp
    : public ref_iterator_counted<T>
{
public:

    typedef C collection;
    typedef I collection_iterator;
    typedef T & ref; ///< @@@ should inherit from superclass

    ref_iterator_counted_imp( collection & );
    virtual ~ref_iterator_counted_imp();

    /// @name standard pattern operations
    //@{
    virtual void        first();
    virtual void        next();
    virtual boolean     is_valid() const;
    virtual ref         retrieve() const;
    //@}

    /// @name additional operations
    //@{
    virtual size_type   get_index() const; ///< may be meaningless
    virtual void        insert( ref );
    virtual void        remove(); ///< no-op if ! is_valid()
    //@}

private:

    collection &        _collection;
    collection_iterator _collection_iterator;
};

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_ITERATOR_COUNTED_IMP
