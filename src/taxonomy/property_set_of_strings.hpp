#if !defined(BEACH_TAXONOMY_PROPERTY_SET_OF_STRINGS)
#define      BEACH_TAXONOMY_PROPERTY_SET_OF_STRINGS
//----------------------------------------------------------
//  Copyright 2005-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_set_of_strings.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <taxonomy/property_group.hpp>

namespace taxonomy
{
    class property_set_of_strings_rep;
    class property_stringex;

//--------------------------------------

/// group of string properties
/**
 *  @note   design patterns applied:
 *              - Handle/Body [PLoP4]
 */     
class property_set_of_strings
    : public property_group
{
public:

    BEACH_ALLOCATION_OPERATORS

    property_set_of_strings();
    virtual ~property_set_of_strings();

    property_stringex & create_property(
        const stringex & in_name, ///< set will not allow duplicate names
        const stringex & in_value );
      
    /// @name property_group required overrides
    //@{
    virtual whole         get_property_count() const;
    virtual const text ** get_property_names() const;
    //@}
    
protected:

    /// @name property_group required overrides
    //@{
    virtual stringex get_property_value( property_index ) const;
    virtual boolean  set_property_value( ///< returns true if successful
        property_index,
        const text * in_value,
        stringex *   out_error_message );
    virtual real     get_property_value_scalar( property_index ) const;
        // @@@ THIS OVERRIDE IS LAME [cat]
    //@}

private:
   
    property_set_of_strings_rep & _rep; 

}; // end of class property_set_of_strings

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_SET_OF_STRINGS
