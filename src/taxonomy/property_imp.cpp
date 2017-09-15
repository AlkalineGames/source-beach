//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_imp.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <taxonomy/property_imp.hpp> // this header

#include <taxonomy/taxonomy_manager.hpp>

namespace taxonomy
{

//--------------------------------------
//  public methods
//--------------------------------------

property_imp::property_imp()
 :
    _name( taxonomy_manager::acquire_singleton().acquire_label( "(unknown)" ) )
{}

//--------------------------------------

property_imp::property_imp(
    const text * in_name )
 :
    _name( taxonomy_manager::acquire_singleton().acquire_label( in_name ) )
{}

//--------------------------------------

// virtual
property_imp::~property_imp()
{}

//--------------------------------------

// virtual
const stringex &
property_imp::get_name() const
{
    return _name;
}

//--------------------------------------

// virtual
pointer
property_imp::get_pointer(
    whole in_index ) const
{
    return 0;
}

//--------------------------------------

// virtual
real
property_imp::get_real(
    whole in_index ) const
{
    return 0;
}

//--------------------------------------

// virtual
const stringex &
property_imp::get_string(
    whole in_index ) const
{
    taxonomy_manager::acquire_singleton().get_label_null();
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
property::~property() // = 0
{}

//--------------------------------------

}  // end namespace simulation

//----------------------------------------------------------
// (end of file)
