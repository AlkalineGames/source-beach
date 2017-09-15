#if !defined(BEACH_INVOCATION_TEXT_COMMAND_EXECUTER)
#define      BEACH_INVOCATION_TEXT_COMMAND_EXECUTER
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_command_executer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace invocation
{
    using atoms::boolean;
    using atoms::stringex;

//--------------------------------------

/// interface for an executer of text commands
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */     
class text_command_executer
{
public:

    /// return false if the command fails or is unknown 
    virtual boolean execute_text_command(
        const stringex &    in_text_command,
        stringex &          out_result_text ) = 0;

}; // end of class text_command_executer

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_TEXT_COMMAND_EXECUTER
