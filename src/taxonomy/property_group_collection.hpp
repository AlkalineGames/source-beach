#if !defined(BEACH_TAXONOMY_PROPERTY_GROUP_COLLECTION)
#define      BEACH_TAXONOMY_PROPERTY_GROUP_COLLECTION

//----------------------------------------------------------
//  Copyright 2008-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group_collection.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <taxonomy/property_group.hpp>

namespace collection
{
    class pointer_vector;
}

//--------------------------------------

namespace taxonomy
{
    using collection::pointer_vector;

//--------------------------------------

/// property_group wrapper for a collection
/**
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */     
class property_group_collection
    : public property_group
{
public:

    property_group_collection(
        pointer_vector &,
        const text * in_property_name );

    virtual ~property_group_collection();
      
    /// @name overrides
    //@{
    virtual whole           get_property_count() const; ///< returns size of collection
    virtual const text **   get_property_names() const; ///< $$$ DYNAMICALLY ALLOCATED
    virtual stringex        get_property_value() const; ///< returns "n properties" (n==count) at this level
    //@}
    
protected:

    pointer_vector &        _collection;

private:

    const stringex          _property_name;
    mutable whole           _property_name_count;
    mutable const text **   _property_names;

}; // end of class property_group

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
// $Log: property_group_collection.hpp,v $
// Revision 1.3  2008/09/10 07:17:08  cat
// renamed sandbar to coast
//
// Revision 1.2  2008/04/30 19:46:37  cat
// get_property_value() overriden to provide properties count
//
// Revision 1.1  2008/03/29 03:25:38  cat
// created
//
//----------------------------------------------------------

#endif // BEACH_TAXONOMY_PROPERTY_GROUP_COLLECTION
