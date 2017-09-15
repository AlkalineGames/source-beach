#if !defined(BEACH_SERIALIZATION_TEXT_STREAM_WRITER)
#define      BEACH_SERIALIZATION_TEXT_STREAM_WRITER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_writer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stream_adapter_echo.hpp>
#include <serialization/writer.hpp>

namespace serialization
{
    using atoms::stream_adapter_echo;

//--------------------------------------

/// serializer that writes to a text stream
/**
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */      
class text_stream_writer
    : public writer
{
public:

    static stringex write_to_string(
        serializable &, const selector * );

    text_stream_writer( std::ostream & );
    text_stream_writer( stream_adapter_echo & ); // @@@ YUCK
    virtual ~text_stream_writer();

    const std::ostream & get_stream_const() const   { return _stream_adapter_echo.get_stream_real_const(); }
          std::ostream & get_stream()               { return _stream_adapter_echo.get_stream_real(); }

    const stream_adapter_echo & get_stream_adapter_echo_const() const { return _stream_adapter_echo; }
          stream_adapter_echo & get_stream_adapter_echo()             { return _stream_adapter_echo; }

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

    virtual void write_object(          const selector *, const selector * in_identity_selector, const text * in_label, serializable * ); ///< (variation: object can be null)
    virtual void write_root(            const selector *, serializable & );
    virtual void write_root( context &, const selector *, serializable & );
    //@}
    
    /// @name Serializer extensions overrides
    //@{
    virtual void write_spec(            const selector *, const text * in_label, const serializable_spec & );
    virtual void write_value(           const selector *, const selector * in_member_selector,   const text * in_label, serializable & in_value );
    virtual boolean write_newline(); ///< returns false if it does nothing, @@@ KIND OF A HACK UNTIL WE USE XML
    //@}
    
private:

    stream_adapter_echo _stream_adapter_echo;
    boolean             _needs_attribute_separator;
    boolean             _needs_root_spec_terminator;

};  // end of class text_stream_writer

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEXT_STREAM_WRITER
