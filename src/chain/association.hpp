#if !defined(BEACH_CHAIN_ASSOCIATION)
#define      BEACH_CHAIN_ASSOCIATION
//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       association.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace chain
{
    using atoms::pointer;
    using atoms::pointer_to_const;
    using atoms::whole8;

//----------------------------------------------------------

/// abstract superclass for an association between two objects, linked to other associations
/**
 *  Linking association objects yield unbounded virtual n-ary networks
 *  without the need to manage separate collection objects, as well as
 *  optimal traversal across all associations for any given object. 
 */
class association
{
public:

    enum side
    {
        side_neither,    // 0x00,
        side_left,       // 0x01,
        side_right,      // 0x10,
        side_either,     // 0x11 bitwise combination
        side_count
    };
    static side calc_side_opposite( side s )
    {
        return side((~whole8(s)) & whole8(side_either));
    }
    association()
      :
        _member_left(       0 ),
        _member_right(      0 ),
        _link_next_left(    0 ),
        _link_next_right(   0 )
    {}
    association(
        pointer             in_member_left,
        pointer             in_member_right,
        association *       in_link_next_left   = 0,
        association *       in_link_next_right  = 0 )
      :
        _member_left(       in_member_left ),
        _member_right(      in_member_right ),
        _link_next_left(    in_link_next_left ),
        _link_next_right(   in_link_next_right )
    {}

    pointer_to_const    get_member_left()           const { return _member_left; }
    pointer             get_member_left_nc()              { return _member_left; }
    pointer_to_const    get_member_right()          const { return _member_right; }
    pointer             get_member_right_nc()             { return _member_right; }
    pointer_to_const    get_member( side in_side )  const
    {
        return  (in_side == side_left ) ? _member_left  :
               ((in_side == side_right) ? _member_right : 0);
    }
    pointer             get_member_nc( side in_side )
    {
        return  (in_side == side_left ) ? _member_left  :
               ((in_side == side_right) ? _member_right : 0);
    }
    side                get_side( pointer_to_const in_member ) const
    {
        return  (_member_left  == in_member) ? side_left  :
               ((_member_right == in_member) ? side_right : side_neither);
    }
    const association * get_link_next_left()  const { return _link_next_left; }
          association * get_link_next_left_nc()     { return _link_next_left; }
    void                set_link_next_left(
          association *     in_link )               { _link_next_left = in_link; }

    const association * get_link_next_right() const { return _link_next_right; }
          association * get_link_next_right_nc()    { return _link_next_right; }
    void                set_link_next_right(
          association *     in_link )               { _link_next_right = in_link; }

    const association * get_link_next( side in_side ) const
    {
        return ((in_side == side_left ) ? _link_next_left  :
               ((in_side == side_right) ? _link_next_right : 0));
    }
          association * get_link_next_nc( side in_side )
    {
        return ((in_side == side_left ) ? _link_next_left  :
               ((in_side == side_right) ? _link_next_right : 0));
    }
    void                set_link_next(
        side                in_side,
        association *       in_link )
    {
        if ( in_side == side_left )
        {
            _link_next_left = in_link;
        }
        else if ( in_side == side_right )
        {
            _link_next_right = in_link;
        }
    }
    pointer_to_const    find_peer_of( pointer_to_const in_member ) const
    {
        return  (in_member == _member_left ) ? _member_right :
               ((in_member == _member_right) ? _member_left  : 0);
    }
    pointer             find_peer_nc_of( pointer_to_const in_member )
    {
        return  (in_member == _member_left ) ? _member_right :
               ((in_member == _member_right) ? _member_left  : 0);
    }
    const association * find_link_matching(
        pointer_to_const    in_member_dominant,     ///< traverses chain of dominant
        side                in_side_matching,       ///< match only when dominant on this side (can be side_either)
        pointer_to_const    in_member_other ) const;

          association * find_link_matching_nc(
        pointer_to_const    in_member_dominant,     ///< traverses chain of dominant
        side                in_side_matching,       ///< match only when dominant on this side (can be side_either)
        pointer_to_const    in_member_other )
    {
        return const_cast<association*>(
            const_cast<const association*>(this)->find_link_matching(
                in_member_dominant, in_side_matching, in_member_other ));
    }
    const association * find_link_next(    pointer_to_const in_member ) const;
          association * find_link_next_nc( pointer_to_const in_member )
    {
        return const_cast<association*>(
            const_cast<association*>(this)->find_link_next( in_member ));
    }

protected:

    void internal_init(
        pointer         in_left_member,
        pointer         in_right_member )
    {
        _member_left  = in_left_member;
        _member_right = in_right_member;
    }

private:

    pointer         _member_left;
    pointer         _member_right;
    association *   _link_next_left;
    association *   _link_next_right;

}; // end of class association

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
#endif // BEACH_CHAIN_ASSOCIATION
