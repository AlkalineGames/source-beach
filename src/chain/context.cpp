//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       context.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/context.hpp> // this header

namespace chain
{

//--------------------------------------
//  public methods
//--------------------------------------

const context_linked *
context::find(
    linked::class_identity in_class_id ) const
{
    return (_first == 0) ? 0 : _first->find( in_class_id );
}

//--------------------------------------

void
context::append(
    context_linked & in_context_linked )
{
    if ( _first == 0 )
    {
        _first = &in_context_linked;
    }
    else
    {
        _first->append( in_context_linked );
    }
}

//--------------------------------------

context_linked::context_linked(
    class_identity in_cid )
  :
    linked( in_cid )
{}
    
//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
