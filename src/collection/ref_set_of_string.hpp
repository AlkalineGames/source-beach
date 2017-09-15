#if !defined(BEACH_COLLECTION_REF_SET_OF_STRING)
#define      BEACH_COLLECTION_REF_SET_OF_STRING
//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_set_of_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham, Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <collection/ref_set.hpp>

namespace collection
{
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// set of string references
/**
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
class ref_set_of_string 
    : public ref_set<stringex>
{
public:

    ref_set_of_string();
    ref_set_of_string( const atoms::destroyer_typed<stringex> & );
    ref_set_of_string(                    const ref_set_of_string & rhs );
    const ref_set_of_string & operator =( const ref_set_of_string & rhs );

    const_iterator find_match( const stringex & )   const;
    const_iterator find_match( const text * )       const;

}; // end of class ref_set_of_string

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_REF_SET_OF_STRING
