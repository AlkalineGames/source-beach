//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_factory.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serializable_factory.hpp> // this header

//--------------------------------------

namespace serialization
{

//--------------------------------------
//  public methods
//--------------------------------------

// virtual
serializable_factory::~serializable_factory()
{}

//--------------------------------------

// virtual
serializable *
serializable_factory::acquire(
    context &           in_context,
    serializable_spec & inout_spec,
    reader *            in_state_reader )
{
    return 0;
}
    
//--------------------------------------

// virtual
serializable *
serializable_factory::acquire(
    context &           in_context,
    reader &            in_spec_reader,
    reader *            in_state_reader)
{
    return 0;
}

//--------------------------------------

// virtual
boolean
serializable_factory::read_file(
    const text *,
    boolean,
    boolean )
{
    return false;
}

//--------------------------------------
//  protected methods
//--------------------------------------

serializable_factory::serializable_factory()
{}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: serializable_factory.cpp,v $
// Revision 1.5  2009/06/18 02:17:17  cat
// deprecated methods removed
//
// Revision 1.4  2009/05/18 21:14:52  cat
// acquire(...): context overloads added
//
// Revision 1.3  2004/08/29 00:57:07  cat
// read_file(...): added is_importing parameter
//
// Revision 1.2  2004/07/10 21:31:45  cat
// renamed SerializableFactory to serializable_factory; extracted spec to separate file; refactored operations
//
// Revision 1.1.1.1  2002/07/14 20:16:50  cat
// first import
//----------------------------------------------------------

// (end of file)
