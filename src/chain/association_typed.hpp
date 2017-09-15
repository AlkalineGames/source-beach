#if !defined(BEACH_CHAIN_ASSOCIATION_TYPED)
#define      BEACH_CHAIN_ASSOCIATION_TYPED
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       association_typed.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/association.hpp>

namespace chain
{

//--------------------------------------

/// template for an association between two objects, linked to other associations
/**
 *  Linking association_typed objects yield unbounded virtual n-ary networks
 *  without the need to manage separate collection objects, as well as
 *  optimal traversal across all associations for any given object. 
 */
template <class M, class Q> ///< specify class arg without the &
class association_typed
    : public association
{
public:

    typedef M member_type;
    typedef Q qualifier_type;
    
    association_typed() {}
    association_typed(
        member_type &       in_member_left,
        member_type &       in_member_right,
        qualifier_type      in_qualifier )
      : 
        association_typed(  &in_member_left,
                           &in_member_right ),
        _qualifier(         in_qualifier )
    {}

    qualifier_type              get_qualifier() const { return _qualifier; }

    const member_type &         get_member_left() const
    {
        return (* static_cast<const member_type*>(
                    association::get_member_left()));
    }
          member_type &         get_member_left_nc() 
    {
        return const_cast<member_type&>(get_member_left());
    }
    const member_type &         get_member_right() const
    {
        return (* static_cast<const member_type*>(
                    association::get_member_right()));
    }
          member_type &         get_member_right_nc() 
    {
        return const_cast<member_type&>(get_member_right());
    }
	const member_type &         get_member( side in_side ) const
    {
        return (* static_cast<const member_type*>(
                    association::get_member( in_side )));
    }
	      member_type &         get_member_nc( side in_side )
    {
        return const_cast<member_type&>(get_member( in_side ));
    }
	side                        get_side( const member_type & in_member ) const
    {
        return association::get_side( &in_member );
    }
    const association_typed *   get_link_next_left() const
    {
        return static_cast<const association_typed*>(
                    association::get_link_next_left());
    }
          association_typed *   get_link_next_left_nc()
    {
        return static_cast<association_typed*>(
                    association::get_link_next_left_nc());
    }
    const association_typed *   get_link_next_right() const
    {
        return static_cast<const association_typed*>(
                    association::get_link_next_right());
    }
          association_typed *   get_link_next_right_nc()
    {
        return static_cast<association_typed*>(
                    association::get_link_next_right_nc());
    }
	const member_type *         find_peer_of( const member_type & in_member ) const
    {
        return static_cast<const member_type*>(association::find_peer_of( &in_member ));
    }
	      member_type *         find_peer_nc_of( const member_type & in_member )
    {
        return const_cast<member_type*>(find_peer_nc_of( &in_member ));
    }
    const association_typed *   find_link_next(
        const member_type &         in_member ) const
    {
        return static_cast<const association_typed*>(
                    association::find_link_next( &in_member ));
    }
          association_typed *   find_link_next_nc(
              member_type &         in_member )
    {
        return static_cast<association_typed*>(
                    association::find_link_next_nc( &in_member ));
    }        
    const association_typed *   find_link_matching(
        const member_type &         in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        const member_type &         in_member_other ) const
    {
        return static_cast<const association_typed*>(
                    association::find_link_matching(
                        &in_member_dominant, in_side_matching, &in_member_other ));
    }
          association_typed *   find_link_matching_nc(
        const member_type &         in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        const member_type &         in_member_other )
    {
        return const_cast<association_typed*>(
            const_cast<const association_typed*>(this)->find_link_matching(
                in_member_dominant, in_side_matching, in_member_other ));
    }
    const association_typed *   find_link_matching_qualifier(
        const member_type &         in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        qualifier_type              in_qualifier,       ///< match only with this qualifier
        const member_type *         in_member_other = 0 ) const ///< zero matches any other member_type
    {
        const association_typed * link = this;
        do
        {
            if ( &in_member_dominant == &(link->get_member_left()) )
            {
                if (   ((in_side_matching & side_left) != 0)
                    && (link->get_qualifier() == in_qualifier) )
                {
                    if (   (in_member_other == 0                           )
                        || (in_member_other == &(link->get_member_right())) )
                    {
                        return link;                        
                    }
                }
                link = link->get_link_next_left();
            }
            else if ( &in_member_dominant == &(link->get_member_right()) )
            {
                if (   ((in_side_matching & side_right) != 0)
                    && (link->get_qualifier() == in_qualifier) )
                {
                    if (   (in_member_other == 0                          )
                        || (in_member_other == &(link->get_member_left())) )
                    {
                        return link;                        
                    }
                }
                link = link->get_link_next_right();
            }
            else // dominant not in this link (erroneous condition)
            {
                return 0;
            }
        }
        while (link != 0);
        return 0;
    }
    association_typed *         find_link_matching_qualifier_nc(
        member_type &               in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        qualifier_type              in_qualifier,       ///< match only with this qualifier
        member_type *               in_member_other = 0 ) ///< zero matches any secondary
    {
        return const_cast<association_typed*>(
            const_cast<const association_typed*>(this)->findMachingLink(
                in_member_dominant, in_side_matching, in_qualifier, in_member_other ));
    }
    const association_typed *   find_link_matching_next(
        const member_type &         in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        qualifier_type              in_qualifier,       ///< match only with this qualifier
        const member_type *         in_member_other = 0 ) const ///< zero matches any secondary
    {
        const association_typed * linknext = find_link_next( in_member_dominant );
        return (linknext == 0 ? 0 : linknext->find_link_matching_qualifier(
            in_member_dominant, in_side_matching, in_qualifier, in_member_other ));
    }        
    association_typed *         find_link_matching_next_nc(
        member_type &               in_member_dominant, ///< traverses chain of dominant
        side                        in_side_matching,   ///< match only when dominant on this side (can be EitherSide)
        qualifier_type              in_qualifier,       ///< match only with this qualifier
        member_type *               in_member_other = 0 ) ///< zero matches any secondary
    {
        return const_cast<association_typed*>(
            const_cast<const association_typed*>(this)->find_link_matching_next(
                in_member_dominant, in_side_matching, in_qualifier, in_member_other ));
    }

protected:

    void                internal_init(
        member_type &       in_left_member,
        member_type &       in_right_member,
        qualifier_type      in_qualifier )
    {
        association::internal_init(
            &in_left_member, &in_right_member );
        _qualifier = in_qualifier;
    }

private:

    qualifier_type _qualifier;

}; // end of template class association_typed

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_ASSOCIATION_TYPED
