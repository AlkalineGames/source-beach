#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_FACTORY)
#define      BEACH_SERIALIZATION_SERIALIZABLE_FACTORY
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_factory.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <chain/context.hpp>
#include <atoms/primitives.hpp>

namespace serialization
{
    class reader;
    class serializable;
    class serializable_spec;
    using atoms::boolean;
    using chain::context;
    using atoms::text;

//--------------------------------------

/// abstract superclass for a serializable factory
/**
 *  This class is implemented as an abstract superclass
 *  rather than a pure interface so that subclasses do not
 *  have to override every operation. Factory methods of this
 *  superclass will return 0. 
 *
 *  @note   design patterns applied:
 *              - Abstract Factory      [GoF]
 *              - Encapsulated Context  [PLoP5]
 *              - Factory Method        [GoF]
 *              - Serializer            [PLoP3]
 */      
class serializable_factory
{
public:

    BEACH_ALLOCATION_OPERATORS

    virtual ~serializable_factory();

    /// @name factory method overrideables
    //@{
    /**
     * Overriders should only act on inout_spec._class_id
     * and ignore inout_spec._class_name because the
     * serializable_manager will attempt to resolve
     * inout_spec._class_name into its registered class id,
     * failing with an error and not calling this method
     * if it cannot be resolved.
     */
    virtual serializable *  acquire(
        context &               in_context,
        serializable_spec &     in_out_spec,
        reader *                in_state_reader );

    virtual serializable *  acquire(
        context &               in_context,
        reader &                in_spec_reader,
        reader *                in_state_reader );

    virtual boolean         read_file(
        const text *            in_file_spec,
        boolean                 in_do_change_to_file_directory  = false,
        boolean                 in_is_importing                 = false );
    //@}

protected:

    serializable_factory();
    
}; // end of class serializable_factory

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_FACTORY
