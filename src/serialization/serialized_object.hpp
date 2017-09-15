#if !defined(BEACH_SERIALIZATION_SERIALIZED_OBJECT)
#define      BEACH_SERIALIZATION_SERIALIZED_OBJECT
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serialized_object.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <lifecycle/counted_object.hpp>
#include <lifecycle/identified_object.hpp>
#include <lifecycle/object_identification_id_name.hpp>
#include <serialization/serializable.hpp>

namespace serialization
{
    using atoms::text;
    using lifecycle::counted_object;
    using lifecycle::identified_object;
    using lifecycle::object_identification;
    using lifecycle::object_identification_id_name;

//--------------------------------------

/// superclass for a canonical serialized object

class serialized_object
    : public counted_object,
      public identified_object,
      public serializable
{
protected:

    BEACH_ALLOCATION_OPERATORS

    serialized_object(
        id_value        in_id,
        const text *    in_name );

    virtual ~serialized_object();

    /// identified_object override
    virtual object_identification & get_identification_nc();

private:

    /// @name copy operations not implemented
    //@{
    serialized_object(               const serialized_object & );
    serialized_object & operator = ( const serialized_object & );
    //@}

    object_identification_id_name _identification;

}; // end of class serialized_object

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZED_OBJECT
