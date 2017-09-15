#if !defined(BEACH_CHAIN_EXTENSION_TYPED)
#define      BEACH_CHAIN_EXTENSION_TYPED
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extension_typed.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/extension.hpp>

namespace chain
{

//--------------------------------------

/// template for an extension object
/**
 *  Multiple extensions are chained together in a linked-list.
 *
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
template <class T> ///< T must be the owner class
class extension_typed
    : public extension
{
public:

    typedef T owner;

    const owner &               get_owner() const
    {
        return * static_cast<const owner*>(extension::get_owner_nc());
    }
          owner &               get_owner_nc() 
    {
        return * static_cast<owner*>(extension::get_owner_nc());
    }
    const extension_typed<T> *  get_next() const
    {
        return static_cast<const extension_typed<T>*>(extension::get_next());
    }
          extension_typed<T> *  get_next_nc()
    {
        return static_cast<extension_typed<T>*>(extension::get_next_nc());
    }

protected:

    extension_typed( class_identity, T & in_owner );
    
}; // end of template class extension_typed

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_EXTENSION_TYPED
