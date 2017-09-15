#if !defined(BEACH_TAXONOMY_PROPERTY_SCALAR)
#define      BEACH_TAXONOMY_PROPERTY_SCALAR
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_scalar.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <taxonomy/property_imp.hpp>

namespace taxonomy
{

//--------------------------------------

/// a single real number
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property_scalar
    : public property_imp
{
public:

	property_scalar(
        const stringex &    in_name,
        const real          in_value )
      :
        property_imp(       in_name ),
        _value(             in_value )
    {}

	virtual ~property_scalar();

	const real  get_value() const   { return _value; }
	void        set_value( real v ) { _value = v; }

private:

    real _value;
};

//--------------------------------------

} // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_SCALAR
