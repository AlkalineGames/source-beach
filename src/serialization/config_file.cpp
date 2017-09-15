//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       config_file.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <serialization/config_file.hpp> // this header

#include <atoms/allocation.hpp>
#include <atoms/stream_string.hpp>
#include <collection/ref_map_by_string.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

namespace serialization
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

typedef std::map<stringex,stringex>                 entry_map;
typedef collection::ref_map_by_string<entry_map>   section_map;

//--------------------------------------

/// internal implementation class

class config_file::config_item_list
{
public:

    BEACH_ALLOCATION_OPERATORS

    config_item_list();
    ~config_item_list();

    boolean get_entry(
        const stringex &    section,
        const stringex &    key,
        stringex &          value );

    void    put_entry(
        const stringex &    section,
        const stringex &    key,
        const stringex &    value );

    stringex to_string() const;

private:

    section_map _sections;
};

//--------------------------------------
//  internal methods
//--------------------------------------

config_file::config_item_list::config_item_list()
  :
    _sections( atoms::destroyer<entry_map>() )
{}

//--------------------------------------

config_file::config_item_list::~config_item_list()
{}

//--------------------------------------

bool
config_file::config_item_list::get_entry(
    const stringex &    in_section,
    const stringex &    in_key,
    stringex &          out_value )
{
    entry_map * entries = _sections.find_ref( in_section );
    if ( entries == 0 )
    {
        return false;
    }
    entry_map::const_iterator entiter( entries->find( in_key ) );
    if ( entiter == entries->end() )
    {
        return false;
    }
    out_value = entiter->second;
    return true;
}

//--------------------------------------

void
config_file::config_item_list::put_entry(
    const stringex &    in_section,
    const stringex &    in_key,
    const stringex &    in_value )
{
    entry_map * entries = _sections.find_ref( in_section );
    if ( entries == 0 )
    {
        entries = new BEACH_ALLOCATION entry_map;
        _sections.add( in_section, *entries );
    }
    // @@@ REPLACE LOGIC AS CODED IN pointer_map_by_string
    entry_map::iterator iter = entries->find( in_key );
    if ( iter != entries->end() )
    {
        entries->erase( iter );
    }
    entries->insert( entry_map::value_type( in_key, in_value ) );
}

//--------------------------------------

stringex
config_file::config_item_list::to_string() const
{
    stream_string_o sso;
    for ( section_map::const_iterator
          seciter(   _sections.begin() );
          seciter != _sections.end();
          seciter++ )
    {
        sso << "[" <<  seciter.get_key() << "]" << std::endl;
        const entry_map * entries = seciter.get_ptr();
        for ( entry_map::const_iterator
              entiter(   entries->begin() );
              entiter != entries->end();
              entiter++ )
        {
            sso << entiter->first << "="
                << entiter->second << std::endl; }
    }
    return sso.str();
}

//--------------------------------------
//  public methods
//--------------------------------------

config_file::config_file(
    const text * in_file_name )
  :
    _file_name( "" ),
    _list( 0 )
{
    _file_name = in_file_name;
    _list = new config_item_list;
    load_file();
}

//--------------------------------------

config_file::~config_file()
{
    delete _list;
}

//--------------------------------------

boolean
config_file::find_text(
    const text *    in_section,
    const text *    in_key,
    stringex &      out_value ) const
{
   return _list->get_entry( in_section, in_key, out_value );
}

//--------------------------------------

stringex
config_file::get_text(
    const text * section,
    const text * key,
    const text * default_value ) const
{
   stringex value;
   if ( ! _list->get_entry( section, key, value ) )
   {
       if ( default_value != 0 )
       {
           config_file * ncthis = const_cast<config_file *>(this);
           ncthis->set_text( section, key, default_value );
           value = default_value;
       }
       else
       {
           return "";
       }
   }
   return value;
}

//--------------------------------------

void
config_file::set_text(
    const text * section,
    const text * key,
    const text * value )
{
    _list->put_entry( section, key, value );
    write_file();
}

//--------------------------------------

integer
config_file::get_number(
    const text *    section,
    const text *    key,
    integer         default_value ) const
{
    stringex svalue;
    if ( !_list->get_entry( section, key, svalue ) )
    {
        if ( default_value != -1 )
        {
            config_file * ncthis = const_cast<config_file *>(this);
            ncthis->set_number( section, key, default_value );
            return default_value;
        }
        else
        {
            return 0;
        }
    }
    int value = atoi((const  char *)svalue);
    return value;
}

//--------------------------------------

void
config_file::set_number(
    const text *    section,
    const text *    key,
    integer         value )
{
    char buf[64];
    std::sprintf( buf, "%d", value );
    set_text( section, key, buf );
    _list->put_entry( section, key, buf );
}

//--------------------------------------

stringex
config_file::to_string() const
{
    return _list->to_string();
}

//--------------------------------------

void
config_file::write_file()
{
    std::ios_base::openmode mode = ( std::ios::out | std::ios::trunc );
    std::ofstream file( _file_name, mode );
    file << to_string() << std::flush;
    file.close();
}

//--------------------------------------

void
config_file::load_file()
{
    char buf[2048];
    std::ifstream file( _file_name );
    stringex section = "";
    while ( file.good() && (! file.eof()) )
    {
        file.getline( buf, sizeof(buf) );
        if ( buf[0] == 0 )
        {
            continue;
        }
        else if ( buf[0] == '[' )
        {
            // start section
            char * end = ::strchr( buf, ']' );
            if ( end == 0 )
            {
                continue;
            }
            int len = ( end - (&buf[1]) );
            if ( len < 1 )
            {
                continue;
            }
            section = stringex( &buf[1], len );
        }
        else
        {
            // found an entry
            char * p = ::strchr( buf, '=' );
            if ( p == 0 )
            {
                continue;
            }
            stringex key = stringex( buf, p-buf );
            stringex value = stringex( p+1 );
            _list->put_entry( section, key, value );
        }
    }
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
