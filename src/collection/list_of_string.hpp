#if !defined(BEACH_COLLECTION_LIST_OF_STRING)
#define      BEACH_COLLECTION_LIST_OF_STRING
//----------------------------------------------------------
//  Copyright 1999-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       list_of_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham, Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/stringex.hpp>

#include <list>

namespace collection
{
    using atoms::boolean;
    using atoms::stringex;

//--------------------------------------

/// list of strings
/**
 *  This is a copy/value collection.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */
class list_of_string 
    : public std::list<stringex>
{
public:

    BEACH_ALLOCATION_OPERATORS

    list_of_string();
    list_of_string(                    const list_of_string & rhs );
    const list_of_string & operator =( const list_of_string & rhs );

    void add_parsed_list(  const stringex & );

}; // end of class list_of_string

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
#endif // BEACH_COLLECTION_LIST_OF_STRING
