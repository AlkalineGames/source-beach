#if !defined(BEACH_SERIALIZATION_CONFIG_FILE)
#define      BEACH_SERIALIZATION_CONFIG_FILE

//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       config_file.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

//--------------------------------------

namespace serialization
{
    using atoms::boolean;
    using atoms::integer;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// configuration text file
/**
 *  A config file is a simple text file containing named 
 *  properties expressed as name/value pairs that can be
 *  organized into separate sections. [cat]
 *
 *  If a default value is given in a 'get' operation and the entry
 *  does not exist in the configuration file, then the entry will be
 *  created.  If no default is given, the entry will not be created,
 *  the get_text function will return an empty string, and the 
 *  get_number function will return a zero. [swb]
 */
class config_file
{
public:

    class config_item_list;

	config_file( const text * in_file_name );
	~config_file();

    const stringex & get_file_name() { return _file_name; }

    //@{
	boolean  find_text(  const text * section, const text * key, stringex & out_value ) const;
	stringex get_text(   const text * section, const text * key, const text * default_value = 0 ) const;
	void     set_text(   const text * section, const text * key, const text * value );
	integer  get_number( const text * section, const text * key, integer default_value = -1 ) const;
	void     set_number( const text * section, const text * key, integer value );
    //@}
    
    stringex to_string() const;

    void write_file();
    void load_file();

private:

	stringex            _file_name;
    config_item_list *  _list;
};

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: config_file.hpp,v $
// Revision 1.6  2005/08/30 04:41:21  cat
// renamed sanddune to beach
//
// Revision 1.5  2005/08/23 18:50:10  cat
// added find_text(...)
//
// Revision 1.4  2004/07/10 21:04:06  cat
// renamed from ConfigFile to config_file
//
// Revision 1.3  2003/08/30 15:26:27  swb
// switched to the STL map, fixed a memory leak, renamed the class and members.
//
// Revision 1.2  2003/06/01 16:18:04  swb
// provide optional initial values
//
// Revision 1.1.1.1  2002/07/14 20:16:49  cat
// first import
//----------------------------------------------------------

#endif // BEACH_SERIALIZATION_CONFIG_FILE
