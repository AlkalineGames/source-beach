#if !defined(BEACH_NOTIFICATION_OBSERVER)
#define      BEACH_NOTIFICATION_OBSERVER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <notification/observer_flags.hpp>

/// Beach Notification Framework
namespace notification
{
    class observable;
    using atoms::stringex;

//--------------------------------------

/// interface for an observer
/**
 *  Application of the Observer [GoF] design pattern with variations.
 *
 *  VARIATION 1: the update operation passes a parameter for
 *  the notifying observable/subject so that an observer can
 *  observe multiple observables/subjects and know which one
 *  is notifying. Both the notify and and update operations
 *  also pass a flags parameter to indicate the specific change.
 *
 *  VARIATION 2: additionally, a void * is passed indicating the
 *  affected object. This is a very simplified form of the 
 *  "One Message Per Affected Object" implementation pattern
 *  for the Observer Pattern described in the PLOP 2
 *  (Pattern Languages of Program Design 2) book.
 *
 *  VARIATION 3: additionally, clients can alter the 
 *  notification behavior such that observer flags are 
 *  accumulated in an internal state rather than notifying
 *  observers. This accumulation can be subsequently flushed,
 *  notifying observers followed by clearing of the state.
 *
 *  @note       design patterns applied:
 *                  - Handle/Body [PLoP4]
 *                  - Observer    [GoF], [PLoP2], [cat]
 */
class observer
{
public:

    virtual stringex        make_name_observer() const = 0;
    virtual void            update_observer(
        const observable &      in_observable,
        const void *            in_affected_object,
        observer_flags          in_flags ) = 0;
};

#define BEACH_NOTIFICATION_OBSERVER_OVERRIDES_REQUIRED \
    /** @name observer overrides required */\
    /**@{*/\
    virtual stringex        make_name_observer() const;\
    virtual void            update_observer(\
        const observable &      in_observable,\
        const void *            in_affected_object,\
        observer_flags          in_flags );\
    /**}*/

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVER
