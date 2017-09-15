#if !defined(BEACH_TAXONOMY_PROPERTY_REALS)
#define      BEACH_TAXONOMY_PROPERTY_REALS
//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_reals.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_imp.hpp>

namespace taxonomy
{

//--------------------------------------

/// property: array of reals
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */
class property_reals
    : public property_imp
{
public:

    property_reals(
        const text *    in_name,
        whole           in_count,
        real            in_values[] = 0 );

    virtual ~property_reals();

    /// @name value accessors
    //@{
    virtual real get_real( whole in_index = 0 ) const;
    //@}

private:

    whole   _count;
    real *  _values;

}; // end of class property

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_REALS
