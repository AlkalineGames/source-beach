#if !defined(BEACH_SERIALIZATION_CLASS_INFO_SERIALIZABLE)
#define      BEACH_SERIALIZATION_CLASS_INFO_SERIALIZABLE
//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_info_serializable.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <serialization/serializable.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/class_info.hpp>

namespace serialization
{
    using atoms::boolean;
    using atoms::whole;
    using serialization::reader;
    using serialization::selector;
    using serialization::serializable;
    using serialization::writer;
    using lifecycle::class_identifier;
    using lifecycle::class_info;
    using lifecycle::class_info_extension;

//--------------------------------------

/// dynamic definition of a serializable class
/**
 *  @note   design patterns applied:
 *              - Extension Object  [PLoP3]
 *              - Taxonomy        [POSA1]
 *              - Serializer        [PLoP3]
 */      
class class_info_serializable
    : public class_info_extension,
      public serializable
{
public:

    static class_identifier get_class_id();

    class_info_serializable( class_info & );
    virtual ~class_info_serializable();

    virtual void update_owner_changed(); ///< class_info_extension required override

	/// @name serialization
    //@{
    enum selector_index
    {
        selector_all,       ///< combination of all selectors
        selector_identity,  ///< combination of all identiny selectors
        selector_class_id,
        selector_class_name,
        selector_last_object_id,
        selector_count
    };
    virtual const selector & get_selector_all(); ///< polymorphic (all for the instance)
    static  const selector & get_selector( whole in_index );
    static  void register_selectors();

    virtual boolean read_from( reader & );
    virtual void    write_to(  writer &, const selector * = 0 );
    //@}

private:

    boolean _is_reading;
    
};  // end of class class_info_serializable

//--------------------------------------

}; // end of namespace threed

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_CLASS_INFO_SERIALIZABLE
