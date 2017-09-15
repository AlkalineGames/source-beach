#if !defined(BEACH_TAXONOMY_PROPERTY_RANGE)
#define      BEACH_TAXONOMY_PROPERTY_RANGE
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_range.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <taxonomy/property_imp.hpp>

namespace taxonomy
{
    using atoms::boolean;

//--------------------------------------

/// a range of real numbers
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property_range
    : public property_imp
{
public:

	property_range(
        const stringex &    in_name,
        const real          in_range1,
        const real          in_range2 )
      :
        property_imp(       in_name ),
        _range1(            in_range1 ),
        _range2(            in_range2 )
    {}
	boolean     member_of( real range1, real range2 )
    {
        return (range1 >= _range1) && (range2 <= _range2);
    }

	const real  get_range1() const          { return _range1; }
	const real  get_range2() const          { return _range2; }
	void        set_range1( real range1 )   { _range1 = range1; }
	void        set_range2( real range2 )   { _range2 = range2; }

private:

	real  _range1;
	real  _range2;
};

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_RANGE

