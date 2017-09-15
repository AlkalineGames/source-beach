#if !defined(BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID)
#define      BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID

//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_id.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification.hpp>

//--------------------------------------

namespace lifecycle
{

//--------------------------------------

/// concrete subclass for identification by id
/**
 *  @note	design patterns applied:
 *				- Identity Field [PEAA]
 */
class object_identification_id
    : public object_identification
{
public:

    object_identification_id(
        id_value );

    object_identification_id(
        const object_identification_id & );

    virtual ~object_identification_id();

    /// @name accessor overrides
    //@{    
    virtual id_value    get_id()  const;
    virtual boolean     has_id()  const;  ///< this level always returns true
    //@}

protected:

    /// @name mutator overrides
    //@{    
    virtual void set_id( id_value );
    //@}

private:

    id_value _id;

}; // end of class object_identification_id

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identification_id.hpp,v $
// Revision 1.1  2006/12/06 23:39:23  cat
// creation; refactored from portions of old named_object
//
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID
