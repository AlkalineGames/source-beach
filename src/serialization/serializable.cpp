//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serializable.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <lifecycle/logger.hpp>

namespace serialization
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text text_name_null_selector[]
    = "beach::serialization::serializable::null_selector";

static selector * null_selector_cached = 0;
        
//--------------------------------------
//  public methods
//--------------------------------------

// virtual
const selector & 
serializable::get_selector_all()
{
    return lifecycle::object_catalog_utility<selector,selector>
            ::acquire_object( text_name_null_selector, &null_selector_cached );
}

//--------------------------------------

// virtual
void
serializable::populate_spec(
    serializable_spec & ) const
{
    // do nothing, intended for override
}
    
//--------------------------------------

// virtual
boolean
serializable::read_from(
    reader & in_reader )
{
    context ctx;
    return read_from( ctx, in_reader );
}

//--------------------------------------

// virtual
void
serializable::write_to(
    writer &            in_writer,
    const selector *    in_selector )
{
    logger::get_singleton().log_error(
        "serializable", "write_to(...)",
        "obsolete method; replace with write_to( context &, ... )" );
}
    
//--------------------------------------

// virtual
boolean
serializable::read_from(
    context &,
    reader & in_reader )
{
    return read_from( in_reader );
}

//--------------------------------------

// virtual
void
serializable::write_to(
    context &,
    writer &            in_writer,
    const selector *    in_selector )
{
    write_to( in_writer, in_selector );
}
    
//--------------------------------------
//  protected methods
//--------------------------------------

serializable::serializable()
  :
    _source( 0 )
{}

//--------------------------------------

// virtual
serializable::~serializable()
{}
     
//--------------------------------------

}; // end of namespace serialization

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<serialization::selector>;

//----------------------------------------------------------
// (end of file)
