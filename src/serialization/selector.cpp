//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       selector.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/selector.hpp> // this header
#include <atoms/stringex.hpp>

//--------------------------------------

namespace serialization
{
    using namespace atoms;
    using atoms::stringex;

//--------------------------------------
//  internal definitions
//--------------------------------------

enum { selector_part_length = 2 };

//--------------------------------------
//  public methods
//--------------------------------------

boolean
selector::includes(
    const selector & in_selector ) const
{
    if ( in_selector.get_size() == 0 )
    {
        return false;
    }
    whole i = 0;
    while ( (i+in_selector.get_size()) <= get_size() )
    {
        boolean matches = true;
        for ( whole j = 0; j < in_selector.get_size(); j++ )
        {
            if ( (*this)[i+j] != in_selector[j] )
            {
                matches = false;
                break;
            }
        }
        if ( matches )
        {
            return true;
        }
        i += selector_part_length;
    }
    return false;
}

//--------------------------------------

void
selector::exclude(
    const selector & in_selector )
{
    whole i = 0;
    while ( (i+in_selector.get_size()) <= get_size() )
    {
        boolean matches = true;
        for ( whole j = 0; j < in_selector.get_size(); j++ )
        {
            if ( (*this)[i+j] != in_selector[j] )
            {
                matches = false;
                break;
            }
        }
        if ( matches )
        {
            erase( i, selector_part_length );
        }
        else
        {
            i += selector_part_length;
        }
    }
}

//--------------------------------------

void
selector::increment()
{
    // uninitialized, set to first value
    if ( get_size() == 0 )
    {
        for ( whole i = 0; i < selector_part_length; i++ )
        {
            (*this) += '\x01';
        }
    }
    if ( get_size() > selector_part_length )
    {
        return; // only works on single-part selectors
    }
    // increment the character values from least to most
    for ( whole j = (selector_part_length-1); j >= 0; j-- )
    {
        unsigned char c = ((*this)[j] + 1);
        if ( c != '\0' )
        {
            (*this)[j] = c;
            break;
        }
        (*this)[j] = '\x01';
    }
}

//--------------------------------------

whole16
selector::get_value() const
{
    return (whole16(at( 0 )) << 8) + whole16(at( 1 ));
}

//--------------------------------------

void
selector::set_value(
    whole16 in_value )
{
    erase();
    (*this) += (unsigned char)(in_value >> 8);
    (*this) += (unsigned char)(in_value & 255);
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: selector.cpp,v $
// Revision 1.6  2006/05/03 14:06:31  cat
// refactored class id and selectors
//
// Revision 1.5  2006/04/27 02:39:45  def
// new stringex implementation which removes stl subclass which caused problems with dll's
//
// Revision 1.4  2005/12/14 02:48:36  cat
// set_value(...)
//
// Revision 1.3  2004/07/10 21:24:30  cat
// renamed Selector to selector
//
// Revision 1.2  2003/10/24 16:43:39  cat
// includes(...): return false if selector is null
//
// Revision 1.1.1.1  2002/07/14 20:16:50  cat
// first import
//----------------------------------------------------------

// (end of file)
