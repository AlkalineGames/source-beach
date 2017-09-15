#if !defined(BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_NAME)
#define      BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_NAME

//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_name.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <lifecycle/object_identification.hpp>

//--------------------------------------

namespace lifecycle
{
    using atoms::text;

//--------------------------------------

/// concrete subclass for identification by name
/**
 *  @note	design patterns applied:
 *				- Name [AP]
 */
class object_identification_name
    : public object_identification
{
public:

    object_identification_name(
        const text * );

    object_identification_name(
        const object_identification_name & );

    virtual ~object_identification_name();

    /// @name accessor overrides
    //@{    
    virtual const name &    get_name()  const;
    virtual boolean         has_name()  const;  ///< this level always returns true
    //@}

protected:

    /// @name mutator overrides
    //@{    
    virtual void set_name( const name & );
    //@}

private:

    name _name;

}; // end of class object_identification_id_name

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identification_name.hpp,v $
// Revision 1.1  2006/12/06 23:39:23  cat
// creation; refactored from portions of old named_object
//
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_NAME
