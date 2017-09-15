//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_spec.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serializable_spec.hpp> // this header

#include <serialization/serializable_spec.hpp>
#include <lifecycle/class_catalog.hpp>

#include <sstream>

//--------------------------------------

namespace serialization
{
    using lifecycle::class_catalog;

//--------------------------------------
//  public methods
//--------------------------------------

stringex
serializable_spec::to_string() const
{
    std::stringstream ss;
    if ( (_class_id != 0) || _class_name.is_empty() )
    {
        ss << _class_id;
    }
    if ( ! _class_name.is_empty() )
    {
        if ( _class_id != 0 )
        {
            ss << '-';
        }
        ss << _class_name.get_text();
    }                
    if ( (_object_id != 0) || (! _object_name.is_empty()) )
    {
        ss << '/';
        if ( _object_id != 0 )
        {
            ss <<
#if defined(_MSC_VER) /// @@@ STUPID MSVC DOES NOT SUPPORT 64-BIT 
                atoms::whole32(_object_id);
#else
                _object_id;
#endif        
        }
        if ( ! _object_name.is_empty() )
        {
            if ( _object_id != 0 )
            {
                ss << '-';
            }
            ss << '"' << _object_name.get_text() << '"';
        }
    }
    ss << std::flush;
    return ss.str().c_str();
}

//--------------------------------------

stringex
serializable_spec::to_string_resolved()
{
    if (   (_class_id   == 0)
        && (_class_name != 0) )
    {
        class_catalog & catalog = class_catalog::get_singleton();
        _class_id = catalog.resolve_class_id_by_name(
            _class_name, true ); // can fail
    }
    return to_string();
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: serializable_spec.cpp,v $
// Revision 1.1  2004/07/10 21:47:04  cat
// extracted from serializable_factory and refactored into a single class
//
//----------------------------------------------------------

// (end of file)
