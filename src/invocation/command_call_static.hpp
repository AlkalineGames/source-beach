#if !defined(BEACH_INVOCATION_COMMAND_CALL_STATIC)
#define      BEACH_INVOCATION_COMMAND_CALL_STATIC
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_static.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command for calling a static class method with no arguments and no return value
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 *  
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
class command_call_static
    : public command_abstract
{
public:

    typedef void (*type_method_pointer)();

    command_call_static( const command_call_static & );
    command_call_static( type_method_pointer );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    type_method_pointer     _method;

}; // end of class template command_call_static

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_STATIC
