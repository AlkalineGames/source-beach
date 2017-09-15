#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_SPEC)
#define      BEACH_SERIALIZATION_SERIALIZABLE_SPEC
//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_spec.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/object_identifier.hpp>

namespace serialization
{
    using atoms::stringex;
    using atoms::text;
    using lifecycle::class_identifier;
    using lifecycle::object_identifier;

//--------------------------------------

/// identity specifier for a serializable object

class serializable_spec
{
public:

    class_identifier    _class_id;
    stringex            _class_name;
    object_identifier   _object_id;
    stringex            _object_name;

    BEACH_ALLOCATION_OPERATORS

    serializable_spec(
        class_identifier    in_class_id     = 0,
        const text *        in_class_name   = 0,        
        object_identifier   in_object_id    = 0,
        const text *        in_object_name  = 0 )
      :
        _class_id(          in_class_id     ),
        _class_name(        in_class_name   ),
        _object_id(         in_object_id    ),
        _object_name(       in_object_name  )
    {}
    serializable_spec(
        class_identifier    in_class_id,
        const stringex &    in_class_name,
        object_identifier   in_object_id,
        const stringex &    in_object_name )
      :
        _class_id(          in_class_id     ),
        _class_name(        in_class_name   ),
        _object_id(         in_object_id    ),
        _object_name(       in_object_name  )
    {}

    stringex to_string() const;
    stringex to_string_resolved();

}; // end of class serializable_spec

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_SPEC
