#if !defined(BEACH_SERIALIZATION_READER_PACKETED)
#define      BEACH_SERIALIZATION_READER_PACKETED
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       reader_packeted.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/enumerations.hpp>
#include <serialization/reader.hpp>
#include <notification/channel_identifier.hpp>

namespace notification
{
    class channel;
    class packet;
};

namespace serialization
{
    using atoms::boolean;
    using atoms::integer;
    using atoms::integer32;
    using atoms::ownership;
    using atoms::real;
    using atoms::size_type;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;
    using atoms::whole16;
    using atoms::whole32;
    using atoms::whole64;
    using serialization::reader;
    using serialization::selector;
    using serialization::serializable;
    using serialization::serializable_source;
    using serialization::serializable_spec;
    using notification::channel;
    using notification::channel_identifier;
    using notification::packet;

//--------------------------------------

/// serializable reader from packets
/**
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */
class reader_packeted
    : public reader
{
public:

    BEACH_ALLOCATION_OPERATORS

    reader_packeted();
    reader_packeted( reader & ); ///< copies name associations

    virtual ~reader_packeted();

    /// @name Serializer operations overrides
    //@{
    virtual boolean read_boolean(       const selector *, const text * in_label, boolean &      out_value );
    virtual boolean read_enum(          const selector *, const text * in_label, const text * names[], whole in_name_count, integer & out_value );
    virtual boolean read_integer(       const selector *, const text * in_label, integer &      out_value );
    virtual boolean read_integer32(     const selector *, const text * in_label, integer32 &    out_value );
    virtual boolean read_ordered_real(  const selector *, const text * in_label, real           out_values[], whole in_count, whole in_position_count = 0  );
    virtual boolean read_ordered_whole( const selector *, const text * in_label, whole          out_values[], whole in_count );
    virtual boolean read_real(          const selector *, const text * in_label, real &         out_value,  whole in_position_count = 0  );
    virtual boolean read_string(        const selector *, const text * in_label, stringex &     out_string, whole in_position_count = 0   );
    virtual boolean read_text(          const selector *, const text * in_label, text           out_text[], size_type in_text_length );
    virtual boolean read_whole(         const selector *, const text * in_label, whole &        out_value );
    virtual boolean read_whole16(       const selector *, const text * in_label, whole16 &      out_value );
    virtual boolean read_whole32(       const selector *, const text * in_label, whole32 &      out_value );
    virtual boolean read_whole64(       const selector *, const text * in_label, whole64 &      out_value );
    virtual boolean read_object(        const selector *, const text * in_label, serializable * & out_object, whole in_position_count = 0  );
    virtual boolean read_root(          serializable * & out_root, serializable_source * in_source = 0 );
    virtual boolean read_root( context &, serializable * & out_root, serializable_source * in_source = 0 );
    //@}

    /// @name Serializer extensions overrides
    //@{
    virtual boolean read_all(   serializable & );
    virtual boolean read_spec(  const selector *, const text * in_label, serializable_spec & out_spec );
    virtual boolean read_state( serializable & out_object );
    virtual boolean read_value( const selector *, const text * in_label, serializable & out_value );
    virtual boolean has_field(  const selector *, const text * in_label );
    //@}

    void read_packet(
        ownership           in_packet_ownership,
        const packet &,
        channel *,
        channel_identifier  in_source,
        channel_identifier  in_destination );

private:

    boolean read_selector( const selector *, size_type in_data_size );

    whole           _packet_position;
    const packet *  _packet;

}; // end of class reader_packeted

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_READER_PACKETED
