#if !defined(BEACH_INVOCATION_COMMAND_CALL_ARGS_TWO_SETTER)
#define      BEACH_INVOCATION_COMMAND_CALL_ARGS_TWO_SETTER
//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_args_two_setter.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with two arguments and no return value, with additional argument setters
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 * 
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T, typename A1, typename A2>
class command_call_args_two_setter
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)( A1, A2 );

    command_call_args_two_setter( const command_call_args_two_setter & );
    command_call_args_two_setter(
        T &                 in_object,
        type_method_pointer in_method,
        A1                  in_arg1,
        A2                  in_arg2 );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    //@}

    A1                      get_arg1() const    { return _arg1; }
    void                    set_arg1( A1 arg1 ) { _arg1 = arg1; }

    A2                      get_arg2() const    { return _arg2; }
    void                    set_arg2( A2 arg2 ) { _arg2 = arg2; }

private:

    /// assignment operator disabled
    command_call_args_two_setter & operator=( const command_call_args_two_setter & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;
    A1                      _arg1;
    A2                      _arg2;

}; // end of class template command_call_args_two_setter

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_ARGUMENTS_TWO_SETTER
