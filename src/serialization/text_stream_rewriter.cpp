//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_rewriter.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_rewriter.hpp> // this header

#include <atoms/stringex.hpp>
#include <atoms/stream_string.hpp>
#include <lifecycle/logger.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>
#include <serialization/serializable.hpp>
#include <serialization/serializable_manager.hpp>
#include <serialization/text_stream_writer.hpp>

namespace serialization
{
    using namespace atoms;
    using atoms::stringex;
    using lifecycle::logger;
    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "serialization::text_stream_rewriter";

static const text text_regex_attribute_prefix[]
    = "[:,<^][ \t]*(";

static const text text_regex_attribute_suffix[]
    = "[ \t]*=[ \t]*[^,;]+)";

static const text text_regex_attribute_combined[] =
    "[:,<^][ \t]*([^= \t]+[ \t]*=[ \t]*[^,;]+)";

static const text text_regex_attribute_separate[] =
    "([^= \t]+)[ \t]*=[ \t]*(.+)";

static const text text_regex_attribute_rhs[] =
    "=[ \t]*(.+)";

//--------------------------------------
//  public methods
//--------------------------------------

text_stream_rewriter::text_stream_rewriter(
    std::istream &      in_source_stream,
    const stringex *    in_base_directory,
    const stringex *    in_update_file_spec )
  :
    text_stream_reader( in_source_stream,
                        in_base_directory,
                        in_update_file_spec )
{}

//--------------------------------------

text_stream_rewriter::text_stream_rewriter(
    std::istream &      in_source_stream,
    std::ostream &      in_update_stream,
    const stringex *    in_base_directory )
  :
    text_stream_reader( in_source_stream,
                        in_update_stream,
                        in_base_directory )
{}

//--------------------------------------

// virtual
text_stream_rewriter::~text_stream_rewriter()
{}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
text_stream_rewriter::parse_include(
    const SPString & in_include_string )
{
    // ignore includes, rewriting is not recursive
}

//--------------------------------------

// virtual
serializable *
text_stream_rewriter::parse_object(
    context &           in_context,
    const SPString &    in_spec_string,
    boolean             in_do_read_on_acquire,
    boolean *           out_do_bypass_update )
{
    static const text this_method_name[]
        = "parse_object(...)";

    serializable * ser =
        text_stream_reader::parse_object(
            in_context, in_spec_string,
            false ); // do NOT read on acquire
    if ( ser != 0 )
    {
        stream_string_o sso;
        text_stream_writer wtr( sso );
        context ctx;
        ser->write_to( ctx, wtr );
        stringex written_string( sso.str() );

        // replace all attributes in the current statement
        //  with those found in the written string
        SPString        parse_string;
        SPString        expression_string;
        SPStringList    current_parse_list;
        SPStringList    written_parse_list;
        while ( true )
        {
            // parse the written string to find an attribute
            written_parse_list.reset();
            parse_string = written_string;
            regular_expression regexattributecombined(
                text_regex_attribute_combined,
                regular_expression::nocase );
            parse_string.m( regexattributecombined, written_parse_list );
            if ( written_parse_list.count() < 2 )
            {
                break; // no more attributes
            }
            // erase the parsed attribute from the written string
            parse_string = written_parse_list[1];
            stringex::size_type attrpos =
                written_string.find( parse_string );
            if ( attrpos == stringex::npos )
            {
                break; // !!! should never happen since we found a match
            }
            written_string.erase( attrpos, parse_string.length() );

            // parse to separate the attribute name from its rhs
            written_parse_list.reset();
            regular_expression regexattributeseparate(
                text_regex_attribute_separate,
                regular_expression::nocase );
            parse_string.m( regexattributeseparate, written_parse_list );
            if ( written_parse_list.count() < 3 )
            {
                continue; // !!! this should never happen
            }
            // parse the current statement string to find the same attribute
            current_parse_list.reset();
            parse_string = _current_statement_string;
            expression_string  = text_regex_attribute_prefix;
            expression_string += written_parse_list[1];
            expression_string += text_regex_attribute_suffix;
            regular_expression exp( expression_string, regular_expression::nocase );
            parse_string.m( exp, current_parse_list );
            if ( current_parse_list.count() < 2 )
            {
                // attribute not found so add to end of statement
                continue;
            /*
                @@@ DISABLED UNTIL WE REALLY NEED IT
                @@@ OTHERWISE WE GET REDUNDANT name= ATTRIBUTES
                stringex::size_type pos =
                    _current_statement_string.find_last_of( ";" );
                if ( pos == stringex::npos )
                {
                    stringex msg(
                        "invalid statement does not end with a ';': " );
                    msg += _current_statement_string;
                    logger::acquire_default_instance().log_error(
                        this_class_name, this_method_name, msg );
                    continue;
                }
                _current_statement_string[pos] = ',';
                _current_statement_string += ' ';
                _current_statement_string += written_parse_list[1];
                _current_statement_string += '=';
                _current_statement_string += written_parse_list[2];
                _current_statement_string += ';';
            */
            }
            else // found attribute
            {
                // determine exact position in current statement
                stringex attrstr( current_parse_list[1] );
                attrstr.erase_trailing_whitespace();
                stringex::size_type attrpos =
                    _current_statement_string.find( attrstr );
                if ( attrpos == stringex::npos )
                {
                    continue; // !!! should never happen since we found a match
                }
                // determine offset of attribute rhs
                current_parse_list.reset();
                parse_string = attrstr.get_text();
                regular_expression regexattributerhs(
                    text_regex_attribute_rhs,
                    regular_expression::nocase );
                parse_string.m( regexattributerhs, current_parse_list );
                if ( current_parse_list.count() < 2 )
                {
                    continue; // !!! should never happen because of previous match
                }
                stringex::size_type offset =
                    attrstr.find( current_parse_list[1] );
                if ( offset == stringex::npos )
                {
                    continue; // !!! should never happen since we found a match
                }
                // compare written rhs with current rhs
                stringex written_rhs( written_parse_list[2] );
                written_rhs.erase_trailing_whitespace();
                stringex current_rhs( current_parse_list[1] );
                if ( current_rhs.compare( written_rhs ) == 0 )
                {
                    continue;
                }
                stringex::size_type pos = attrpos + offset;
                stringex::size_type len = current_rhs.get_size();
                _current_statement_string.replace(
                    pos, len, written_rhs );
            }
            _is_current_statement_altered = true;
        }
    }
    return ser;
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
