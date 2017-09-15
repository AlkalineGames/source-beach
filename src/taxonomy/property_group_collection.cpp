//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group_collection.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_group_collection.hpp> // this header

#include <atoms/stream_string.hpp>
#include <collection/pointer_vector.hpp>

#include <cstring>

namespace taxonomy
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

property_group_collection::property_group_collection(
    pointer_vector &        in_collection,
    const text *            in_property_name )
  :
    _collection(            in_collection ),
    _property_name(         in_property_name ),
    _property_name_count(   0 ),
    _property_names(        0 )
{}

//--------------------------------------

// virtual
property_group_collection::~property_group_collection()
{
    for ( whole i = 0; i < _property_name_count; i++ )
    {
        delete [] _property_names[i];
    }
    delete [] _property_names;
}

//--------------------------------------

// virtual
whole
property_group_collection::get_property_count() const
{
    return _collection.size();
}

//--------------------------------------

// virtual
const text **
property_group_collection::get_property_names() const
{
    whole currentsize = _collection.size();
    if ( _property_name_count < currentsize )
    {
        // $$$ ALLOCATE NEW NAMES AND NEW ARRAY OF POINTERS
        const text ** newnames = new const text *[currentsize];
        for ( whole i = 0; i < currentsize; i++ )
        {
            if ( i < _property_name_count )
            {
                newnames[i] = _property_names[i];
            }
            else
            {
                stream_string_o sso;
                sso << _property_name << '[' << i << ']' << std::flush;
                stringex str( sso.str() );
                whole strlen = str.get_size() + 1;
                text * newname = new text[strlen];
                std::strcpy( newname, str.get_text() );
                newnames[i] = newname;
            }
        }
        delete [] _property_names;
        _property_names = newnames;
        _property_name_count = currentsize;
    }
    return _property_names;
}

//--------------------------------------

// virtual
stringex
property_group_collection::get_property_value() const
{
    stream_string_o sso;
    sso << get_property_count() << " items" << std::flush;
    return sso.str();
}

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
// (end of file)
