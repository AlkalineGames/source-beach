//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       linked.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/linked.hpp> // this header

namespace chain
{

//--------------------------------------
//  protected methods
//--------------------------------------

linked::linked(
    class_identity  in_class_id )
  :
    _class_id(      in_class_id ),
    _next(          0 )
{}

//--------------------------------------

// virtual
linked::~linked()
{}

//--------------------------------------

const linked &
linked::get_last() const
{
    const linked * last = this;
    while ( last->get_next() != 0 )
    {
        last = last->get_next();
    }
    return *last;
}

//--------------------------------------

const linked *
linked::find(
    linked::class_identity in_class_id ) const
{
    const linked * ext = this;
    while ( ext->get_class_id() != in_class_id )
    {
        ext = ext->get_next();
        if ( ext == 0 )
        {
            break;
        }
    }
    return ext;
}

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
