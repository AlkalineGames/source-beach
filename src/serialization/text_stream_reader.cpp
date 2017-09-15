//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_stream_reader.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/text_stream_reader.hpp> // this header

#include <atoms/string.hpp>
#include <serialization/serializable.hpp>
#include <serialization/serializable_manager.hpp>
#include <serialization/serializable_source.hpp>
#include <serialization/serializable_spec.hpp>
#include <lifecycle/logger.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

#include <fstream>
#include <istream>
#include <strstream>

namespace serialization
{
    using namespace atoms;
    using lifecycle::logger;
    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "text_stream_reader";

static const text text_syntax_comment_single_line[]
    = "//";

static const text text_syntax_object_attributes_start
    = ':';

static const text text_syntax_embedded_attribute_start
    = '<';

static const text text_regex_attribute_pre[] =
    "[:<,][ \t]*";

static const text text_regex_attribute_post[] =
    "[ \t]*=[ \t]*([^,;]+)";

static const text text_regex_embedded_attribute[] =
    "[ \t]*=[ \t]*(<[^>]+)>";

static const text text_regex_attribute_text[] =
    "[ \t]*=[ \t]*\"([^\"]+)\"";

static const text text_regex_attribute_ordered_head[] =
    "[ \t]*=[ \t]*{[ \t]*([^/},]+)";

static const text text_regex_attribute_ordered_extra[] =
    "[ \t]*(/[^/},]+)?";

static const text text_regex_attribute_ordered_tail[] =
    "}";

static const text text_regex_include[] =
    "#include[ \t]*<(.+)>";

static const text text_regex_object[] =
    "[ \t]*([^:;]+)[ \t]*:[ \t]*([^;]+)[ \t]*;";

static const text text_regex_spec[] =
    "([^/]+)/?[ \t]*(.+)?";

static const text text_regex_id_name[] =
    "^[ \t]*([0-9]+)[ \t]*-?[ \t]*(.+)?";

static const text text_regex_quoted[] =
    "\"([^\"]+)\"";

static const text text_regex_unquoted[] =
    "([^\" \t]+)";

//--------------------------------------
//  public methods
//--------------------------------------

text_stream_reader::text_stream_reader(
    std::istream &      in_source_stream,
    const stringex *    in_base_directory,
    const stringex *    in_update_file_spec,
    boolean             in_is_importing )
  :
    reader( in_base_directory ),
    _manager( serializable_manager::acquire_singleton() ), // optimization
    _is_current_statement_altered(  false ),
    _update_stream(                 0 ),
    _is_importing(                  in_is_importing ),
    _owns_update_stream(            false ),
    _source_stream(                 in_source_stream ),
    _object_attributes(             new SPString )
{
    if ( in_update_file_spec != 0 )
    {
        _update_stream = new std::ofstream(
            in_update_file_spec->get_text(),
            std::ios_base::out | std::ios_base::binary );
        _owns_update_stream = true;
    }
}

//--------------------------------------

text_stream_reader::text_stream_reader(
    std::istream &      in_source_stream,
    std::ostream &      in_update_stream,
    const stringex *    in_base_directory,
    boolean             in_is_importing )
  :
    reader( in_base_directory ),
    _manager( serializable_manager::acquire_singleton() ), // optimization
    _is_current_statement_altered(  false ),
    _update_stream(                &in_update_stream ),
    _is_importing(                  in_is_importing ),
    _owns_update_stream(            false ),
    _source_stream(                 in_source_stream ),
    _object_attributes(             new SPString )
{}

//--------------------------------------

// virtual
text_stream_reader::~text_stream_reader()
{
    delete _object_attributes;
    if ( _owns_update_stream )
    {
        delete _update_stream;
    }
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_boolean(
    const selector *, // not used
    const text *    in_label,
    boolean &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        attribute.to_lower();
        if (   (attribute.compare( "true" ) == 0)
            || (attribute.compare( "t"    ) == 0)
            || (attribute.compare( "1"    ) == 0) )
        {
            out_value = true;
            return true;
        }
        if (   (attribute.compare( "false" ) == 0)
            || (attribute.compare( "f"     ) == 0)
            || (attribute.compare( "0"     ) == 0) )
        {
            out_value = false;
            return true;
        }
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_enum(
    const selector *,
    const text *    in_label,
    const text *    in_names[],
    whole           in_name_count,
    integer &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        // compare against names
        attribute.to_lower(); // !!! assumming names are lowercase
        for ( whole i = 0; i < in_name_count; i++ )
        {
            if ( in_names[i] != 0 )
            {
                if ( attribute.compare( in_names[i] ) == 0 )
                {
                    out_value = i;
                    return true;
                }
            }
        } 
        // assume numeric value
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_integer(
    const selector *, // not used
    const text *    in_label,
    integer &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_integer32(
    const selector *, // not used
    const text *    in_label,
    integer32 &     out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_ordered_real(
    const selector *, // not used
    const text *    in_label,
    real            in_values[],
    whole           in_count,
    whole           in_position_count )
{
    SPStringList valuelist;
    stringex syntax = text_regex_attribute_ordered_head;
    for ( whole i = 1; (i < in_count); i++ )
    {
        syntax += text_regex_attribute_ordered_extra;
    }
    syntax += text_regex_attribute_ordered_tail;
    parse_ordered_attribute(
        in_label, syntax, valuelist, in_position_count );
    whole parsecount = valuelist.count();

    if ( parsecount > 1 )
    {
        //logger::get_singleton().log_information(
        //  this_class_name, "read_ordered_real B",
        //  valuelist[0] );

        --parsecount;
        for ( whole i = 0; (i < in_count) && (i < parsecount); i++ )
        {
           // logger::get_singleton().log_information(
           //     this_class_name, "read_ordered_real C",
           //     valuelist[i+1] );

            char strip;
            std::istrstream valuestream( valuelist[i+1] );
            if ( i > 0 ) // remove leading separator
            {
                    valuestream >> strip;
            }
            valuestream >> in_values[i];
        }
    }
    return (parsecount == in_count);
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_ordered_whole(
    const selector *, // not used
    const text *    in_label,
    whole           in_values[],
    whole           in_count )
{
    SPStringList valuelist;
    stringex syntax = text_regex_attribute_ordered_head;
    whole i;
    for ( i = 1; (i < in_count); i++ )
    {
        syntax += text_regex_attribute_ordered_extra;
    }
    syntax += text_regex_attribute_ordered_tail;
    parse_ordered_attribute(
        in_label, syntax, valuelist );
    whole parse_count = valuelist.count() - 1;
    for ( i = 0; (i < in_count) && (i < parse_count); i++ )
    {
        char strip;
        std::istrstream valuestream( valuelist[i+1] );
        if ( i > 0 ) // remove leading separator
        {
            valuestream >> strip;
        }
        valuestream >> in_values[i];
    }
    return (parse_count == in_count);
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_real(
    const selector *, // not used
    const text *    in_label,
    real &          out_value,
    whole           in_position_count)
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute, in_position_count ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_string(
    const selector *, // not used
    const text *    in_label,
    stringex &      out_string,
    whole           in_position_count )
{
    return parse_attribute(
        in_label, text_regex_attribute_text, out_string, in_position_count );
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_text(
    const selector *, // not used
    const text *    in_label,
    text *          out_text,
    size_type       in_text_length )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_text, attribute ) )
    {
        strncpyex( out_text, attribute, in_text_length );
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_whole(
    const selector *, // not used
    const text *    in_label,
    whole &         out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_whole16(
    const selector *, // not used
    const text *    in_label,
    whole16 &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_whole32(
    const selector *, // not used
    const text *    in_label,
    whole32 &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_whole64(
    const selector *, // not used
    const text *    in_label,
    whole64 &       out_value )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        std::istrstream valuestream( attribute );
        valuestream >> out_value;
        return true;
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_object(
    const selector *, // not used
    const text *        in_label,
    serializable * &    out_object,
    whole               in_position_count )
{
    stringex attribute;
    // try embedded attribute list first
    if ( parse_attribute(
            in_label, text_regex_embedded_attribute,
            attribute, in_position_count ) )
    {
        // parse embedded attributes using normal reader
        SPString * origattr = _object_attributes; // @@@ GROSS
        SPString spattr( attribute );
        _object_attributes = &spattr;
        context ctx;
        out_object = _manager.acquire( ctx, *this, 0 );
        _object_attributes = origattr;
        return (out_object != 0);
    }
    if ( parse_attribute(
            in_label, text_regex_attribute_post,
            attribute, in_position_count ) )
    {
        context ctx;
        SPString spattr( attribute );
        out_object = parse_object( ctx, spattr,
            false ); // do NOT read on acquire
        return (out_object != 0);
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_root(
    serializable * &        out_root,
    serializable_source *   in_source )
{
    context ctx;
    return read_root( ctx, out_root, in_source );
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_root(
    context &               in_context,
    serializable * &        out_root,
    serializable_source *   in_source )
{
    static text this_method_name[]
        = "read_root(...)";

    out_root = 0;

    SPString       statementstring; // EXPRESSION class
    SPStringList   statementlist;   // ...ditto...
    while ( ! _source_stream.eof() )
    {
        // @@@ ONLY SUPPORTING ENTIRE STATEMENT ON ONE LINE FOR NOW
        _source_stream >> statementstring;
        if ( _source_stream.bad() )
        {
            logger::get_singleton().log_error(
                this_class_name, this_method_name,
                "input stream is corrupted" );
            return false;
        }
        if ( _source_stream.fail() )
        {
            break; // most likely end-of-file
        }
        _current_statement_string = statementstring;
        _is_current_statement_altered = false;

        // strip comments
        int pos = statementstring.index( text_syntax_comment_single_line );
        if ( pos >= 0 )
        {
            statementstring = statementstring.substr( 0, pos );
        }
        // handle include
        statementlist.reset();
        regular_expression regexinclude(
            text_regex_include, regular_expression::nocase );
        statementstring.m( regexinclude, statementlist );
        if ( statementlist.count() > 1 )
        {
            parse_include( statementlist[1] );
        }
        // handle object
        statementlist.reset();
        regular_expression regexobject(
            text_regex_object, regular_expression::nocase );
        statementstring.m( regexobject, statementlist );
        boolean do_bypass_update = false;
        if ( statementlist.count() > 2 )
        {
            *_object_attributes = text_syntax_object_attributes_start;
            *_object_attributes += statementlist[2];
            serializable * object = parse_object(
                in_context, statementlist[1],
                true, // do read on acquire
                &do_bypass_update );
            if ( object != 0 )
            {
                if (   (in_source != 0)
                    && (object->get_serializable_source() == 0) )
                {
                    object->set_serializable_source( in_source );
                }
                if ( out_root == 0 )
                {
                    out_root = object;
                }
            }
        }
        if ( (_update_stream != 0) && (! do_bypass_update) )
        {
            *_update_stream
                << _current_statement_string.get_text();
            _update_stream->put( '\n' ); // *nix end-of-line
            _update_stream->flush();
            if ( in_source != 0 )
            {
                in_source->add_dirty_flags(
                    serializable_source::dirty_source_copied );
                if ( _is_current_statement_altered )
                {
                    in_source->add_dirty_flags(
                        serializable_source::dirty_source_revised );
                }
            }
        }
    }
    return true;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_spec(
    const selector *,   // not used
    const text *        in_label,
    serializable_spec & out_spec )
{
    stringex attribute;
    if ( parse_attribute(
            in_label, text_regex_attribute_post, attribute ) )
    {
        SPString specspstring( attribute );
        return parse_spec( specspstring, out_spec );
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_state(
    serializable & in_object )
{
    SPString parsingspstring; // EXPRESSION class
    while ( _source_stream.good() && (! _source_stream.eof()) )
    {
        // ### ASSUME ENTIRE STATEMENT ON ONE LINE FOR NOW
        _source_stream >> parsingspstring;
        *_object_attributes = parsingspstring;
        in_object.read_from( *this );
    }
    return true;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_statement(
    serializable & in_object )
{
    SPString parsingspstring; // EXPRESSION class
    if ( _source_stream.good() && (! _source_stream.eof()) )
    {
        // ### ASSUME ENTIRE STATEMENT ON ONE LINE FOR NOW
        _source_stream >> parsingspstring;
        *_object_attributes = parsingspstring;
        return in_object.read_from( *this );
    }
    return false;
}

//--------------------------------------

// virtual
boolean
text_stream_reader::read_value(
    const selector *, // not used
    const text *    in_label,
    serializable &  out_value )
{
    stringex attribute;
    if ( ! parse_attribute(
            in_label, text_regex_embedded_attribute,
            attribute ) )
    {
        return false;
    }
    // parse embedded attributes using normal reader
    SPString * origattr = _object_attributes; // @@@ GROSS
    SPString spattr( attribute );
    _object_attributes = &spattr;
    context ctx;
    out_value.read_from( ctx, *this );
    _object_attributes = origattr;
    return true;
}

//--------------------------------------

// virtual
void
text_stream_reader::add_dependency(
    serializable & in_object )
{
    if ( ! _dependencies.contains( in_object ) )
    {
        _dependencies.add( in_object );
    }
}

//--------------------------------------

// virtual
boolean
text_stream_reader::has_field(
    const selector *, // not used
    const text * in_label )
{
    stringex attribute;
    return parse_attribute(
        in_label, text_regex_attribute_post, attribute,
        0, false ); // don't remove
}

//--------------------------------------

// @@@ SHOULD BE MADE INTO A GENERIC PROPERTIES
//  ... get_properties() const
// virtual
boolean
text_stream_reader::is_importing() const
{
    return _is_importing;
}

//--------------------------------------
//  protected methods
//--------------------------------------

// virtual
void
text_stream_reader::parse_include(
    const SPString & in_include_string )
{
    static text this_method_name[] = "parse_include(...)";

    stringex filespec( get_base_directory() );
    filespec += in_include_string;
    if ( ! _manager.read_file( filespec.get_text(),
            false, _is_importing ) ) // don't change to file directory
    {
        stringex msg( "failed to read included file: " );
        msg += in_include_string;
        logger::get_singleton().log_error(
            this_class_name, this_method_name, msg );
    }
}

//--------------------------------------

// virtual
serializable *
text_stream_reader::parse_object(
    context &           in_context,
    const SPString &    in_spec_string,
    boolean             in_do_read_on_acquire,
    boolean *           out_do_bypass_update )
{
    serializable * ser;
    serializable_spec spec;
    if ( parse_spec( in_spec_string, spec ) )
    {
        boolean lacked_class_id  = (spec._class_id  == 0);
        boolean lacked_object_id = (spec._object_id == 0);

        ser = _manager.acquire( in_context, spec,
            in_do_read_on_acquire ? this : 0 );
            // !!! may recurse to here if does read on acquire

        if (   (lacked_class_id  && (spec._class_id  != 0))
            || (lacked_object_id && (spec._object_id != 0)) )
        {
            // replace incomplete spec with fully resolved spec
            // @@@ HACK TO PREVENT REPLACING THE
            // @@@ SUBSTRING OF ANOTHER WORD
            // @@@ --REFACTOR WHEN WE USE A BETTER regex LIBRARY
            stringex::size_type pos = 0;
            do
            {
                pos = _current_statement_string.find(
                    in_spec_string, pos );
                if ( pos == stringex::npos )
                {
                    break;
                }
                if ( pos > 0 )
                {
                    char prevchar = _current_statement_string[pos-1];
                    if (   (prevchar == '_' )
                        || ((prevchar >= '0') && (prevchar <= '9'))
                        || ((prevchar >= 'A') && (prevchar <= 'Z'))
                        || ((prevchar >= 'a') && (prevchar <= 'z')) )
                    {
                        ++pos;
                        continue;
                    }
                    stringex::size_type endpos = pos + in_spec_string.length();
                    if ( endpos < _current_statement_string.get_size() )
                    {
                        char nextchar = _current_statement_string[endpos];
                        if (   (nextchar == '_' )
                            || ((nextchar >= '0') && (nextchar <= '9'))
                            || ((nextchar >= 'A') && (nextchar <= 'Z'))
                            || ((nextchar >= 'a') && (nextchar <= 'z')) )
                        {
                            ++pos;
                            continue;
                        }
                    }
                }
                stringex specstr( spec.to_string() );
                    _current_statement_string.replace(
                        pos, in_spec_string.length(), specstr );
                pos += specstr.length();
                _is_current_statement_altered = true;
            }
            while ( true );
        }
    }
    else
    {
        ser = 0;
    }
    return ser;
}

//--------------------------------------
//  private methods
//--------------------------------------

boolean
text_stream_reader::parse_spec(
    const SPString &    in_spec_string,
    serializable_spec & out_spec )
{
    static text this_method_name[] = "parse_spec(...)";

    out_spec._class_id  = 0;
    out_spec._object_id = 0;

    SPStringList speclist;
    regular_expression regexspec(
        text_regex_spec, regular_expression::nocase );
    const_cast<SPString&>(in_spec_string) // @@@ shouldn't need const_cast
        .m( regexspec, speclist );
    if ( speclist.count() < 2 ) // no match
    {
        stringex msg( "missing class/object specifier: '" );
        msg += in_spec_string;
        msg += "'";
        logger::get_singleton().log_error(
            this_class_name, this_method_name, msg );
        return false;
    }
    SPStringList cspeclist;
    SPString     cspecspstring( speclist[1] );
    regular_expression regexidname(
        text_regex_id_name, regular_expression::nocase );
    cspecspstring.m( regexidname, cspeclist );
    if ( cspeclist.count() > 1 ) // id found
    {
        std::istrstream valuestream( cspeclist[1] );
        valuestream >> out_spec._class_id;
        if ( cspeclist.count() > 2 ) // name also
        {
            cspecspstring = cspeclist[2]; // parse it below
        }
        else // no name
        {
            out_spec._class_name.erase();
        }
    }
    if ( cspeclist.count() != 2 ) // no id, or id & name
    {
        if ( ! parse_quoted_or_unquoted(
                cspecspstring, cspeclist ) ) // no name
        {
            stringex msg( "invalid class specifier: '" );
            msg += cspecspstring;
            msg += "'";
            logger::get_singleton().log_error(
                this_class_name, this_method_name, msg );
            out_spec._class_name.erase();
            out_spec._object_name.erase();
            return false;
        }
        out_spec._class_name = cspeclist[1];
    }
    if ( speclist.count() > 2 ) // has object part
    {
        SPString     ospecspstring( speclist[2] );
        SPStringList ospeclist;
        regular_expression regexidname(
            text_regex_id_name, regular_expression::nocase );
        ospecspstring.m( regexidname, ospeclist );
        if ( ospeclist.count() > 1 ) // id found
        {
            std::istrstream valuestream( ospeclist[1] );
            valuestream >> out_spec._object_id;
            if ( ospeclist.count() > 2 ) // name also
            {
                ospecspstring = ospeclist[2]; // parse it below
            }
            else // no name
            {
                out_spec._object_name.erase();
            }
        }
        if ( ospeclist.count() != 2 ) // no id, or id & name
        {
            if ( ! parse_quoted_or_unquoted(
                    ospecspstring, ospeclist ) ) // no name
            {
                stringex msg( "object specifier is invalid: '" );
                msg += ospecspstring;
                msg += "'";
                logger::get_singleton().log_error(
                    this_class_name, this_method_name, msg );
                out_spec._object_name.erase();
                return false;
            }
            out_spec._object_name = ospeclist[1];
        }
    }
    return true;
}

//--------------------------------------

boolean
text_stream_reader::parse_quoted_or_unquoted(
    const SPString &    in_string,
    SPStringList &      out_list )
{
    out_list.reset();
    regular_expression regexquoted(
        text_regex_quoted, regular_expression::nocase );
    const_cast<SPString&>(in_string) // @@@ shouldn't need const_cast
        .m( regexquoted, out_list );
    if ( out_list.count() < 2 ) // quoted not found
    {
        out_list.reset();
        regular_expression regexunquoted(
            text_regex_unquoted, regular_expression::nocase );
        const_cast<SPString&>(in_string) // @@@ shouldn't need const_cast
            .m( regexunquoted, out_list );
        if ( out_list.count() < 2 ) // nothing found
        {
            return false;
        }
    }
    return true;
}

//--------------------------------------

boolean
text_stream_reader::parse_attribute(
    const text *    in_label,
    const text *    in_post_syntax,
    stringex &      out_string,
    whole           in_position_count,
    boolean         in_do_remove )
{
    SPStringList parsedlist;
    stringex regexpstr( text_regex_attribute_pre );
    regexpstr += in_label;
    regexpstr += in_post_syntax;
    regular_expression regexp( regexpstr, regular_expression::nocase );
    _object_attributes->m( regexp, parsedlist );
    if ( parsedlist.count() < 2 )
    {
        return false;
    }
    out_string = parsedlist[1];
    if ( in_do_remove )
    {
        // $$$ SPString HAS NO ERASE METHOD
        stringex attributes( (const char *)*_object_attributes );
        stringex fullmatch(  (const char *)parsedlist[0] );
        if (   (fullmatch.at( 0 ) == text_syntax_object_attributes_start)
            || (fullmatch.at( 0 ) == text_syntax_embedded_attribute_start) )
        {
            // do not remove prefixes used for multiple attributes
            fullmatch.erase( 0, 1 );
        }                        
        attributes.find_erase( fullmatch );
        *_object_attributes = attributes.get_text();
    }
    return true;
}

//--------------------------------------

void
text_stream_reader::parse_ordered_attribute(
    const text *    in_label,
    const text *    in_syntax,
    SPStringList &  out_list,
    whole           in_position_count,
    boolean         in_do_remove )
{
    stringex regexpstr( text_regex_attribute_pre );
    regexpstr += in_label;
    regexpstr += in_syntax;
    regular_expression regexp( regexpstr, regular_expression::nocase );

    if ( in_position_count > 1 )
    {
        SPStringList splitparsedlist; // EXPRESSION

        // 1st step is to SPLIT the string
        stringex splitregexpstr( in_label );
        splitregexpstr += "[ \t]*=";
        splitparsedlist = _object_attributes->split( splitregexpstr );

        if ( splitparsedlist.count() < (1+in_position_count) )
        {
            return;
        }
        // UGLY, must add back in (example), {1/2/3} and make it in_label={1/2/3}
        stringex attribute( ": " );
        attribute += in_label;
        attribute += "=";
        attribute += splitparsedlist[in_position_count];
        SPString attributespstring( attribute );
        attributespstring.m( regexp, out_list );
    }
    else
    {
        _object_attributes->m( regexp, out_list );
    }
    if ( in_do_remove && (out_list.count() > 0) )
    {
        // $$$ SPString HAS NO ERASE METHOD
        stringex attributes( (const char *)*_object_attributes );
        stringex fullmatch(  (const char *)out_list[0] );
        if (   (fullmatch.at( 0 ) == text_syntax_object_attributes_start)
            || (fullmatch.at( 0 ) == text_syntax_embedded_attribute_start) )
        {
            // do not remove prefixes used for multiple attributes
            fullmatch.erase( 0, 1 );
        }                        
        attributes.find_erase( fullmatch );
        *_object_attributes = attributes.get_text();
    }
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
