#if !defined(BEACH_SERIALIZATION_TEXT_STREAM_READER)
#define      BEACH_SERIALIZATION_TEXT_STREAM_READER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_reader.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <collection/ref_vector.hpp>
#include <serialization/reader.hpp>
#include <expression/splash.h>

#include <iostream>

namespace serialization
{
    class serializable_manager;
    class serializable_spec;
    using atoms::size_type;
    using atoms::stringex;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------

/// serializer that reads from a text stream
/**
 *  @note   design patterns applied:
 *              - Serializer        [PLoP3]
 *              - Template Method   [GoF]
 */
class text_stream_reader
    : public reader
{
public:

    typedef collection::ref_vector<serializable> serializables;

    text_stream_reader(
        std::istream &      in_source_stream,
        const stringex *    in_base_directory   = 0,
        const stringex *    in_update_file_spec = 0,
        boolean             in_is_importing     = false );

    text_stream_reader(
        std::istream &      in_source_stream,
        std::ostream &      in_update_stream,
        const stringex *    in_base_directory   = 0,
        boolean             in_is_importing     = false );

    virtual ~text_stream_reader(); ///< creates reader for dependencies if file specs provided

    /// @name Serializer operations overrides
    //@{
    virtual boolean read_boolean(       const selector *, const text * in_label, boolean &  out_value );
    virtual boolean read_enum(          const selector *, const text * in_label, const text * names[], whole in_name_count, integer & out_value );
    virtual boolean read_integer(       const selector *, const text * in_label, integer &  out_value );
    virtual boolean read_integer32(     const selector *, const text * in_label, integer32 & out_value );
    virtual boolean read_ordered_real(  const selector *, const text * in_label, real       out_values[], whole in_count,   whole in_position_count = 0  );
    virtual boolean read_ordered_whole( const selector *, const text * in_label, whole      out_values[], whole in_count );
    virtual boolean read_real(          const selector *, const text * in_label, real &     out_value,  whole in_position_count = 0 );
    virtual boolean read_string(        const selector *, const text * in_label, stringex & out_string, whole in_position_count = 0 );
    virtual boolean read_text(          const selector *, const text * in_label, text       out_text[], size_type in_text_length );
    virtual boolean read_whole(         const selector *, const text * in_label, whole &    out_value );
    virtual boolean read_whole16(       const selector *, const text * in_label, whole16 &  out_value );
    virtual boolean read_whole32(       const selector *, const text * in_label, whole32 &  out_value );
    virtual boolean read_whole64(       const selector *, const text * in_label, whole64 &  out_value );

    virtual boolean read_object(        const selector *, const text * in_label, serializable * & out_object, whole in_position_count = 0 );
    virtual boolean read_root(          serializable * & out_root, serializable_source * in_source = 0 );
    virtual boolean read_root( context &, serializable * & out_root, serializable_source * in_source = 0 );
    //@}

    /// @name Serializer extensions overrides
    //@{
    virtual boolean read_spec(          const selector *, const text * in_label, serializable_spec & out_spec );
    virtual boolean read_state(         serializable & out_object );
    virtual boolean read_statement(     serializable & out_object );
    virtual boolean read_value(         const selector *, const text * in_label, serializable & out_value );

    virtual void    add_dependency(     serializable & );
    virtual boolean has_field(          const selector *, const text * in_label );
    //@}

    // @@@ SHOULD BE MADE INTO A GENERIC PROPERTIES
    //  ... get_properties() const
    virtual boolean is_importing() const;

    serializables::wrapped_iterator get_dependencies() { return _dependencies; }

protected:

    virtual void            parse_include(  ///< read_root(...) template method
        const SPString &        in_include_string );

    virtual serializable *  parse_object(   ///< read_root(...) template method
        context &               in_context,
        const SPString &        in_spec_string,
        boolean                 in_do_read_on_acquire,
        boolean *               out_do_bypass_update = 0 );

    boolean                 parse_spec(
        const SPString &        in_spec_string,
        serializable_spec &     out_spec );

    serializable_manager &  _manager;
    stringex                _current_statement_string;
    boolean                 _is_current_statement_altered;
    std::ostream *          _update_stream;

private:

    boolean                 parse_quoted_or_unquoted(
        const SPString &        in_string,
        SPStringList &          out_list );

    boolean                 parse_attribute(
        const text *            in_label,
        const text *            in_syntax,
        stringex &              out_string,
        whole                   in_position_count   = 0,
        boolean                 in_do_remove        = true );

    void                    parse_ordered_attribute(
        const text *            in_label,
        const text *            in_syntax,
        SPStringList &          out_list,
        whole                   in_position_count   = 0,
        boolean                 in_do_remove        = true );

    boolean         _is_importing;
    boolean         _owns_update_stream;
    std::istream &  _source_stream;
    SPString *      _object_attributes;
    serializables   _dependencies;

};  // end of class text_stream_reader

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEXT_STREAM_READER
