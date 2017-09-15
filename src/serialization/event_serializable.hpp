#if !defined(BEACH_SERIALIZATION_EVENT_SERIALIZABLE)
#define      BEACH_SERIALIZATION_EVENT_SERIALIZABLE

//----------------------------------------------------------
//  Copyright 2005-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_serializable.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <serialization/serializable.hpp>
#include <lifecycle/class_identifier.hpp>
#include <notification/event.hpp>

//--------------------------------------

namespace serialization
{
    using atoms::boolean;
    using atoms::whole;
    using serialization::reader;
    using serialization::selector;
    using serialization::serializable;
    using serialization::writer;
    using lifecycle::class_identifier;
    using notification::event;
    using notification::event_extension;

//--------------------------------------

/// dynamic definition of an event
/**
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */
class event_serializable
    : public event_extension,
      public serializable
{
public:

    static class_identifier get_class_id();

    event_serializable( event & );
    virtual ~event_serializable();

    virtual void update_owner_changed(); ///< event_extension required override

	/// @name serialization
    //@{
    enum selector_index
    {
        selector_all,       ///< combination of all selectors
        selector_identity,  ///< combination of all identity selectors
        selector_class_id,
        selector_class_name,
        selector_event_channel,
        selector_count
    };
    virtual const selector & get_selector_all(); ///< polymorphic (all for the instance)
    static  const selector & get_selector( whole in_index );
    static  void register_selectors();

    virtual boolean read_from( reader & );
    virtual void    write_to(  writer &, const selector * = 0 );
    //@}

};  // end of class event_serializable

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: event_serializable.hpp,v $
// Revision 1.2  2006/05/03 14:06:31  cat
// refactored class id and selectors
//
// Revision 1.1  2006/03/07 02:22:35  def
// event_channel_serializable.cpp
//----------------------------------------------------------

#endif // BEACH_SERIALIZATION_EVENT_SERIALIZABLE
