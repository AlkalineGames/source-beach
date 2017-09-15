#if !defined(BEACH_TAXONOMY_PROPERTY_GROUP_VECTOR)
#define      BEACH_TAXONOMY_PROPERTY_GROUP_VECTOR

//----------------------------------------------------------
//  Copyright 2008-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group_vector.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <collection/ref_vector.hpp>
#include <taxonomy/property_group_collection.hpp>

//--------------------------------------

namespace taxonomy
{

//--------------------------------------

/// property_group wrapper for a vector of property_group compatible objects
/**
 *  Template parameter T must be a subclass of property_group.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */     
template <typename T>
class property_group_vector
    : public property_group_collection
{
public:

    typedef collection::ref_vector<T> collection;

    property_group_vector(
        collection &,
        const text * in_property_name );

    const collection & get_collection_const() const
    {   
        return static_cast<const collection &>(_collection);
    }
    collection & get_collection()
    {   
        return static_cast<collection&>(_collection);
    }

    /// @name overrides
    //@{
    virtual stringex get_property_value() const;
    //@}
      
protected:

    /// @name overrides
    //@{
    virtual const property_group *  get_property_group( property_index ) const;
    virtual stringex                get_property_value( property_index ) const;
    //@}

}; // end of class property_group_vector

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
// $Log: property_group_vector.hpp,v $
// Revision 1.2  2008/09/10 07:17:08  cat
// renamed sandbar to coast
//
// Revision 1.1  2008/04/30 19:49:26  cat
// created
//
//----------------------------------------------------------

#endif // BEACH_TAXONOMY_PROPERTY_GROUP_VECTOR
