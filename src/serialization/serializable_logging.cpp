//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_logging.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <serialization/serializable_logging.hpp> // this header

#include <serialization/selector.hpp>
#include <lifecycle/logger.hpp>

#include <iomanip>

namespace serialization
{
    using namespace atoms;
    using lifecycle::logger;

//--------------------------------------
//  public methods
//--------------------------------------

// static
void
serializable_logging::log_trace_element(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_type,
    const stringex &    in_value,
    size_type           in_buffer_position_after )
{
    stream_string_o sso;
    output_to_stream_selector_label_type(
        in_selector, in_label, in_type,
        in_buffer_position_after, 1, sso );                    
    sso << in_value;
    logger::get_singleton().log_trace(
        0, 0, sso.str().c_str() );
}

//--------------------------------------

// static
void
serializable_logging::output_to_stream_selector_label_type(
    const selector *    in_selector,
    const text *        in_label,
    const text *        in_type,
    size_type           in_buffer_position_after,
    whole               in_element_count,
    stream_string_o &   inout_sso )
{
    if ( in_buffer_position_after != 0 )
    {
        inout_sso << '['
                  << std::setw( 5 ) << in_buffer_position_after
                  << ']';
    }
    else
    {
        inout_sso << ".......";
    }
    inout_sso << " sel<";
    if ( in_selector == 0 )
    {
        inout_sso << "-----";
    }
    else 
    {
        inout_sso << std::setw( 5 ) << in_selector->get_value();
    }
    inout_sso << ">,";
    if ( in_type == 0 )
    {
        inout_sso << "?type?";
    }           
    else
    {
        inout_sso << in_type;
        if ( in_element_count > 1 )
        {
            inout_sso << '[' << in_element_count << ']';
        }
    }           
    inout_sso << '/';
    if ( in_label == 0 )
    {
        inout_sso << "(unlabeled)";
    }           
    else
    {
        inout_sso << in_label;
    }           
    inout_sso << "==";
    if ( in_element_count > 1 )
    {
        inout_sso << '(';
    }
}

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// (end of file)
