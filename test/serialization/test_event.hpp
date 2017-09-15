#if !defined(BEACH_SERIALIZATION_TEST_EVENT)
#define      BEACH_SERIALIZATION_TEST_EVENT
//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_event.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <notification/event.hpp>

namespace serialization
{
    using atoms::text;
    using atoms::stringex;
    using notification::event;

//--------------------------------------

/// event class for testing

class test_event
{
friend class test_event_handler;
public:

    test_event( const text * in_name );
    virtual ~test_event();

    const stringex & get_name() const { return _name; }

private:

    /// @name copy operations not implemented
    //@{
    test_event(               const test_event & );
    test_event & operator = ( const test_event & );
    //@}

    stringex    _name;
    event *     _world_event;

}; // end of class test_event

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_TEST_EVENT
