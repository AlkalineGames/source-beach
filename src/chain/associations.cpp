//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       associations.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/associations.hpp> // this header

namespace chain
{

//--------------------------------------
//  public methods
//--------------------------------------

const association *
associations::find_link(
    association::side  in_side_matching, // side_either is allowed
    pointer_to_const        in_member_other ) const
{
    if ( get_link_first() == 0 )
    {
        return 0;
    }
    pointer_to_const memdom = get_member_dominant();
    if ( memdom == 0 )
    {
        return 0;
    }
    return get_link_first()->find_link_matching( 
        memdom, in_side_matching, in_member_other );
}

//--------------------------------------

void
associations::insert_link(
    association::side      in_side_dominant,
    association &          in_link,
    associations &    in_chain_other )
{
    perform_insert( in_side_dominant, in_link );
    association::side sideother =
        association::calc_side_opposite( in_side_dominant );
    in_chain_other.perform_insert( sideother, in_link );
}

//--------------------------------------

void
associations::remove_link(
    association &          in_link,
    associations &    in_chain_other )
{ 
    perform_remove( in_link );
    in_chain_other.perform_remove( in_link );
}

//--------------------------------------
//  private methods
//--------------------------------------

void
associations::perform_insert(
    association::side  in_side_dominant,
    association &      in_link )
{
    if ( _link_first != 0 )
    {
        in_link.set_link_next( in_side_dominant, _link_first );
    }
    _side_dominant_first = in_side_dominant;
    _link_first          = &in_link;
}

//--------------------------------------

void
associations::perform_remove(
    association & in_link )
{ 
    if ( _link_first == 0 )
    {
        return; // no links here
    }
    // find the previous and new next links
    association *     linkprev = _link_first;
    association::side sideprev = _side_dominant_first;
    association *     linknext;
    association::side sidenext;
    while ( true )
    {
        linknext = linkprev->get_link_next_nc( sideprev );
        if ( linknext == 0 )
        {
            sidenext = association::side_neither;
            break;
        }
        pointer member = linkprev->get_member_nc( sideprev );
        if ( linknext->get_member_left() == member )
        {
            sidenext = association::side_left;
        }
        else if ( linknext->get_member_right() == member )
        {
            sidenext = association::side_right;
        }
        else // this erroneous condition shouldn't happen
        {
            sidenext = association::side_neither;
            break;
        }
        if ( linkprev == &in_link )
        {
            break;  // only happens when in_link == _link_first
        }
        if ( linknext == &in_link )
        {
            linknext = linknext->get_link_next_nc( sidenext );
            break;
        }
        linkprev = linknext;
        sideprev = sidenext;
    }
    if ( &in_link == _link_first )
    {
        _link_first          = linknext;
        _side_dominant_first = sidenext;
    }
    else 
    {
        linkprev->set_link_next( sideprev, linknext );
    }
}

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
