#if !defined(BEACH_LIFECYCLE_INITIALIZATION_COORDINATOR)
#define      BEACH_LIFECYCLE_INITIALIZATION_COORDINATOR
//----------------------------------------------------------
//  Copyright 2003-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       initialization_coordinator.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <lifecycle/execution_coordinator.hpp>

namespace invocation
{
    class command;
};

namespace lifecycle
{
    using atoms::text;
    using invocation::command;

//--------------------------------------

/// global coordinator of intialization
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Singleton [GoF]
 */
class initialization_coordinator
{
public:

    class submitter
    {
    public:

        submitter( command & cmd )
        {
            initialization_coordinator::get_global_instance()
                .submit_command( cmd );
        }
    };

    BEACH_ALLOCATION_OPERATORS

    static const execution_coordinator & get_global_instance_const() { return get_global_instance(); }
    static       execution_coordinator & get_global_instance();

}; // end of class initialization_coordinator

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_INITIALIZATION_COORDINATOR
