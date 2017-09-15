#if !defined(BEACH_CHAIN_ASSOCIATIONS_TYPED)
#define      BEACH_CHAIN_ASSOCIATIONS_TYPED
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       associations_typed.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/association_typed.hpp>
#include <chain/associations.hpp>

namespace chain
{

//--------------------------------------

/// template for a chain of associations between objects

template <class M, class Q> // specify class arg without the &
class associations_typed
    : public associations
{
public:

    typedef association_typed<M,Q>  association_type;
    typedef M                       member_type;
    typedef Q                       qualifier_type;

    associations_typed( ///< side must be LeftSide or RightSide if first link is non-zero
        association::side   in_side_dominant_first  = association::side_neither,
        association *       in_link_first           = 0 )
      : 
        associations(       in_side_dominant_first,
                            in_link_first )
    {}
    const association_type *    get_link_first() const
    {
        return static_cast<const association_type*>(associations::get_link_first());
    }
          association_type *    get_link_first_nc()
    {
        return static_cast<association_type*>(associations::get_link_first());
    }
    const member_type *         get_member_dominant() const 
    {
        return static_cast<const member_type*>(associations::get_member_dominant());
    }
          member_type *         get_member_dominant_nc() 
    {
        return static_cast<member_type*>(associations::get_member_dominant());
    }
    const association_type *    find_link_matching(
        association::side           in_side_matching, ///< side of dominant member
        const member_type &         in_member_other ) const 
    {
        if ( get_link_first() == 0 )
        {
            return 0;
        }
        const member_type * memdom = get_member_dominant();
        if ( memdom == 0 )
        {
            return 0;
        }
        return get_link_first()->find_link_matching( 
            *memdom, in_side_matching, in_member_other );
    }
    association_type *          find_link_matching_nc(
        association::side           in_side_matching,
        const member_type &         in_member_other )
    {
        return const_cast<association_type*>(
            const_cast<const associations_typed*>(this)->find_link_matching(
                in_side_matching, in_member_other ));
    }
    const association_type *    find_link_matching_qualifier(
        association::side           in_side_matching,
        qualifier_type              in_qualifier,
        const member_type *         in_member_other = 0 ) const ///< zero matches any other member
    {
        if ( get_link_first() == 0 )
        {
            return 0;
        }
        const member_type * memdom = get_member_dominant();
        if ( memdom == 0 )
        {
            return 0;
        }
        return get_link_first()->find_link_matching_qualifier( 
            *memdom, in_side_matching, in_qualifier, in_member_other );
    }
    association_type *          find_link_matching_qualifier_nc(
        association::side           in_side_matching,
        qualifier_type              in_qualifier,
        const member_type *         in_member_other = 0 ) ///< zero matches any other member
    {
        return const_cast<association_type*>(
            const_cast<const associations_typed*>(this)->find_link_matching_qualifier(
                in_side_matching, in_qualifier, in_member_other ));
    }

}; // end of template class associations_typed

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_ASSOCIATIONS_TYPED
