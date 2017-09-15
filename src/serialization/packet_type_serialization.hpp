#if !defined(BEACH_SERIALIZATION_SERIALIZATION_PACKET_TYPE)
#define      BEACH_SERIALIZATION_SERIALIZATION_PACKET_TYPE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_type_serialization.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/packet_type.hpp>

namespace serialization
{

//--------------------------------------

class packet_type_serialization
    : public notification::packet_type
{
public:

    enum type_enum
    {
        type_serializable = notification::packet_type::next_type, // 2
        next_type
    };
};

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZATION_PACKET_TYPE
