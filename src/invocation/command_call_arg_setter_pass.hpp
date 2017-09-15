#if !defined(BEACH_INVOCATION_COMMAND_CALL_ARG_SETTER_PASS)
#define      BEACH_INVOCATION_COMMAND_CALL_ARG_SETTER_PASS
//----------------------------------------------------------
//  Copyright 2007-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_arg_setter_pass.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with one argument and no return value, with additional argument setter and option to pass argument
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 * 
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T, class A>
class command_call_arg_setter_pass
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)( A, void * );

    command_call_arg_setter_pass( const command_call_arg_setter_pass & );
    command_call_arg_setter_pass(
        T &                 in_object,
        type_method_pointer in_method,
        A                   in_arg );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    virtual void            execute( void * );
    //@}

    A                       get_arg()           { return _arg; }
    void                    set_arg( A arg )    { _arg = arg; }

private:

    /// assignment operator disabled
    command_call_arg_setter_pass & operator=( const command_call_arg_setter_pass & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;
    A                       _arg;

}; // end of class template command_call_arg_setter_pass

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_ARG_SETTER_PASS
