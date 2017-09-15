#if !defined(BEACH_SERIALIZATION_TEXT_STREAM_APPENDER)
#define      BEACH_SERIALIZATION_TEXT_STREAM_APPENDER
//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_appender.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_reader.hpp>
#include <serialization/serializable_spec.hpp>

namespace serialization
{

//--------------------------------------

/// serializer that appends (or replaces) an object in a text stream
/**
 *  @note   design patterns applied:
 *              - Serializer        [PLoP3]
 *              - Template Method   [GoF]
 */      
class text_stream_appender
    : public text_stream_reader
{
public:

    text_stream_appender(
        const selector *,
        serializable &      in_object,
        std::istream &      in_source_stream,
        const stringex *    in_base_directory   = 0,
        const stringex *    in_update_file_spec = 0 );

    text_stream_appender(
        const selector *,
        serializable &      in_object,
        std::istream &      in_source_stream,
        std::ostream &      in_update_stream,
        const stringex *    in_base_directory = 0 );

    virtual ~text_stream_appender();

    /// @name Serializer operations overrides
    virtual boolean read_root( context &, serializable * & out_root, serializable_source * in_source = 0 );
    //@}

protected:

    virtual void            parse_include(  ///< read_root(...) template method override
        const SPString &        in_include_string );

    virtual serializable *  parse_object(   ///< read_root(...) template method override
        context &               in_context,
        const SPString &        in_spec_string,
        boolean                 in_do_read_on_acquire,
        boolean *               out_do_bypass_update = 0 );

    const selector *    _selector;
    serializable &      _object;
    serializable_spec   _object_spec;
    boolean             _written;

private:

    void init_object_spec();
    void write_object();

};  // end of class text_stream_appender

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEXT_STREAM_APPENDER
