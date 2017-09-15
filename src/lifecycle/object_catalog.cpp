//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_catalog.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_catalog.hpp> // this header

#include <atoms/allocation.hpp>
#include <invocation/command.hpp>
#include <lifecycle/allocation_center.hpp>
#include <lifecycle/logger.hpp>
#include <expression/regular_expression.hpp>

namespace lifecycle
{
    using atoms::byte;
    using atoms::whole;
    using atoms::text;
    using expression::regular_expression;

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text this_class_name[]
    = "object_catalog";

static object_catalog * singleton = 0;

static byte object_catalog_placement[sizeof(object_catalog)];

//--------------------------------------
//  internal methods
//--------------------------------------

static 
void
log_trace_binding(
    object_catalog::binding &   in_binding,
    object_catalog::bindings &  in_bindings,
    const text *                in_method_name,
    const text *                in_message_prefix )
{
    logger & log = logger::get_singleton();
    if ( ! log.is_including( this_class_name ) ) 
    {
        return;
    }
    const stringex & name =
         in_bindings.find_const_iterator(
            &in_binding )->first;
    stringex logmsg( in_message_prefix );
    logmsg += " \"";
    logmsg += name;
    logmsg += '"'; 
    logger::get_singleton().log_trace(
        this_class_name, in_method_name, logmsg );
}

//--------------------------------------
//  public methods
//--------------------------------------

void
object_catalog::bind(
    const name &    in_name,
    object          in_object,
    command *       in_killer,
    object *        out_cached_pointer,
    stringex *      out_error_message )
{
    static const text this_method_name[]
        = "bind(...)";

    if ( _bindings.contains_key( in_name ) )
    {
        if ( out_error_message != 0 )
        {
            *out_error_message  = "!! ";
            *out_error_message += this_class_name;
            *out_error_message += "::";
            *out_error_message += this_method_name;
            *out_error_message += " FAILED; \"";
            *out_error_message += in_name;
            *out_error_message += "\" is already bound.";
        }
        return;
    }
    binding * b = new binding;
    _bindings.add( in_name, *b );
    init_binding( *b, in_name, in_object,
        in_killer, out_cached_pointer );
}

//--------------------------------------

void
object_catalog::rebind(
    const name &    in_name,
    object          in_object,
    command *       in_killer,
    object *        out_cached_pointer )
{
    binding * b = _bindings.find_ref( in_name );
    if ( b != 0 )
    {
        clear_binding( *b );
        _bindings_sequence.erase_first( *b ); // move to last
    }
    else
    {
        b = new binding;
        _bindings.add( in_name, *b );
    }
    init_binding( *b, in_name, in_object,
        in_killer, out_cached_pointer );
}

//--------------------------------------

void
object_catalog::unbind(
    const name &    in_name,
    boolean         in_is_regex )
{
    regular_expression regex( in_name );

    // @@@ refactor into a generic reverse regex iterator
    // search in reverse order
    for ( bindings_sequence::reverse_iterator
          i( _bindings_sequence.rbegin() ),
          iend( _bindings_sequence.rend() );
          i != iend; i++ )
    {
        binding & b = *i;
        boolean matches = in_is_regex
            ? regex.match( b._name )
            : (b._name == in_name);
        if ( matches )
        {
            clear_binding( b );
            _bindings_sequence.erase_first( b );
            _bindings.erase( b._name ); // $$$ double the lookup
            delete &b;
            if ( ! in_is_regex )
            {
                break; // finished search
            }
        }
    }
}

//--------------------------------------

object_catalog::object
object_catalog::resolve(
    const name &    in_name,
    object *        inout_cached_pointer )
{
    object obj = 0;
    binding * bnd = _bindings.find_ref( in_name );
    if ( bnd != 0 )
    {
        obj = bnd->_object;
    }            
    if ( inout_cached_pointer != 0 )
    {
        *inout_cached_pointer = obj;
    }
    return obj;
}

//--------------------------------------
//  private methods
//--------------------------------------

// static
object_catalog &
object_catalog::create()
{
    return *(new object_catalog);
}

//--------------------------------------

// static
void
object_catalog::destroy(
    object_catalog & in_singleton )
{
    delete &in_singleton;
}

//--------------------------------------

object_catalog::object_catalog()
{}

//--------------------------------------

object_catalog::~object_catalog()
{
    // apply all killers 
    for ( bindings_sequence::reverse_iterator
          i( _bindings_sequence.rbegin() ),
          iend( _bindings_sequence.rend() );
          i != iend; i++ )
    {
        binding & b = *i;
        clear_binding( b );
        _bindings.erase_first( b ); // $$$ double the lookup
        delete &b;
    }
}

//--------------------------------------

void
object_catalog::clear_binding(
    binding & in_binding )
{
    static const text this_method_name[]
        = "clear_binding(...)";

#if 0 // @@@ THIS CAN CAUSE CRASHES IF THE CACHED POINTER
      // @@@ IS IN A PLUGIN THAT HAS BEEN UNLOADED
    if ( in_binding._cached_pointer != 0 )
    {
        *(in_binding._cached_pointer) = 0;
    }
#endif
    if ( in_binding._killer == 0 )
    {
        log_trace_binding(
            in_binding, _bindings,
            this_method_name, "removing" ); 
    }
    else
    {
        log_trace_binding(
            in_binding, _bindings,
            this_method_name, "deleting" ); 

        in_binding._killer->execute();
        delete in_binding._killer;
    }
}

//--------------------------------------

void
object_catalog::init_binding(
    binding &       in_binding,
    const name &    in_name,
    object          in_object,
    command *       in_killer,
    object *        out_cached_pointer )
{
    static const text this_method_name[]
        = "init_binding(...)";

    in_binding._name            = in_name;
    in_binding._object          = in_object;
    in_binding._killer          = in_killer;
    in_binding._cached_pointer  = out_cached_pointer;
    if ( out_cached_pointer != 0 )
    {
        *out_cached_pointer = in_object;
    }
    _bindings_sequence.push_back( in_binding );

    log_trace_binding(
        in_binding, _bindings,
        this_method_name, "adding" ); 
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  public C API
//--------------------------------------

extern "C" {

  void beach_lifecycle_object_catalog_bind(
          const char* in_name,
          void*       in_object) {
      lifecycle::object_catalog::get_singleton()
          .bind(atoms::stringex(in_name), in_object);      
  }

}; // end of extern "C"

//----------------------------------------------------------
// (end of file)
