#if !defined(BEACH_LIFECYCLE_IDENTIFIED_OBJECT)
#define      BEACH_LIFECYCLE_IDENTIFIED_OBJECT

//----------------------------------------------------------
//  Copyright 2006-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       identified_object.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/object_identification.hpp>

//--------------------------------------

namespace lifecycle
{

//--------------------------------------

/// superclass for an object with a unique id
/**
 *  @note	design patterns applied:
 *				- Identity Field    [PEAA]
 *				- Name              [AP]
 */
class identified_object ///< abstract
{
public:

    typedef object_identification::id_value id_value;
    typedef object_identification::name     name;
        
    const object_identification & get_identification() const
    {
        return const_cast<identified_object*>(this)->get_identification_nc();
    }        
    /// @name object identification delegators
    //@{    
    id_value        get_id()    const { return get_identification().get_id(); }
    const name &    get_name()  const { return get_identification().get_name(); }
    boolean         has_id()    const { return get_identification().has_id(); }
    boolean         has_name()  const { return get_identification().has_name(); }
    //@}

protected:

    identified_object();
    virtual ~identified_object(); ///< protected to prevent public destruction 

    virtual object_identification & get_identification_nc() = 0;
    
private:

    /// @name copy operations not implemented
    //@{
    identified_object(               const identified_object & );
    identified_object & operator = ( const identified_object & );
    //@}

}; // end of class identified_object

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: identified_object.hpp,v $
// Revision 1.1  2006/12/06 23:38:28  cat
// creation; refactored from old named_object
//
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_IDENTIFIED_OBJECT
