#if !defined(BEACH_ATOMS_VERSION)
#define      BEACH_ATOMS_VERSION
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       version.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>

namespace atoms
{

//--------------------------------------

#pragma pack(1)

/// canonical version structure

struct version
{
    version( no_init_type )
    {}
    version()
      : _major( 0 ), _minor( 0 ), _build( 0 )
    {}
    version( whole in_major,     whole in_minor,     whole in_build )
      : _major(    in_major ), _minor( in_minor ), _build( in_build )
    {}
    operator whole32() const
    {
        return (whole32(_major) << 16)
             + (whole32(_minor) << 8 )
             +  whole32(_build);
    }
    bool operator ==( const version & rhs ) const
    {
        return whole32(*this) == whole32(rhs);
    }
    bool operator !=( const version & rhs ) const
    {
        return whole32(*this) != whole32(rhs);
    }
    bool operator <=( const version & rhs ) const
    {
        return whole32(*this) <= whole32(rhs);
    }
    bool operator >=( const version & rhs ) const
    {
        return whole32(*this) >= whole32(rhs);
    }
    bool operator <( const version & rhs ) const
    {
        return whole32(*this) < whole32(rhs);
    }
    bool operator >( const version & rhs ) const
    {
        return whole32(*this) > whole32(rhs);
    }
    whole8 _major;
    whole8 _minor;
    whole8 _build;
};

//--------------------------------------

}; // end of namespace atoms

#pragma pack()

//----------------------------------------------------------
#endif // BEACH_ATOMS_VERSION
