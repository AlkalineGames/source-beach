#if !defined(BEACH_INVOCATION_COMMAND_ABSTRACT)
#define      BEACH_INVOCATION_COMMAND_ABSTRACT
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_abstract.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <invocation/command.hpp>

namespace invocation
{
    class command_arguments;

//--------------------------------------

/// abstract implementation for the command interface
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
class command_abstract
    : public command
{
public:

    BEACH_ALLOCATION_OPERATORS

    virtual ~command_abstract();

    /// prototype method override, returns 0 here
    virtual command *       clone() const;

    virtual void            execute() = 0;

    /// @name variation: argument based execution
    /** (this classes' implementation calls execute() without the args) */
    //@{
    virtual void            execute( void * );
    virtual void            execute( command_arguments & );
    //@}

    /// @name enhancements overrides
    //@{
    virtual const text *    get_name() const;
    virtual void            set_name( const text * );
    //@}

protected:

    command_abstract( const text * in_name = 0 );
    command_abstract( const command_abstract & );

    stringex                _name;
    mutable const text *    _name_text; ///< !!! debugging aid

}; // end of class command_abstract

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_ABSTRACT
