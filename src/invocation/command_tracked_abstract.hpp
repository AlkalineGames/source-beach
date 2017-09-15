#if !defined(BEACH_INVOCATION_COMMAND_TRACKED_ABSTRACT)
#define      BEACH_INVOCATION_COMMAND_TRACKED_ABSTRACT
//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
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

#include <invocation/command_tracked.hpp>

namespace invocation
{

//--------------------------------------

/// abstract implementation of a dynamic command tracked by source file and line
/**
 *  @note   design patterns applied:
 *              - Command [GoF]
 */
class command_tracked_abstract
    : public command_tracked
{
public:

    command_tracked_abstract(
        const text *        in_name,
        const text *        in_file_name,
        whole               in_line_number,
        boolean             in_immediately );

    /// @name subset of required overrides
    //@{
    virtual const text *    get_name()          const;
    virtual const text *    get_file_name()     const;
    virtual whole           get_line_number()   const;
    virtual boolean         immediately()       const;
    virtual boolean         supersedes()        const; ///< returns false
    virtual stringex        make_signature()    const; ///< returns get_name()
    //@}

private:

    const text *            _name;
    const text *            _file_name;
    whole                   _line_number;
    boolean                 _immediately;

}; // end of class command_tracked_abstract

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_TRACKED_ABSTRACT
