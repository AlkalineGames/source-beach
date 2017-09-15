#if !defined(BEACH_CHAIN_EXTENSION)
#define      BEACH_CHAIN_EXTENSION
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extension.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/linked.hpp>

namespace chain
{

//--------------------------------------

/// abstract superclass for an extension object
/**
 *  Multiple extensions are chained together in a linked-list.
 *
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
class extension
    : public linked
{
friend class extensions;
public:

    const void *        get_owner_nc()  const { return _owner; }
          void *        get_owner_nc()        { return _owner; }
    const extension *   get_next()      const { return static_cast<const extension*>(linked::get_next()); }
          extension *   get_next_nc()         { return static_cast<extension*>(linked::get_next_nc()); }

protected:

    extension( class_identity, void * in_owner );
    virtual ~extension();

private:

    /// @name copy operations not implemented
    //@{
    extension(              const extension & );
    extension & operator =( const extension & );
    //@}

    void set_next( ///< only by friends
        extension * in_extension )
    {
        linked::set_next( in_extension );
    }

    void * _owner;
    
}; // end of class extension

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_EXTENSION
