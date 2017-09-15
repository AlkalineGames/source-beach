//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_eraser.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_eraser.hpp> // this interface

#include <serialization/serializable_spec.hpp>

namespace serialization
{

//--------------------------------------
//  public methods
//--------------------------------------

text_stream_eraser::text_stream_eraser(
    const serializable_spec &   in_erase_spec,
    std::istream &              in_source_stream,
    const stringex *            in_base_directory,
    const stringex *            in_update_file_spec )
  :
    text_stream_reader(         in_source_stream,
                                in_base_directory,
                                in_update_file_spec ),
    _erase_spec(                in_erase_spec ),
    _erased(                    false )
{}

//--------------------------------------

text_stream_eraser::text_stream_eraser(
    const serializable_spec &   in_erase_spec,
    std::istream &              in_source_stream,
    std::ostream &              in_update_stream,
    const stringex *            in_base_directory )
  :
    text_stream_reader(         in_source_stream,
                                in_update_stream,
                                in_base_directory ),
    _erase_spec(                in_erase_spec ),
    _erased(                    false )
{}

//--------------------------------------

// virtual
text_stream_eraser::~text_stream_eraser()
{}

//--------------------------------------

// virtual
boolean
text_stream_eraser::read_root(
    serializable * &        out_root,
    serializable_source *   in_source )
{
    text_stream_reader::read_root( out_root, in_source );
    return _erased;
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
text_stream_eraser::parse_include(
    const SPString & in_include_string )
{
    // ignore includes, erasing is not recursive
}

//--------------------------------------

// virtual
serializable *
text_stream_eraser::parse_object(
    context &           in_context,
    const SPString &    in_spec_string,
    boolean             in_do_read_on_acquire,
    boolean *           out_do_bypass_update )
{
    serializable_spec spec;
    if ( parse_spec( in_spec_string, spec ) )
    {
        if (   (spec._class_id  == _erase_spec._class_id )
            && (spec._object_id == _erase_spec._object_id) )
        {
            _erased = true;
            if ( out_do_bypass_update != 0 )
            {
                *out_do_bypass_update = true;
            }
        }
    }
    return 0;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
