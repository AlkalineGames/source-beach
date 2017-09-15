//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       association.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/association.hpp> // this header

namespace chain
{

//--------------------------------------
//  public methods
//--------------------------------------

const association *
association::find_link_matching(
    pointer_to_const    in_member_dominant,
    side                in_matching_side, 
    pointer_to_const    in_member_other ) const
{
    const association * link = this;
    do
    {
        if ( in_member_dominant == link->get_member_left() )
        {
            if (   ((in_matching_side & side_left) != 0)
                && (in_member_other == link->get_member_right()) )
            {
                return link;                        
            }
            link = link->get_link_next_left();
        }
        else if ( in_member_dominant == link->get_member_right() )
        {
            if (   ((in_matching_side & side_right) != 0)
                && (in_member_other == link->get_member_left()) )
            {
                return link;                        
            }
            link = link->get_link_next_right();
        }
        else // dominant not in this link (erroneous condition)
        {
            return 0;
        }
    }
    while ( link != 0 );
    return 0;
}

//--------------------------------------

const association *
association::find_link_next(
    pointer_to_const in_member ) const
{
    const association * linknext;
    if ( in_member == get_member_left() )
    {
        linknext = get_link_next_left();
    }
    else if ( in_member == get_member_right() )
    {
        linknext = get_link_next_right();
    }
    else
    {
        linknext = 0;
    }
    return linknext;
}        

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
