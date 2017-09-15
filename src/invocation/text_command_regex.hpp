#if !defined(BEACH_INVOCATION_TEXT_COMMAND_REGEX)
#define      BEACH_INVOCATION_TEXT_COMMAND_REGEX
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_command_regex.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/text_command.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

namespace invocation
{

    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------

/// abstract superclass for regular expression commands
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */
class text_command_regex
    : public text_command
{
public:

    virtual ~text_command_regex();

    virtual boolean try_execute( ///< text_command override
        const text *, stringex & out_result );
        /** returns false if text does not match this command
         *  !!! this implementation delegates to execute_parsed(...)
         *  !!! ONLY if the first piece of the expression matches */

protected:

    text_command_regex(
        const text *    in_name,
        const text *    in_help,
        const text *    in_regular_expression_text );

    text_command_regex(
        const text *    in_name,
        const text *    in_help,
        const regular_expression & );
        /** !!! this object hangs on to the regular_expression & for it's lifetime
         *  !!! because regular_expression doesn't have a good copy constructor */

    virtual void execute_parsed(
        const SPStringList &,
        stringex & out_result ) = 0;
        ///< intended for override, only called if first piece matches

private:

    /// @name copy operations not implemented
    //@{
    text_command_regex(               const text_command_regex & );
    text_command_regex & operator = ( const text_command_regex & );
    //@}

    const regular_expression *  _regular_expression;
    boolean                     _owns_expression;

}; // end of class text_command_regex

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_TEXT_COMMAND_REGEX
