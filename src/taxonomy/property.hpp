#if !defined(BEACH_TAXONOMY_PROPERTY)
#define      BEACH_TAXONOMY_PROPERTY
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace atoms
{
    class stringex;
};

/// Beach Taxonomy Framework
namespace taxonomy
{
    using atoms::pointer;
    using atoms::real;
    using atoms::stringex;
    using atoms::whole;

//--------------------------------------

/// interface to a dynamic property
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List [PLoP5]
 */      
class property
{
public:

    virtual const stringex &    get_name() const = 0;

    /// @name value accessors
    //@{
    virtual pointer             get_pointer(    whole in_index = 0 ) const = 0;
    virtual real                get_real(       whole in_index = 0 ) const = 0;
    virtual const stringex &    get_string(     whole in_index = 0 ) const = 0;
    //@}

protected:

    virtual ~property() = 0;

}; // end of class property

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY
