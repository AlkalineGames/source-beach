#if !defined(BEACH_INVOCATION_TEXT_COMMAND)
#define      BEACH_INVOCATION_TEXT_COMMAND
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       text_command.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace invocation
{
    using atoms::boolean;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// abstract superclass for text commands
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */     
class text_command
{
public:

    BEACH_ALLOCATION_OPERATORS

    virtual ~text_command();

    virtual const stringex & get_name() { return _name; }
    virtual const stringex & get_help() { return _help; }

    virtual boolean try_execute(
        const text *, stringex & out_result ) = 0;
        ///< returns false if text does not match this command

protected:

    text_command(
        const text * in_name,
        const text * in_help );

private:

    /// @name copy operations not implemented
    //@{
    text_command(               const text_command & );
    text_command & operator = ( const text_command & );
    //@}

    stringex _name;
    stringex _help;

}; // end of class text_command

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_TEXT_COMMAND
