#if !defined(BEACH_SERIALIZATION_WRITER_FORWARDED)
#define      BEACH_SERIALIZATION_WRITER_FORWARDED
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       writer_forwarded.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <serialization/writer.hpp>

namespace notification
{
    class forwarder;
    class packet;
};

namespace serialization
{
    using atoms::size_type;
    using notification::forwarder;
    using notification::packet;

//--------------------------------------

/// serializer that writes state in binary format to a forwarder
/**
 *  @note   design patterns applied:
 *              - forwarder-Receiver    [Siemens]
 *              - Serializer            [PLoP3]
 */      
class writer_forwarded
    : public writer
{
public:

    BEACH_ALLOCATION_OPERATORS

    static writer * get_trace_writer()              { return __trace_writer; }
    static void     set_trace_writer( writer * w )  { __trace_writer = w;    }

    writer_forwarded( forwarder & );
    virtual ~writer_forwarded();

    const forwarder & get_forwarder_const() const   { return _forwarder; }
          forwarder & get_forwarder()               { return _forwarder; }

    /// @name Serializer operations overrides
    //@{
    virtual void write_boolean(         const selector *, const text * in_label, boolean );
    virtual void write_enum(            const selector *, const text * in_label, const text * names[], whole in_name_count, integer );
    virtual void write_integer(         const selector *, const text * in_label, integer );
    virtual void write_integer32(       const selector *, const text * in_label, integer32 );
    virtual void write_ordered_real(    const selector *, const text * in_label, const real[],  whole in_count );
    virtual void write_ordered_whole(   const selector *, const text * in_label, const whole[], whole in_count );
    virtual void write_real(            const selector *, const text * in_label, real );
    virtual void write_string(          const selector *, const text * in_label, const stringex & );
    virtual void write_text(            const selector *, const text * in_label, const text * in_text );
    virtual void write_whole(           const selector *, const text * in_label, whole );
    virtual void write_whole16(         const selector *, const text * in_label, whole16 );
    virtual void write_whole32(         const selector *, const text * in_label, whole32 );
    virtual void write_whole64(         const selector *, const text * in_label, whole64 );

    virtual void write_object(          const selector *, const selector * in_identity_selector, const text * in_label, serializable * ); // (variation: object can be null)
    virtual void write_root(            const selector *, serializable & );
    virtual void write_root( context &, const selector *, serializable & );
    //@}
    
    /// @name Serializer extensions overrides
    //@{
    virtual void write_spec(            const selector *, const text * in_label, const serializable_spec & );
    virtual void write_value(           const selector *, const selector * in_member_selector,   const text * in_label, serializable & in_value );
    //@}
    
protected: 

    void write_to_packet( context &, const selector *, serializable & );

    whole       _packet_position;
    packet *    _packet;

private:

    boolean write_selector( const selector *, size_type in_data_size );

    static writer * __trace_writer;

    forwarder & _forwarder;

}; // end of class writer_forwarded

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_WRITER_FORWARDED
