#if !defined(BEACH_CHAIN_ASSOCIATIONS)
#define      BEACH_CHAIN_ASSOCIATIONS
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       associations.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/association.hpp>

namespace chain
{

//--------------------------------------

/// abstract superclass for a chain of associations between objects

class associations
{
public:

    associations( ///< side must be side_left or side_right if first link is non-zero
        association::side       in_side_dominant_first  = association::side_neither,
        association *           in_link_first           = 0 )
      :
        _side_dominant_first(   in_side_dominant_first ),
        _link_first(            in_link_first )
    {}

    association::side       get_side_dominant_first()   const { return _side_dominant_first; }
    const association *     get_link_first()            const { return _link_first; }
          association *     get_link_first()                  { return _link_first; }
    pointer_to_const        get_member_dominant()       const 
    {
        return ((_link_first == 0) ? 0 : _link_first->get_member( _side_dominant_first ));
    }
    pointer                 get_member_dominant() 
    {
        return ((_link_first == 0) ? 0 : _link_first->get_member_nc( _side_dominant_first ));
    }
    const association *     find_link(
        association::side       in_side_matching, ///< side_either is allowed
        pointer_to_const        in_member_other ) const;

    association *           find_link_nc(
        association::side       in_side_matching, ///< side_either is allowed
        pointer                 in_member_other )
    {
        return const_cast<association*>(
            const_cast<const associations*>(this)
                ->find_link( in_side_matching, in_member_other ));
    }
    void                    insert_link(
        association::side       in_side_dominant,
        association &           in_link,
        associations &          in_chain_other );

    void                    remove_link(
        association &           in_link,
        associations &          in_chain_other );

private:

    void                    perform_insert(
        association::side       in_side_dominant,
        association &           in_link );

    void                    perform_remove(
        association &           in_link );

    association::side   _side_dominant_first;
    association *       _link_first;

}; // end of class associations

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_ASSOCIATIONS
