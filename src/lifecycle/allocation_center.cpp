//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       allocation_center.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/allocation_center.hpp> // this header

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <lifecycle/logger.hpp>

#include <sstream>

namespace lifecycle
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

/// internal implementation subclass

class allocation_center_imp
    : public allocation_center
{
public:

    allocation_center_imp();
    virtual ~allocation_center_imp();

    /// @name allocation operations
    //@{
    virtual void *  allocate(
        size_t          in_size,
        const char *    in_file,
        int             in_line );
    
    virtual void    deallocate(
        void *          in_pointer,
        const char *    in_file,
        int             in_line );
    //@}

}; // end of class allocation_center_imp

//--------------------------------------

static const text this_class_name[]
    = "allocation_center";

static allocation_center * singleton_cached = 0;
    
//--------------------------------------
//  internal public methods
//--------------------------------------

allocation_center_imp::allocation_center_imp()
{}

//--------------------------------------

// virtual
allocation_center_imp::~allocation_center_imp()
{}

//--------------------------------------

// virtual
void *
allocation_center_imp::allocate(
    size_t          in_size,
    const char *    in_file,
    int             in_line )
{
    static const text this_method_name[]
        = "new_single(...)";

// adjust DEBUG_NEW to use method parameters for file and line number
#if defined(DEBUG_NEW)
#define BEACH_NEW_REDEFINITION new
#define DEBUG_NEW __debug_new_recorder( in_file, in_line ) ->* new
#if defined(_DEBUG_NEW_REDEFINE_NEW)
#define new DEBUG_NEW
#endif
#endif

    void * pointer = new byte[in_size];

// disable DEBUG_NEW new redefinition
#if defined(DEBUG_NEW)
#undef new
#endif

#if 0
    // @@@ FIGURE OUT HOW TO DO THIS WITHOUT GOING THROUGH
    // @@@ INFINITE RECURSION logger -> lock_factory -> ... 
    logger & log = logger::acquire_default_instance();
//    if ( log.is_including( this_class_name ) ) 
    {
        std::ostringstream oss;
        oss << "@ " << std::hex << whole64(&pointer)
            << " for " << in_size
            << " bytes; " << in_file << ':' << in_line; 
        log.log_trace( this_class_name, this_method_name,
            oss.str().c_str() );
    }
#endif
    return pointer;
}
    
//--------------------------------------

// virtual
void
allocation_center_imp::deallocate(
    void *          in_pointer,
    const char *    in_file,
    int             in_line )
{
    static const text this_method_name[]
        = "delete_array(...)";

#if 0 
    logger & log = logger::acquire_default_instance();
    // @@@ FIGURE OUT HOW TO DO THIS WITHOUT GOING THROUGH
    // @@@ INFINITE RECURSION logger -> lock_factory -> ... 
//    if ( log.is_including( this_class_name ) ) 
    {
        std::ostringstream oss;
        oss << "@ " << std::hex << whole64(&in_pointer)
            << "; " << in_file << ':' << in_line; 
        log.log_trace( this_class_name, this_method_name,
            oss.str().c_str() );
    }
#endif
    if ( in_pointer != 0 )
    {
        delete [] static_cast<byte*>(in_pointer);
    }
}

//--------------------------------------
//  private methods
//--------------------------------------

// static
allocation_center &
allocation_center::create()
{
    return *(::new allocation_center_imp);
}

//--------------------------------------

// static
void
allocation_center::destroy(
    allocation_center & in_singleton )
{
    ::delete &static_cast<allocation_center_imp&>(in_singleton);
}

//--------------------------------------

}; // end of namespace lifecycle

//--------------------------------------
//  global operators
//--------------------------------------

void *
operator new(
    size_t                      in_size,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    return lifecycle::allocation_center::get_singleton()
        .allocate( in_size, in_file, in_line );
}

//--------------------------------------

void *
operator new[](
    size_t                      in_size,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    return lifecycle::allocation_center::get_singleton()
        .allocate( in_size, in_file, in_line );
}

//--------------------------------------

void
operator delete(
    void *                      in_pointer,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    return lifecycle::allocation_center::get_singleton()
        .deallocate( in_pointer, in_file, in_line );
}

//--------------------------------------

void
operator delete[](
    void *                      in_pointer,
    atoms::allocation_placement,
    const char *                in_file,
    int                         in_line )
{
    return lifecycle::allocation_center::get_singleton()
        .deallocate( in_pointer, in_file, in_line );
}

//----------------------------------------------------------
// (end of file)
