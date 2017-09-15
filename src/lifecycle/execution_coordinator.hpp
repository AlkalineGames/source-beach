#if !defined(BEACH_LIFECYCLE_EXECUTION_COORDINATOR)
#define      BEACH_LIFECYCLE_EXECUTION_COORDINATOR
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       execution_coordinator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/ref_list.hpp>

namespace invocation
{
    class command;
};

namespace lifecycle
{
    using invocation::command;

//--------------------------------------

/// coordinator of executable commands.
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */
class execution_coordinator
{
public:

    BEACH_ALLOCATION_OPERATORS

    execution_coordinator();
    ~execution_coordinator();

    void submit_command( command & ); ///< takes ownership of command
    void execute_once(); ///< destroys commands after they are executed

private: 

    typedef collection::ref_list<command> commands;

    /// @name copy operations not implemented
    //@{
    execution_coordinator(              const execution_coordinator & );
    execution_coordinator & operator =( const execution_coordinator & );
    //@}

    commands _commands;

}; // end of class execution_coordinator

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_EXECUTION_COORDINATOR
