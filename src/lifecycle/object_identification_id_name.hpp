#if !defined(BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID_NAME)
#define      BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID_NAME
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification_id_name.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <lifecycle/object_identification.hpp>

namespace lifecycle
{
    using atoms::text;

//--------------------------------------

/// concrete subclass for identification by id and name 
/**
 *  @note	design patterns applied:
 *				- Identity Field    [PEAA]
 *				- Name              [AP]
 */
class object_identification_id_name
    : public object_identification
{
public:

    object_identification_id_name(
        id_value = 0, const text * = 0 );

    object_identification_id_name(
        const object_identification_id_name & );

    virtual ~object_identification_id_name();

    /// @name accessor overrides
    //@{    
    virtual id_value        get_id()    const;
    virtual const name &    get_name()  const;
    virtual boolean         has_id()    const;  ///< this level always returns true
    virtual boolean         has_name()  const;  ///< this level always returns true
    //@}

protected:

    /// @name mutator overrides
    //@{    
    virtual void set_id(        id_value );
    virtual void set_id_name(   id_value, const name & );
    virtual void set_name(                const name & );
    //@}

private:

    id_value    _id;
    name        _name;

}; // end of class object_identification_id_name

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_OBJECT_IDENTIFICATION_ID_NAME
