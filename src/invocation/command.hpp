#if !defined(BEACH_INVOCATION_COMMAND)
#define      BEACH_INVOCATION_COMMAND
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>

/// Beach Invocation Framework
/**
 *	This is a framework of abstract superclasses and class
 *	templates for the indirect invocation of object methods.
 *	These mechanisms help promote a loose coupling between
 *	caller and called object/method that can be used for
 *	deferring the execution of methods during runtime,
 *	providing alternate execution paths that are determined
 *	by dynamic conditions or configuration, and/or reducing
 *	the static compile-time dependencies between classes.
 *	Most of these designs and implementations are based on
 *	the Command design pattern [Gang-of-Four].
 */
namespace invocation
{
    class command_arguments;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// interface to an executable command
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
class command
{
public:

    virtual ~command() = 0;

    virtual command *       clone() const = 0; ///< prototype method

    virtual void            execute() = 0;

    /// @name variation: argument based execution
    //@{
    virtual void            execute( void * ) = 0;
    virtual void            execute( command_arguments & ) = 0;
    //@}

    /// @name enhancements
    //@{
    virtual const text *    get_name() const = 0;
    virtual void            set_name( const text * ) = 0;
    //@}

}; // end of class command 

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND
