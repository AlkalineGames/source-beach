//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       context_reading.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/context_reading.hpp> // this header

#include <chain/context.hpp>
#include <lifecycle/class_catalog.hpp>

namespace serialization
{
    using namespace atoms;
    using lifecycle::class_catalog;
    using lifecycle::class_info;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text name_this_class[]
    = "context_reading";

static const class_info * this_class_info = 0;

//--------------------------------------
//  protected methods
//--------------------------------------

// static
context_reading::class_identity
context_reading::acquire_class_id()
{
    if ( this_class_info == 0 )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        this_class_info = catalog.resolve_class_by_name(
            name_this_class, false ); // cannot fail
    }
    return this_class_info->get_class_id();
}

//--------------------------------------


context_reading::context_reading()
  :
    context_linked( acquire_class_id() ),
    _sender_id( 0 )
{}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
