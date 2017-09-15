//----------------------------------------------------------
//  Copyright 2008-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group_vector.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_group_vector.hpp> // this header

//--------------------------------------

namespace taxonomy
{

//--------------------------------------
//  public methods
//--------------------------------------

template <typename T>
property_group_vector<T>::property_group_vector(
    collection &                in_collection,
    const text *                in_property_name )
  :
    property_group_collection(  in_collection,
                                in_property_name )
{}

//--------------------------------------

// virtual
template <typename T>
stringex
property_group_vector<T>::get_property_value() const
{
    return property_group_collection::get_property_value();
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
template <typename T>
const property_group *
property_group_vector<T>::get_property_group(
    property_index in_index ) const
{
    if ( in_index <= _collection.size() )
    {
        return &(get_collection_const()[in_index-1]);
    }
    return 0;
}

//--------------------------------------

// virtual
template <typename T>
stringex
property_group_vector<T>::get_property_value(
    property_index in_index ) const
{
    if ( in_index <= _collection.size() )
    {
        return get_collection_const()[in_index-1].get_property_value();
    }
    return 0;
}

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
// $Log: property_group_vector.tpp,v $
// Revision 1.1  2008/04/30 19:49:26  cat
// created
//
//----------------------------------------------------------

// (end of file)
