#if !defined(BEACH_NOTIFICATION_PACKETED_COMMAND)
#define      BEACH_NOTIFICATION_PACKETED_COMMAND
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_packeted.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/class_catalog.hpp>
#include <lifecycle/class_identifier.hpp>
#include <invocation/command_abstract.hpp>
#include <notification/packet.hpp>
#include <notification/packet_type.hpp>

namespace notification
{
    using atoms::boolean;
    using atoms::size_type;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole8;
    using invocation::command;
    using invocation::command_abstract;

//--------------------------------------

/// abstract superclass

class command_packeted
    : public command_abstract
{
public:

    typedef lifecycle::class_identifier class_identity; /// @deprecate
    typedef whole8 priority;
    enum { default_priority = 20 };
    class header : public packet_header
    {
    public:

        header()
          :
            packet_header( packet_type::type_command_packeted, 0, 1, 0, 0 )
        {}
        header( const header & rhs )
          :
            packet_header( rhs )
        {}

        void setDataSize( size_type s ) { _dataSize = s; }
		void setPriority( priority p )  { _priority = p; }
    };

    /// if not set, returns and sets priority to default_priority + in_modifier
    static command_packeted::priority get_class_priority( const stringex & in_key, priority in_modifier = 0 );
    static void                      set_class_priority( const stringex & in_key, priority );
    
    virtual ~command_packeted();

    virtual class_identity  getClassId()    const = 0;
    virtual size_type       getPacketSize() const = 0;
    virtual packet &        getPacket()           = 0;
      const packet &        getPacket()     const
    {   return const_cast<command_packeted&>(*this).getPacket(); }

    channel_identifier get_sender_id() const
    {
        return getPacket().getHeader().get_sender_id();
    }

    boolean initPacket( const packet & ); // false if cannot initialize

protected:

    command_packeted( const text * in_name = 0 );
    command_packeted( const command_packeted & );

}; // end of class command_packeted

//--------------------------------------
//  macros
//--------------------------------------

#define BEACH_PACKET _packet
#define BEACH_PACKET_BEGIN struct P { header _header; class_identity _classId;
#define BEACH_PACKET_END } BEACH_PACKET;

//--------------------------------------

#define BEACH_PACKET_INIT(CLASS,PRIORITY) \
BEACH_PACKET._header.setDataSize( sizeof(BEACH_PACKET)-sizeof(header) ); \
BEACH_PACKET._header.setPriority( PRIORITY ); \
BEACH_PACKET._classId = lifecycle::class_catalog::get_singleton().resolve_class_by_id_or_name( class_id_ ## CLASS, # CLASS )->get_class_id();

//--------------------------------------

#define BEACH_DECLARE_PACKETED_COMMAND_OVERRIDES \
virtual lifecycle::class_identifier getClassId()    const; \
virtual atoms::size_type            getPacketSize() const; \
virtual notification::packet &      getPacket();

//--------------------------------------

#define BEACH_IMPLEMENT_PACKETED_COMMAND_OVERRIDES(SUBCLASS_NAME) \
lifecycle::class_identifier \
SUBCLASS_NAME::getClassId() const \
{ \
    return BEACH_PACKET._classId; \
} \
atoms::size_type \
SUBCLASS_NAME::getPacketSize() const \
{\
    return sizeof(BEACH_PACKET); \
}\
notification::packet & \
SUBCLASS_NAME::getPacket() \
{ \
    return reinterpret_cast<notification::packet&>(BEACH_PACKET); \
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKETED_COMMAND
