#if !defined(BEACH_TAXONOMY_PROPERTY_VECTOR)
#define      BEACH_TAXONOMY_PROPERTY_VECTOR
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_vector.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <geometry/vector.hpp>
#include <taxonomy/property_imp.hpp>

namespace taxonomy
{

//--------------------------------------

/// interface to a dynamic property
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property_vector
    : public property_imp
{
public:

    typedef geometry::vector_xyz<real> vector;

	property_vector( const stringex & in_name );
	property_vector( const stringex & in_name,
                     const vector & in_default_value );
	virtual ~property_vector();

	const vector &  get_value() const { return _value; }
	void            set_value( const vector & in_value ) { _value = in_value; }

private:

    vector _value;
};

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_VECTOR
