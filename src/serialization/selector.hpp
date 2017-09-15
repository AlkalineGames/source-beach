#if !defined(BEACH_SERIALIZATION_SELECTOR)
#define      BEACH_SERIALIZATION_SELECTOR
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       selector.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace serialization
{
    using atoms::boolean;
    using atoms::stringex;
    using atoms::whole16;

//--------------------------------------

/// selector for serialization
/**
 *  A selector is a sequence of parts that are each two
 *  bytes/characters in length. Each selector part corresponds
 *  to a single part selector registered by a serializable class.
 *  Selectors that contain zero or more of these parts, are
 *  typically applied as a mask to indicate inclusion of the
 *  selected attributes. Since each two byte/character part
 *  is a binary value, the string data is very likely not 
 *  printable. Also, there can be bytes of zero value within the
 *  string array data, so treating the character array as a null- 
 *  terminated string may yield undesirable results.
 */ 
class selector
    : public stringex
{
public:

    selector() {}

    /// @note looks for exact match of selector parameter
    //@{
    boolean includes( const selector & ) const;

    void exclude( const selector & );
    void include( const selector & s )
    {
        if ( ! includes( s ) )
        {
            *this += s;
        }
    }
    //@}

    void increment(); ///< only works on single-part selectors

    whole16 get_value() const;
    void    set_value( whole16 );

}; // end of class selector

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SELECTOR
