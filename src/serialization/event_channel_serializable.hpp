#if !defined(BEACH_SERIALIZATION_EVENT_CHANNEL_SERIALIZABLE)
#define      BEACH_SERIALIZATION_EVENT_CHANNEL_SERIALIZABLE

//----------------------------------------------------------
//  Copyright 2005-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_channel_serializable.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <serialization/serializable.hpp>
#include <lifecycle/class_identifier.hpp>
#include <notification/event_channel.hpp>

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
    using notification::event_channel;
    using notification::event_channel_extension;

//--------------------------------------

/// dynamic definition of a events
/**
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */
class event_channel_serializable
    : public event_channel_extension,
      public serializable
{
public:

    static class_identifier get_class_id();

    event_channel_serializable( event_channel & );
    virtual ~event_channel_serializable();

    virtual void update_owner_changed(); ///< event_extension required override

	/// @name serialization
    //@{
    enum selector_index
    {
        selector_all,       ///< combination of all selectors
        selector_identity,  ///< combination of all identity selectors
        selector_class_id,
        selector_channel_type,
        selector_handler_name,
        selector_count
    };
    virtual const selector & get_selector_all(); ///< polymorphic (all for the instance)
    static  const selector & get_selector( whole in_index );
    static  void register_selectors();

    virtual boolean read_from( reader & );
    virtual void    write_to(  writer &, const selector * = 0 );
    //@}

};  // end of class event_channel_serializable

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: event_channel_serializable.hpp,v $
// Revision 1.2  2006/05/03 14:06:31  cat
// refactored class id and selectors
//
// Revision 1.1  2006/03/07 02:22:35  def
// event_channel_serializable.cpp
//----------------------------------------------------------

#endif // BEACH_SERIALIZATION_EVENT_CHANNEL_SERIALIZABLE
