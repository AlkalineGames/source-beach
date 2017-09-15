#if !defined(BEACH_NOTIFICATION_TEXT_BUFFER)
#define      BEACH_NOTIFICATION_TEXT_BUFFER
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_buffer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <notification/observable_imp.hpp>
#include <notification/observer.hpp>

namespace notification
{
    class observable_string;
    class observable_list_of_string;
    class text_buffer_creation_parameters;
    using atoms::boolean;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;

//--------------------------------------

/// a buffer of text for browsing and optionally editing
/**
 *  @note   design patterns applied:
 *              - Observer [GoF]
 */
class text_buffer
    : public virtual observable_imp,
      public observer
{
public:

    enum observer_flag ///< bitwise values can be combined
    { 
        observe_line_appended           = observable::next_observer_flag << 1,
        observe_current_string_changed  = observe_line_appended          << 1
    };
    text_buffer( const text_buffer_creation_parameters & );
    virtual ~text_buffer();

    boolean             is_multiline() const { return _client_list_of_string != 0; }
    whole               get_line_count();

    const stringex *    get_string_for_line(
        whole in_line_number ); ///< numbers start at 1

    const text *        get_text_for_line(
        whole in_line_number ) ///< numbers start at 1
    {
        const stringex * str = get_string_for_line( in_line_number );
        return str == 0 ? 0 : str->get_text(); 
    }

    observable_string * get_current_string()        { return _current_string; }
    const stringex &    get_edit_boundary() const   { return _edit_boundary; }

    void commit();
    void rollback();

    BEACH_NOTIFICATION_OBSERVER_OVERRIDES_REQUIRED

private:

    observable_list_of_string * _client_list_of_string;
    observable_string *         _client_string;
    observable_string *         _internal_string;
    observable_string *         _current_string;
    stringex                    _edit_boundary;
   
}; // end of class text_buffer

//--------------------------------------

class text_buffer_creation_parameters
{
public:

    observable_list_of_string * _in_list_of_string;    ///< one or...
    observable_string *         _in_text_editable;  ///<    ...the other
    const text *                _in_text_constant;  ///<    ...or the other
    const text *                _in_edit_boundary;

    text_buffer_creation_parameters(
        observable_list_of_string & in_list_of_string )
      :
        _in_list_of_string(        &in_list_of_string ),
        _in_text_editable(      0 ),
        _in_text_constant(      0 ),
        _in_edit_boundary(      0 )
    {}        
    text_buffer_creation_parameters(
        observable_string &     in_text_editable,
        const text *            in_edit_boundary = 0 )
      :                         
        _in_list_of_string(        0 ),
        _in_text_editable(      &in_text_editable ),
        _in_text_constant(      0 ),
        _in_edit_boundary(      in_edit_boundary )
    {}        
    text_buffer_creation_parameters(
        const text *            in_text_constant )
      :                         
        _in_list_of_string(        0 ),
        _in_text_editable(      0 ),
        _in_text_constant(      in_text_constant ),
        _in_edit_boundary(      0 )
    {}        
};

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_TEXT_BUFFER
