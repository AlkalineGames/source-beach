#if !defined(BEACH_INVOCATION_COMMAND_CALL)
#define      BEACH_INVOCATION_COMMAND_CALL
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with no arguments and no return value
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 * 
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T>
class command_call
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)();

    command_call( const command_call & );
    command_call(
        T &                 in_object,
        type_method_pointer in_method );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    /// assignment operator disabled
    command_call & operator=( const command_call & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;

}; // end of class template command_call

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL
