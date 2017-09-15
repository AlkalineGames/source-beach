#if !defined(BEACH_NOTIFICATION_PACKET_TYPE)
#define      BEACH_NOTIFICATION_PACKET_TYPE
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_type.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace notification
{

//--------------------------------------

class packet_type
{
public:

    enum type_enum
    {
        no_type,
   
        type_command_packeted, // 1

        next_type
    };
};

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKET_TYPE
