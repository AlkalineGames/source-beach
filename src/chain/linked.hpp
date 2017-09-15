#if !defined(BEACH_CHAIN_LINKED)
#define      BEACH_CHAIN_LINKED
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       linked.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>

/// Beach Chain Framework 

namespace chain
{
    using atoms::whole16;

//--------------------------------------

/// abtract superclass for a linked object
/**
 *  Multiple links are chained together in a linked-list.
 */
class linked
{
public:

    BEACH_ALLOCATION_OPERATORS

    typedef whole16 class_identity;

    class_identity  get_class_id()  const   { return _class_id; }
    const linked *  get_next()      const   { return _next; }
          linked *  get_next_nc()           { return _next; }
    const linked &  get_last()      const;
          linked &  get_last_nc()           { return const_cast<linked&>(get_last()); }

    const linked *  find(    class_identity ) const;
          linked *  find_nc( class_identity in_class_id )
    {
        return const_cast<linked*>(find( in_class_id ));
    }
    void            append( linked & in_linked )
    {
        get_last_nc().set_next( &in_linked );
    }

protected:

    linked( class_identity );
    virtual ~linked();

    void set_next( linked * in_next ) { _next = in_next; }

private:

    /// @name copy operations not implemented
    //@{
    linked(              const linked & );
    linked & operator =( const linked & );
    //@}

    class_identity  _class_id;
    linked *        _next;
    
}; // end of class linked

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_LINKED
