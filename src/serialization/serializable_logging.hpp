#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_LOGGING)
#define      BEACH_SERIALIZATION_SERIALIZABLE_LOGGING
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_logging.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stream_string.hpp>

namespace atoms
{
    class stringex;
};

namespace serialization
{
    class selector;
    using atoms::size_type;
    using atoms::stream_string_o;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;

//--------------------------------------

/// serializable logging utilities

class serializable_logging
{
public:

    static void log_trace_element(
        const selector *    in_selector,
        const text *        in_label,
        const text *        in_type,
        const stringex &    in_value,
        size_type           in_buffer_position_after );

    static void output_to_stream_selector_label_type(
        const selector *    in_selector,
        const text *        in_label,
        const text *        in_type,
        size_type           in_buffer_position_after,
        whole               in_element_count,
        stream_string_o &   inout_sso );

}; // end of class selector

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_LOGGING
