#if !defined(BEACH_TAXONOMY_PROPERTY_IMP)
#define      BEACH_TAXONOMY_PROPERTY_IMP
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_imp.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <taxonomy/property.hpp>

namespace taxonomy
{
    using atoms::text;

//--------------------------------------

/// dynamic property implementation superclass
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List    [PLoP5]
 *              - Null Object                           [PLoP3]
 */      
class property_imp
    : public property
{
public:

    property_imp(); ///< sets name to "(unknown)"
    property_imp( const text * in_name );
    virtual ~property_imp();

    virtual const stringex &    get_name()  const;

    /// @name value accessors
    //@{
    virtual pointer             get_pointer(    whole in_index = 0 ) const;
        ///< this level returns 0
    virtual real                get_real(       whole in_index = 0 ) const;
        ///< this level returns 0
    virtual const stringex &    get_string(     whole in_index = 0 ) const;
        ///< this level returns the empty string
    //@}

private:

    const stringex & _name;

}; // end of class property

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_IMP
