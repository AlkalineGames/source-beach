#if !defined(BEACH_CHAIN_EXTENSIONS)
#define      BEACH_CHAIN_EXTENSIONS
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extensions.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <chain/extension.hpp>

namespace chain
{

//--------------------------------------

/// abstract superclass for a chain of extension objects
/**
 *  Multiple extensions are connected in a linked-list.
 *
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
class extensions
{
public:

    BEACH_ALLOCATION_OPERATORS

    const void *        get_owner_nc()  const { return _owner; }
          void *        get_owner_nc()        { return _owner; }
    const extension *   get_first()     const { return _first; }
          extension *   get_first_nc()        { return _first; }
    const extension *   get_last()      const;
          extension *   get_last_nc()
    {
        return const_cast<extension*>(get_last());
    }
    const extension *   find(    extension::class_identity in_class_id ) const;
          extension *   find_nc( extension::class_identity in_class_id )
    {
        return const_cast<extension*>(find( in_class_id ));
    }
    void                destroy( extension & );
    void                destroy( extension::class_identity );

protected:

    extensions( void * in_owner )
      :
        _owner( in_owner ),
        _first( 0 )
    {}
    ~extensions(); ///< destroys from first to last

    void add( extension & ); ///< subclass must provide a public add(...)

private:

    /// @name copy operations not supported
    //@{
    extensions(              const extensions & );
    extensions & operator =( const extensions & );
    //@}

    void *      _owner;
    extension * _first;
    
}; // end of class extensions

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_EXTENSIONS
