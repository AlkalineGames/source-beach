#if !defined(BEACH_TAXONOMY_TAXONOMY_MANAGER)
#define      BEACH_TAXONOMY_TAXONOMY_MANAGER
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       taxonomy_manager.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus, David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <lifecycle/object_catalog_utility.hpp>

namespace taxonomy
{
    class property;
    class property_range;
    class property_set;
    using atoms::real;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// interface to the taxonomy manager
/**
 *  This class is coded as a public interface with an
 *  internal implementation subclass. Linkage is only
 *  required for code that calls the static methods.
 *
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List    [PLoP5]
 *              - Linkage Liberty                       [WF]
 *              - Manager                               [PLoP3]
 *              - Null Object                           [PLoP3]
 *              - Singleton                             [GoF]
 */      
class taxonomy_manager
{
friend class taxonomy_manager_imp;
public:

    /// @name linkage required
    //@{
    static taxonomy_manager & acquire_singleton(); ///< via the object_catalog
    //@}
    static taxonomy_manager * find_singleton()
    {
        return lifecycle::object_catalog_utility<taxonomy_manager,taxonomy_manager>
                ::find_object( "taxonomy_manager", 0 );
    }
    virtual const stringex &        get_label_null()        const = 0;
    virtual const property &        get_property_null()     const = 0;
    virtual const property_set &    get_property_set_null() const = 0;

    virtual const stringex &        acquire_label(           const text * ) = 0;
    virtual const property_set &    acquire_property_set(    const text * in_name ) = 0;
    virtual       property_set &    acquire_property_set_nc( const text * in_name )
    {
        return const_cast<property_set&>(acquire_property_set( in_name ));
    }
    virtual const property_set *    find_property_set(       const text * in_name ) = 0;
    virtual       property_set *    find_property_set_nc(    const text * in_name )
    {
        return const_cast<property_set*>(find_property_set( in_name ));
    }
    virtual property_range &        create_property_range(
        const text *                    in_name,
        const real                      in_from = 0,
        const real                      in_to   = 0 ) = 0;

private:
    
    virtual ~taxonomy_manager() = 0;

}; // end of class taxonomy_manager

//--------------------------------------

} // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_TAXONOMY_MANAGER
