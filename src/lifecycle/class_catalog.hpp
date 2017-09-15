#if !defined(BEACH_LIFECYCLE_CLASS_CATALOG)
#define      BEACH_LIFECYCLE_CLASS_CATALOG
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_catalog.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/class_info.hpp>
#include <lifecycle/lifecycle_manager.hpp>
#include <lifecycle/object_identifier.hpp>
#include <collection/ref_list.hpp>

namespace lifecycle
{
    using atoms::boolean;
    using atoms::stringex;
    using atoms::text;
        
//--------------------------------------

// the catalog of registered C++ classes/types
/**
 *  The class catalog is a local process singleton that 
 *  maintains a collection of class information entries.
 *  All classes requiring dynamic interrogation should
 *  be registered with this catalog. This enables class
 *  identifiers to be passed around between objects
 *  dynamically with very little storage overhead.
 *  Along with supporting the registration of fixed class
 *  identifier values, the catalog will also generate new
 *  class identifier values from an incremental counter.
 *
 *  !!! class id values between 0 and 255 are reserved
 *      and so must not be registered by client code.
 *
 *  !!! If class identifiers are passed inter-process,
 *      each local process must register their classes
 *      with either EXACTLY THE SAME SPECIFIED VALUES or
 *      in EXACTLY THE SAME EXECUTION ORDER; otherwise 
 *      the class id values will NOT correspond to the
 *      same class names.
 * 
 *  @note   design patterns applied:
 *              - Mediator      [GoF]
 *              - Taxonomy    [POSA1]
 *              - Singleton     [GoF]
 */
class class_catalog
{
friend class lifecycle_manager;
public:

    typedef class_identifier class_identity; ///< @deprecated

    BEACH_ALLOCATION_OPERATORS

    static class_catalog & get_singleton()
    {
        return lifecycle_manager::acquire_singleton()
            .get_class_catalog();
    }
	const class_info *  find_class_by_id(   class_identifier );
	const class_info *  find_class_by_name( const text * in_class_name );
    const stringex &    find_class_name(    class_identifier ); ///< returns empty string if class id not registered

    /**
     *  Intended for the initial registration of a unique
     *  class. However, if another (or the same) class is
     *  already registered with the specified id value,
     *  its current information will be overwritten by 
     *  the parameters provided.
     */
    const class_info &  register_class(
        class_identifier    in_class_id,
        const text *        in_class_name,
        object_identifier   in_last_object_id );

    /**
     *  Either finds an existing registered class or creates
     *  a new entry with the specified id and optional name
     *  (unless in_can_fail == true)
     */
    const class_info *  resolve_class_by_id_or_name(
        class_identifier    in_class_id,
        const text *        in_class_name           = 0,
		boolean             in_can_fail             = false,
        class_identifier *  inout_static_class_id   = 0 );
    /**
     *  Either finds an existing registered class or creates
     *  a new entry with a incrementally generated class id
     *  (unless in_can_fail == true)
     */
    const class_info *  resolve_class_by_name(
        const text *        in_class_name,         
		boolean             in_can_fail             = false,
        class_identifier *  inout_static_class_id   = 0 );
    /**
     *  Either finds an existing registered class or creates
     *  a new entry with a incrementally generated class id
     *  (unless in_can_fail == true)
     */
    class_identifier    resolve_class_id_by_name(
        const text *        in_class_name,
		boolean             in_can_fail = false );

    object_identifier   acquire_next_object_id( ///< returns 0 if class not registered
        class_identifier );

private: 

    typedef collection::ref_list<class_info> entries;

    /// @name only by lifecycle_manager
    //@{
    static class_catalog &  create();
    static void             destroy( class_catalog & );
    //@}
    
    class_catalog();
    ~class_catalog();

    /// @name copy operations not implemented
    //@{
    class_catalog(              const class_catalog & );
    class_catalog & operator =( const class_catalog & );
    //@}

    class_info & add_new_entry(
        class_identifier,
        const text *        in_name,
        object_identifier   in_last_object_id,
        class_identifier *  inout_static_class_id );

    entries             _entries;
    class_identifier    _last_generated_class_id;

}; // end of class class_catalog

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_CLASS_CATALOG
