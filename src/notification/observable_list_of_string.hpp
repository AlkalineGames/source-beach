#if !defined(BEACH_NOTIFICATION_OBSERVABLE_LIST_OF_STRING)
#define      BEACH_NOTIFICATION_OBSERVABLE_LIST_OF_STRING
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_list_of_string.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <notification/observable_list.hpp>

namespace notification
{
    using atoms::stringex;

//--------------------------------------

typedef observable_list<stringex>
    observable_list_of_string_superclass;

//--------------------------------------

/// class template adapter for a string list that notify observers
/**
 *  @note   design patterns applied:
 *              - Adapter  [GoF]
 *              - Observer [GoF] [PLoP2] [cat]
 */     
class observable_list_of_string
    : public observable_list_of_string_superclass
{
public:

    observable_list_of_string();               ///< leaves ownership
    observable_list_of_string( ownership );    ///< takes ownership, regardless of passed value
    virtual ~observable_list_of_string();

    stringex    to_string();
    void        parse_string_into_elements(
                    const stringex & );

}; // end of class observable_list_of_string
    
//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_LIST_OF_STRING
