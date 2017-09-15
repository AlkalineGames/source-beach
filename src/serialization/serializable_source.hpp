#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_SOURCE)
#define      BEACH_SERIALIZATION_SERIALIZABLE_SOURCE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
/**
 *  @file       serializable_source.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace serialization
{
    using atoms::boolean;

//--------------------------------------

/// interface for the source of a serializable object
/**
 *  This is provided so that serializable objects can
 *  indicate to their sources when they are changed (dirty).
 *
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */ 
class serializable_source
{
public:

    enum dirty_flags ///< bitwise flags that can be combined
    {
        not_dirty               = 0x0000,
        dirty_source_copied     = 0x0001,
        dirty_source_revised    = 0x0002,
        dirty_objects_changed   = 0x0004,
        dirty_content_changed   = 0x0008
    };

    virtual dirty_flags get_dirty_flags() const = 0;
    virtual void        add_dirty_flags(
        dirty_flags         in_dirty_flags,
        boolean             in_ignore_while_importing = false )  = 0;

    boolean is_dirty() const { return (get_dirty_flags() != not_dirty); }
     
}; // end of class serializable

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_SOURCE
