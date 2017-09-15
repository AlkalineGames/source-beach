#if !defined(BEACH_INVOCATION_COMMAND_CALL_ARGS_THREE)
#define      BEACH_INVOCATION_COMMAND_CALL_ARGS_THREE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_args_three.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with three arguments and no return value
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 * 
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T, class A1, class A2, class A3>
class command_call_args_three
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)( A1, A2, A3 );

    command_call_args_three( const command_call_args_three & );
    command_call_args_three(
        T &                 in_object,
        type_method_pointer in_method,
        A1                  in_arg1,
        A2                  in_arg2,
        A3                  in_arg3 );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    /// assignment operator disabled
    command_call_args_three & operator=( const command_call_args_three & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;
    A1                      _arg1;
    A2                      _arg2;
    A3                      _arg3;

}; // end of class template command_call_args_three

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_ARGS_THREE
