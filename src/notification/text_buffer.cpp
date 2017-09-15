//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_buffer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/text_buffer.hpp> // this header

#include <notification/observable_list_of_string.hpp>
#include <notification/observable_string.hpp>

namespace notification
{

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text name_class_this[] = "text_buffer";

//--------------------------------------
//  public methods
//--------------------------------------

text_buffer::text_buffer(
    const text_buffer_creation_parameters & in_parms )
  :
    _client_list_of_string( in_parms._in_list_of_string ),
    _client_string(         in_parms._in_text_editable ),
    _internal_string(       0 ),
    _current_string(        0 ),
    _edit_boundary(         in_parms._in_edit_boundary )
{
    if (_client_list_of_string != 0)
        _client_list_of_string->attach_observer( *this );
    else { // single line uses our own internal string
        _internal_string = new observable_string;
        _current_string = _internal_string;
        if (_client_string != 0) {
            _client_string->attach_observer( *this );
            _current_string->set_value( _client_string->get_value_ref() );
        } else
            _current_string->set_value( in_parms._in_text_constant );
    }
}

//--------------------------------------

// virtual
text_buffer::~text_buffer()
{
    if (_client_list_of_string != 0)
        _client_list_of_string->detach_observer( *this );
    else if (_client_string != 0)
        _client_string->detach_observer( *this );
    delete _internal_string;
}

//--------------------------------------

whole 
text_buffer::get_line_count()
{
    if (_client_list_of_string != 0)
        return _client_list_of_string->get_list_const().size();
    else if (_current_string != 0)
        return 1;
    return 0;
}

//--------------------------------------

const stringex *
text_buffer::get_string_for_line(
    whole in_line_number )
{
    if (in_line_number == 0)
        return 0;
    whole index = in_line_number - 1;
    if (_client_list_of_string != 0) {
        if ( index < _client_list_of_string->get_list_const().size() )
            return &(_client_list_of_string->get_list_const()[index]);
    }
    else if ((_current_string != 0) && (index == 0))
        return &(_current_string->get_value_ref());
    return 0;
}

//--------------------------------------

void
text_buffer::commit()
{
    if ((_client_string != 0) && (_internal_string != 0))
        _client_string->set_value( _internal_string->get_value_ref() );
}

//--------------------------------------

void
text_buffer::rollback()
{
    if ((_internal_string != 0) && (_client_string != 0))
        _internal_string->set_value( _client_string->get_value_ref() );
}

//--------------------------------------

// virtual
stringex
text_buffer::make_name_observer() const
{
    return name_class_this;
}

//--------------------------------------

// virtual
void
text_buffer::update_observer(
    const observable &  in_observable,
    const void *        in_affected_object,
    observer_flags      in_flags )
{
    if (&in_observable == _client_list_of_string) {
        if (in_flags & observable_list_of_string::observe_element_added)
            notify_observers( observe_line_appended );
    }
    else if (&in_observable == _client_string) {
        if (in_flags & observable_string::observe_value_changed) {
            if (_current_string != 0)
                _current_string->set_value(
                    _client_string->get_value_ref() );
            notify_observers( observe_current_string_changed );
        }
    }
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
