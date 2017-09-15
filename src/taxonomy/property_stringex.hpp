#if !defined(BEACH_TAXONOMY_PROPERTY_STRINGEX)
#define      BEACH_TAXONOMY_PROPERTY_STRINGEX
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_stringex.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <taxonomy/property_imp.hpp>

namespace taxonomy
{
    using atoms::boolean;
    using atoms::integer;

//--------------------------------------

/// property: string
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property_stringex
    : public property_imp
{
public:
        
	property_stringex(
        const stringex & in_name,
        const stringex & in_value );

	virtual ~property_stringex();

    /// @name value accessors overrides
    //@{
    virtual const stringex & get_string( whole in_index = 0 ) const;
    //@}

	const stringex &    get_value() const { return _value; }
	void                set_value(
        const stringex &    in_value )
    {
        _value = in_value;
    }

    /// @name conversion @@@ REFACTOR THIS
    //@{
    boolean to_boolean()    const;
    integer to_integer()    const;
    real    to_real()       const;
    whole   to_whole()      const;
    //@}

	boolean get_boolean()   const { return to_boolean(); }
        ///< @deprecated synonym

private:

    stringex _value;

}; // end of class stringex

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_STRINGEX
