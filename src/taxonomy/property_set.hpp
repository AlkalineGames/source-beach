#if !defined(BEACH_TAXONOMY_PROPERTY_SET)
#define      BEACH_TAXONOMY_PROPERTY_SET
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_set.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
//#include <collection/ref_set.hpp>
#include <collection/ref_map_by_string.hpp>
#include <serialization/serializable.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/identified_object.hpp>
#include <lifecycle/object_identification_name.hpp>
#include <taxonomy/property.hpp>

namespace taxonomy
{
    using atoms::boolean;
    using chain::context;
    using atoms::real;
    using atoms::text;
    using atoms::whole;
    using serialization::reader;
    using serialization::selector;
    using serialization::serializable;
    using serialization::writer;
    using lifecycle::class_identifier;
    using lifecycle::identified_object;
    using lifecycle::object_identification;
    using lifecycle::object_identification_name;

//--------------------------------------

//typedef collection::ref_set<property> property_set_collection;
// $$$ map is much less memory efficient than a set because
// $$$ each key is an unshared copy of the property's name string
typedef collection::ref_map_by_string<property>
    property_set_collection;

//--------------------------------------

/// a dynamic set of properties
/**
 *  @note   design patterns applied:
 *              - Dynamic Object Model/Property List    [PLoP5]
 *              - Null Object                           [PLoP3]
 *              - Serializer                            [PLoP3]
 */      
class property_set
    : public identified_object,
      public serializable,
      public property_set_collection
{
public:

    static class_identifier get_class_id();

    property_set( const text * in_name );
    virtual ~property_set();

    /// @accessors: null object returned if property does not exist
    //@{
    const property & get_property(    const text * in_name ) const;
          property & get_property_nc( const text * in_name )
    {
        return const_cast<property&>(get_property( in_name ));
    }
    //@}

    /// @name serialization, serializable overrides
    //@{
    enum selector_index
    {
        selector_all,       ///< combination of all selectors
        selector_identity,  ///< combination of all identiny selectors
        selector_name,
        selector_property,
        selector_type,
        selector_array,
        selector_value,
        selector_count
    };
    virtual const selector &    get_selector_all(); ///< polymorphic (all for the instance)
    static  const selector &    get_selector( whole in_index );
    static  void                register_selectors();
    virtual boolean             read_from( context &, reader & );
    virtual void                write_to(  context &, writer &, const selector * = 0 );
    //@}    

protected:

    /// identified_object override
    virtual object_identification & get_identification_nc();

private:

    object_identification_name _identification;
#if 0
	collection _all;	
#endif
}; // end of class property_set

//--------------------------------------

}; // end of namespace simulation

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_SET
