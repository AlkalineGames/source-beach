#if !defined(BEACH_CHAIN_EXTENSIONS_TYPED)
#define      BEACH_CHAIN_EXTENSIONS_TYPED
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extensions_typed.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/extensions.hpp>

namespace chain
{

//--------------------------------------

/// template for a chain of extension objects
/**
 *  Multiple extensions are connected in a linked-list.
 *
 *  E must be a extension<T> or descendent.
 *  Make this a member of the owner object class.
 *
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */      
template <class T, class E>
class extensions_typed
    : public extensions
{
public:

    extensions_typed( T & in_owner )
      :
        extensions( &in_owner )
    {}
    const T &   get_owner_nc() const
    {
        return *(static_cast<const T*>(extensions::get_owner_nc()));
    }
          T &   get_owner_nc()
    {
        return *(static_cast<T*>(extensions::get_owner_nc()));
    }
    const E *   get_first() const
    {
        return static_cast<const E*>(extensions::get_first());
    }
          E *   get_first_nc()
    {
        return static_cast<E*>(extensions::get_first_nc());
    }
    const E *   get_last() const
    {
        return static_cast<const E*>(extensions::get_last());
    }
          E *   get_last_nc()
    {
        return static_cast<E*>(extensions::get_last_nc());
    }
    const E *   find( extension::class_identity in_class_id ) const
    {
        return static_cast<const E*>(extensions::find( in_class_id ));
    }
          E *   find_nc( extension::class_identity in_class_id )
    {
        return static_cast<E*>(extensions::find_nc( in_class_id ));
    }
    void        add( E & in_extension ) ///< adds whether or same extension type exists
    {
        extensions::add( in_extension );
    }

}; // end of template class extensions

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_EXTENSIONS_TYPED
