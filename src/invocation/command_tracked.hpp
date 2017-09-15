#if !defined(BEACH_INVOCATION_COMMAND_TRACKED)
#define      BEACH_INVOCATION_COMMAND_TRACKED
//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_tracked.hpp
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
    using atoms::whole;

//--------------------------------------

/// interface to a dynamic command tracked by source file and line
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */      
class command_tracked
{
public:

    BEACH_ALLOCATION_OPERATORS

    virtual                ~command_tracked()       = 0;
    virtual void            execute()               = 0;
    virtual const text *    get_name()        const = 0;
    virtual const text *    get_file_name()   const = 0;
    virtual whole           get_line_number() const = 0;
    virtual boolean         immediately()     const = 0;
    virtual boolean         supersedes()      const = 0;
    virtual stringex        make_signature()  const = 0;
};

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_TRACKED
