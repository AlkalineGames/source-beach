//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_reals.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_reals.hpp> // this header

namespace taxonomy
{

//--------------------------------------
//  public methods
//--------------------------------------

property_reals::property_reals(
    const text *    in_name,
    whole           in_count,
    real            in_values[] )
 :
    property_imp(   in_name ),
    _count(         in_count ),
    _values(        new BEACH_ALLOCATION real[_count] )
{
    for ( whole index = 0; index < _count; index++ )
    {
        real value = (in_values != 0) ? in_values[index] : 0;
        _values[index] = value;
    }
}

//--------------------------------------

// virtual
property_reals::~property_reals()
{
    BEACH_DELETE_WITHOUT_DESTRUCT(_values);
}

//--------------------------------------

// virtual
real
property_reals::get_real(
    whole in_index ) const
{
    if ( in_index < _count )
    {
        return _values[in_index];
    }
    return 0;
}

//--------------------------------------

}  // end namespace simulation

//----------------------------------------------------------
// (end of file)
