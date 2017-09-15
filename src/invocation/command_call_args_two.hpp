#if !defined(BEACH_INVOCATION_COMMAND_CALL_ARGS_TWO)
#define      BEACH_INVOCATION_COMMAND_CALL_ARGS_TWO
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_args_two.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with two arguments and no return value
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 * 
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T, class A1, class A2>
class command_call_args_two
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)( A1, A2 );

    command_call_args_two( const command_call_args_two & );
    command_call_args_two(
        T &                 in_object,
        type_method_pointer in_method,
        A1                  in_arg1,
        A2                  in_arg2 );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

private:

    /// assignment operator disabled
    command_call_args_two & operator=( const command_call_args_two & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;
    A1                      _arg1;
    A2                      _arg2;

}; // end of class template command_call_args_two

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_ARGS_TWO
