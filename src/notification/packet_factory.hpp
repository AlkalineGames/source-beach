#if !defined(BEACH_NOTIFICATION_PACKET_FACTORY)
#define      BEACH_NOTIFICATION_PACKET_FACTORY
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_factory.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/string.hpp>
#include <collection/ref_list.hpp>
#include <notification/packet_header.hpp>

namespace invocation
{
    template <class T> class command_kill;
};

namespace lifecycle
{
    template <class abstract_class, class concrete_class>
        class object_catalog_utility;
};

namespace notification
{
    class packet;
    class packet_handler;
    using atoms::size_type;

//--------------------------------------

class packet_factory
{
friend class invocation::command_kill<packet_factory>;
friend class lifecycle::object_catalog_utility<packet_factory,packet_factory>;
public:

    BEACH_ALLOCATION_OPERATORS

    static packet_factory & acquire_singleton(); ///< via the object catalog

    packet & create(  const packet_header & );
    void     destroy( packet & );

    /// @name packet alteration (produces copies)
    //@{
    packet & clone(      const packet & );
    packet & compress(   const packet & );
    packet & decompress( const packet & );
    packet & decrypt(    const packet & );
    packet & encrypt(    const packet & );
    packet & resize(     const packet &, size_type in_new_data_size );
    //@}

    void             register_handler( packet_header::TypeId, packet_handler * );
    packet_handler * retrieve_handler( packet_header::TypeId );

private:

    struct handler_registration
    {
        packet_header::TypeId _typeId;
        packet_handler *      _handler;

        BEACH_ALLOCATION_OPERATORS
    };
    typedef collection::ref_list<handler_registration>
        handler_registrations;

    packet_factory();
    ~packet_factory();

    /// @name copy operations not implemented
    //@{
    packet_factory(              const packet_factory & );
    packet_factory & operator =( const packet_factory & );
    //@}

    handler_registrations _handler_registrations;

}; // end of class packet

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKET_FACTORY
