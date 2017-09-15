#if !defined(BEACH_LIFECYCLE_OBJECT_CATALOG)
#define      BEACH_LIFECYCLE_OBJECT_CATALOG
//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_catalog.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <collection/ref_map_by_string.hpp>
#include <collection/ref_vector.hpp>
#include <lifecycle/lifecycle_manager.hpp>

namespace invocation
{
    class command;
};

namespace lifecycle
{
    class allocation_center;
    using atoms::boolean;
    using atoms::pointer;
    using atoms::stringex;
    using invocation::command;

//--------------------------------------

/// singleton catalog of registered objects
/**
 *  This is a lightweight equivalent of the CORBA Naming Service
 *  that provides similar functionality for a local process.
 *  It is called object_catalog instead of NamingContext. For
 *  simplicity, the name space is flat rather than hierarchical.
 *  Operation signatures match NamingContext where feasible.
 *
 *  Special notes regarding the Singleton:
 *
 *  In order to ensure that there is only one singleton for
 *  the object catalog across multiple components within a
 *  process, the following must be enforced:
 *
 *  1. The primary component (first non-automatic execution)
 *      should call get_singleton() causing an automatic
 *      creation of the singleton instance in the primary
 *      component's C++ static data area.
 *
 *  2. All secondary components should call set_singleton(...)
 *      with the address of the singleton instance passed
 *      explicitly from the primary component, before any of
 *      its code ever calls get_singleton().
 *
 *  This is necessary because separate components within a
 *  process (i.e. main program versus dynamic/shared libraries),
 *  each have their own copy of C++ static data.
 *
 *  Objects bound with killers are killed in the reverse order
 *  of being bound to help with the potential chain of
 *  dependencies. Re-binding moves the new object to the end
 *  (becoming the first to be killed). 
 *
 *  @note   Design patterns applied:
 *              - Mediator  [GoF]
 *              - Registry  [PEAA]
 *              - Singleton [GoF]
 */
class object_catalog
{
friend class lifecycle_manager;
public:

    typedef stringex name;
    typedef pointer object;
    struct binding
    {
        name        _name;
        object      _object;
        command *   _killer;              
            ///< optional: used to destroy object, command is also destroyed if used
        object *    _cached_pointer;   
            ///< optional: set and cleared by registration operations 

        BEACH_ALLOCATION_OPERATORS
    };
    typedef collection::ref_map_by_string<binding> bindings;

    BEACH_ALLOCATION_OPERATORS

    static object_catalog & get_singleton()
    {
        return lifecycle_manager::acquire_singleton()
            .get_object_catalog();
    }
    /// @name registration (same operations as CORBA NamingContext)
    //@{
    void bind(
        const name &,
        object,
        command *   in_killer           = 0,
        object *    out_cached_pointer  = 0,    ///< set if provided
        stringex *  out_error_message   = 0 );  ///< empty if successful

    void rebind(
        const name &,
        object,
        command *   in_killer           = 0,    ///< uses current killer if present
        object *    out_cached_pointer  = 0 );  ///< clears current cached pointer if present

    void unbind(
        const name &,
        boolean in_is_regex = false ); ///< unbinds every match

    object resolve(
        const name &    in_name,
        object *        out_cached_pointer = 0 ); ///< set if provided
        /**< @@@ UNLIKE THE BOUND CACHED POINTER, THIS WILL
             @@@ NOT GET CLEARED WHEN THE OBJECT IS UNBOUND */
    //@}

private: 

    typedef collection::ref_vector<binding> bindings_sequence;

    /// @name copy operations not implemented
    //@{
    object_catalog(              const object_catalog & );
    object_catalog & operator =( const object_catalog & );
    //@}

    /// @name only by lifecycle_manager
    //@{
    static object_catalog & create();
    static void             destroy( object_catalog & );
    //@}
    
    object_catalog();   ///< should only be called once per process for all components
    ~object_catalog();  ///< applies all killers

    void clear_binding( binding & );
    void init_binding(  binding &, const name &,
                        object, command * in_killer,
                        object * out_cached_pointer );

    bindings            _bindings;
    bindings_sequence   _bindings_sequence;

}; // end of class object_catalog

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_OBJECT_CATALOG
