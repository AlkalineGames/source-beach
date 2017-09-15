//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_appender.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_appender.hpp> // this header

#include <serialization/serializable.hpp>
#include <serialization/text_stream_writer.hpp>
#include <lifecycle/logger.hpp>

namespace serialization
{
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "text_stream_appender";

//--------------------------------------
//  public methods
//--------------------------------------

text_stream_appender::text_stream_appender(
    const selector *    in_selector,
    serializable &      in_object,
    std::istream &      in_source_stream,
    const stringex *    in_base_directory,
    const stringex *    in_update_file_spec )
  :
    text_stream_reader( in_source_stream,
                        in_base_directory,
                        in_update_file_spec ),
    _selector(          in_selector ),
    _object(            in_object ),
    _written(           false )
{
    init_object_spec();
}

//--------------------------------------

text_stream_appender::text_stream_appender(
    const selector *    in_selector,
    serializable &      in_object,
    std::istream &      in_source_stream,
    std::ostream &      in_update_stream,
    const stringex *    in_base_directory )
  :
    text_stream_reader( in_source_stream,
                        in_update_stream,
                        in_base_directory ),
    _selector(          in_selector ),
    _object(            in_object ),
    _written(           false )
{
    init_object_spec();
}

//--------------------------------------

// virtual
text_stream_appender::~text_stream_appender()
{}

//--------------------------------------

// virtual
boolean
text_stream_appender::read_root(
    context &               in_context,
    serializable * &        out_root,
    serializable_source *   in_source )
{
    static const text this_method_name[]
        = "read_root(...)";

    text_stream_reader::read_root( in_context, out_root, in_source );
    if ( ! _written )
    {
        logger & log = logger::get_singleton();
        if ( log.is_including( this_class_name ) )
        {
            stringex msg( "appending object spec: " );
            msg += _object_spec.to_string();
            log.log_trace( this_class_name,
                this_method_name, msg );
        }
        // ### THIS WILL APPEND BEYOND CVS LOG ENTRIES, ETC
        write_object();
    }
    return _written;
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
text_stream_appender::parse_include(
    const SPString & in_include_string )
{
    // ignore includes, appending is not recursive
}

//--------------------------------------

// virtual
serializable *
text_stream_appender::parse_object(
    context &           in_context,
    const SPString &    in_spec_string,
    boolean             in_do_read_on_acquire,
    boolean *           out_do_bypass_update )
{
    static const text this_method_name[]
        = "parse_object(...)";

    if (   ( _object_spec._class_id  == 0 )
        || ( _object_spec._object_id == 0 ) )
    {
        return 0;
    }
    serializable_spec spec;
    if ( parse_spec( in_spec_string, spec ) )
    {
        if (   (spec._class_id  == _object_spec._class_id )
            && (spec._object_id == _object_spec._object_id) )
        {
            logger & log = logger::get_singleton();
            if ( log.is_including( this_class_name ) )
            {
                stringex msg( "replacing object spec: " );
                msg += spec.to_string();
                log.log_trace( this_class_name,
                    this_method_name, msg );
            }
            write_object();
            if ( out_do_bypass_update != 0 )
            {
                *out_do_bypass_update = true;
            }
        }
    }
    return 0;
}

//--------------------------------------
//  private methods
//--------------------------------------

void
text_stream_appender::init_object_spec()
{
    static const text this_method_name[]
        = "init_object_spec()";

    _object.populate_spec( _object_spec );
    if (   ( _object_spec._class_id  == 0 )
        || ( _object_spec._object_id == 0 ) )
    {
        stringex msg( "invalid object spec: " );
        msg += _object_spec.to_string();
        logger::get_singleton().log_error(
            this_class_name, this_method_name, msg );
    }
}

//--------------------------------------

void
text_stream_appender::write_object()
{
    if ( _update_stream != 0 )
    {
        text_stream_writer tswriter( *_update_stream );
        tswriter.write_root( _selector, _object );
        _written = true;
    }
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
