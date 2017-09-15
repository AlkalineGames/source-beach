//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extensions.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/extensions.hpp> // this header

namespace chain
{

//--------------------------------------
//  public methods
//--------------------------------------

const extension *
extensions::get_last()  const
{
    if ( get_first() != 0 )
    {
        return static_cast<const extension*>(&(get_first()->get_last()));
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

const extension *
extensions::find(
    extension::class_identity in_class_id ) const
{
    if ( get_first() != 0 )
    {
        return static_cast<const extension*>(get_first()->find( in_class_id ));
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

void
extensions::destroy(
    extension & in_extension )
{
    extension * prev = 0;
    extension * ext  = _first;
    while ( ext != 0 )
    {
        extension * next = ext->get_next_nc();
        if ( ext == &in_extension )
        {
            if ( prev != 0 )
            {
                prev->set_next( next );
            }         
            else
            {
                _first = next;
            }       
            delete ext;
            break;
        }
        prev = ext;
        ext  = next;
    }
}

//--------------------------------------

void
extensions::destroy(
    extension::class_identity in_class_id )
{
    extension * prev = 0;
    extension * ext  = _first;
    while ( ext != 0 )
    {
        extension * next = ext->get_next_nc();
        if ( ext->get_class_id() == in_class_id )
        {
            if ( prev != 0 )
            {
                prev->set_next( next );
            }         
            else
            {
                _first = next;
            }       
            delete ext;
            break;
        }
        prev = ext;
        ext  = next;
    }
}

//--------------------------------------
//  protected methods
//--------------------------------------

extensions::~extensions()
{
    extension * ext = _first;
    while ( ext != 0 )
    {
        extension * next = ext->get_next_nc();
        delete ext;
        ext = next;
    }
}

//--------------------------------------

void
extensions::add(
    extension & in_extension )
{
    if ( _first == 0 )
    {
        _first = &in_extension;
    }
    else
    {
        extension * last = get_last_nc();
        last->set_next( &in_extension );
    }
}

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
