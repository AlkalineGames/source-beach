#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_MANAGER)
#define      BEACH_SERIALIZATION_SERIALIZABLE_MANAGER
//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_manager.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <chain/context.hpp>
#include <atoms/primitives.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace serialization
{
    class reader;
    class serializable;
    class serializable_factory;
    class serializable_spec;
    using atoms::boolean;
    using chain::context;
    using atoms::text;
    using lifecycle::class_identifier;

//--------------------------------------

/// singleton manager for acquiring serializable objects
/**
 *  Each acquisition method iterates through the manager's 
 *  list of factories and delegates the operation to the
 *  corresponding operation on the factory. The iteration
 *  ends with the first factory encountered that returns
 *  a non-zero or true result.
 * 
 *  This class is coded as a public interface with an
 *  internal implementation subclass. Linkage is only
 *  required for code that calls the static methods.
 *
 *  @note   design patterns applied:
 *              - Encapsulated Context  [PLoP5]
 *              - Linkage Liberty       [WF]
 *              - Manager               [PLoP3]
 *              - Serializer            [PLoP3]
 *              - Singleton             [GoF]
 */      
class serializable_manager
{
public:

    BEACH_ALLOCATION_OPERATORS

    /// @name linkage required
    //@{
    static serializable_manager & acquire_singleton(); ///< via the object_catalog
    //@}
    static serializable_manager * find_singleton()
    {
        return lifecycle::object_catalog_utility<serializable_manager,serializable_manager>
                ::find_object( "serializable_manager", 0 );
    }
    static serializable_manager & get_singleton() ///< !!! assumes already acquired
    {
        return *find_singleton();
    }
    virtual ~serializable_manager() = 0;

    virtual void add_factory(       serializable_factory & ) = 0;
    virtual void remove_factory(    serializable_factory & ) = 0;

    /// @name operations delegated to factories
    //@{
    virtual serializable *  acquire(
        context &               in_context,
        serializable_spec &     inout_spec, ///< @note might resolve undefined values
        reader *                in_state_reader ) = 0;
    
    virtual serializable *  acquire(
        context &               in_context,
        reader &                in_spec_reader,
        reader *                in_state_reader,
        boolean                 in_do_log_error = true ) = 0;

    virtual void            ignore_class(
        class_identifier        in_class_id,
        const text *            in_class_name ) = 0; 

    virtual boolean         import_file(
        const text *            in_file_spec ) = 0;

    virtual boolean         read_file(
        const text *            in_file_spec,
        boolean                 in_do_change_to_file_directory  = false,
        boolean                 in_is_importing                 = false ) = 0;
    //@}

}; // end of class serializable_manager

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_MANAGER
