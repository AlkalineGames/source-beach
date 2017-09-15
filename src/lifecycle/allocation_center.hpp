#if !defined(BEACH_LIFECYCLE_ALLOCATION_CENTER)
#define      BEACH_LIFECYCLE_ALLOCATION_CENTER
//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       allocation_center.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/lifecycle_manager.hpp>

#include <new>

namespace lifecycle
{

//--------------------------------------

/// centralization for dynamic allocations
/**
 *  Provide the means for all dynamic allocations
 *  to occur through the same allocation facility.
 *
 *  This can resolve problems where dynamic allocations
 *  in shared libraries cannot be successfully de-allocated
 *  in the main executable, and vice versa. Using this ensures
 *  that all allocations will now be performed within the same
 *  linked code base. 
 *
 *  The first process component (main executable/shared library)
 *  that calls create() (lifecycle_manager) will be the linked code
 *  base used by this class' default internal implementation class.
 *
 *  An alternative to the default internal implementation
 *  can be installed by another implementation subclass
 *  calling the protected set_singleton method.
 * 
 *  This class is coded as a public interface with an
 *  internal implementation subclass. Linkage is only
 *  required for code that calls the static methods.
 *
 *  @note   design patterns applied:
 *              - Linkage Liberty   [WF]
 *              - Mediator          [GoF]
 *              - Singleton         [GoF]
 */      
class allocation_center
{
friend class lifecycle_manager;
public:

    static allocation_center & get_singleton()
    {
        return lifecycle_manager::acquire_singleton()
            .get_allocation_center();
    }
    virtual void *  allocate(
        std::size_t     in_size,
        const char *    in_file,
        int             in_line ) = 0;
    
    virtual void    deallocate(
        void *          in_pointer,
        const char *    in_file,
        int             in_line ) = 0;

private:

    /// @name only by lifecycle_manager
    //@{
    static allocation_center &  create();
    static void                 destroy( allocation_center & );
    //@}
    
}; // end of class allocation_center

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_ALLOCATION_CENTER
