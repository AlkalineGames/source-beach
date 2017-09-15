#if !defined(BEACH_LIFECYCLE_REF_ITERATOR_COUNTED)
#define      BEACH_LIFECYCLE_REF_ITERATOR_COUNTED
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

#include <collection/ref_iterator.hpp>
#include <lifecycle/counted_object.hpp>

namespace lifecycle
{

//--------------------------------------

/// abstract superclass for counted reference iterators
/**
 *  Instantiators should provide type T without the & reference syntax.
 *
 *  @note   design patterns applied:
 *				- Counted Body    [PLOP4]
 *              - Counted Pointer [POSA1]
 *              - Iterator        [GoF]
 */
template <class T>
class ref_iterator_counted
    : public counted_object,
      public collection::ref_iterator<T>
{};

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_REF_ITERATOR_COUNTED
