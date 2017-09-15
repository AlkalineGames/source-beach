#if !defined(BEACH_ATOMS_POINTER_OWNERSHIP)
#define      BEACH_ATOMS_POINTER_OWNERSHIP
//----------------------------------------------------------
//  Copyright 2008-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       pointer_ownership.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

namespace atoms
{

//--------------------------------------

/// template for a pointer that indicates its ownership

template <typename pointer_type>
class pointer_ownership
{
public:

    BEACH_ALLOCATION_OPERATORS

    pointer_type *  _pointer;
    bool            _owned;

    pointer_ownership(
        pointer_type *  p       = 0,
        bool            owned   = false )
      :
        _pointer( p ), _owned( owned )
    {}
    pointer_ownership & operator  =( pointer_type * p ) { _pointer = p; } 
    bool                operator ==( pointer_type * p ) const { return _pointer == p; } 
    bool                operator !=( pointer_type * p ) const { return _pointer != p; } 
    bool                operator !()                    const { return _pointer == 0; }
    bool                null()                          const { return _pointer == 0; }

    operator pointer_type*() const { return _pointer; }

    /** @name dereferencing operators
     *  !!! clients must not call these if the pointer is null */
    //@{
    pointer_type * operator ->() const { return  _pointer; } 
    pointer_type & operator  *() const { return *_pointer; } 
    //@}

    /// delete if owned and clear pointer to 0
    void delete_if_owned()
    {
        if ( _owned && (_pointer != 0) )
        {
            BEACH_DELETE(pointer_type,_pointer);
            _pointer = 0;
        }
    }
    /// delete if owned and clear pointer to 0, using default deallocation
    void delete_if_owned_via_default()
    {
        if ( _owned && (_pointer != 0) )
        {
            delete _pointer;
            _pointer = 0;
        }
    }

}; // end of template class pointer_ownership

//--------------------------------------

/// template for an ownership pointer that auto destroys its referent

template <typename pointer_type>
class pointer_ownership_auto
    : public pointer_ownership<pointer_type>
{
public:

    pointer_ownership_auto(
        pointer_type *  p       = 0,
        bool            owned   = true )
      : pointer_ownership<pointer_type>( p, owned )
    {}
    ~pointer_ownership_auto()
    {
        this->delete_if_owned();
    }
};

//--------------------------------------

/// template for a pointer that denies ownership

template <typename pointer_type>
class pointer_ownership_deny
    : public pointer_ownership<pointer_type>
{
public:

    pointer_ownership_deny( pointer_type * p )
      : pointer_ownership<pointer_type>( p, false )
    {}
};

//--------------------------------------

/// template for a pointer that grants ownership

template <typename pointer_type>
class pointer_ownership_grant
    : public pointer_ownership<pointer_type>
{
public:

    pointer_ownership_grant( pointer_type * p )
      : pointer_ownership<pointer_type>( p, true )
    {}
};

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_POINTER_OWNERSHIP
