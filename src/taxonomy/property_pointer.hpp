#if !defined(BEACH_TAXONOMY_PROPERTY_POINTER)
#define      BEACH_TAXONOMY_PROPERTY_POINTER
//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_pointer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <taxonomy/property_imp.hpp>

namespace taxonomy
{

//--------------------------------------

/// property: pointer
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property_pointer
    : public property_imp
{
public:
        
	property_pointer(
        const stringex &    in_name,
        pointer             in_value );

	virtual ~property_pointer();

    /// @name value accessors overrides
    //@{
    virtual pointer     get_pointer( whole in_index = 0 ) const;
    //@}

	pointer             get_value() const { return _value; }
	void                set_value(
        pointer             in_value )
    {
        _value = in_value;
    }

private:

    pointer _value;

}; // end of class stringex

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_POINTER
