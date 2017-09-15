#if !defined(BEACH_INVOCATION_COMMAND_CALL_ARG_PASS)
#define      BEACH_INVOCATION_COMMAND_CALL_ARG_PASS
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_call_arg_pass.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_abstract.hpp>

namespace invocation
{

//--------------------------------------

/// command template for calling a method with one argument and no return value
/**
 *  A call command is used to indirectly and/or opaquely invoke operations on objects.
 *  This variation passes the argument during the call to execute( void * ),
 *  instead of at object construction.
 *
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
template <class T>
class command_call_arg_pass
    : public command_abstract
{
public:

    typedef void (T::*type_method_pointer)( void * );

    command_call_arg_pass( const command_call_arg_pass & );
    command_call_arg_pass(
        T &                 in_object,
        type_method_pointer in_method );

    /// @name command required overrides
    //@{
    virtual command *       clone() const; ///< prototype method
    virtual void            execute();
    virtual void            execute( void * );
    //@}
    
private:

    /// assignment operator disabled
    command_call_arg_pass & operator=( const command_call_arg_pass & ) { return *this; }

    T &                     _object;
    type_method_pointer     _method;

}; // end of class template command_call_arg_pass

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_CALL_ARG_PASS
