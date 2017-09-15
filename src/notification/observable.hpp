#if !defined(BEACH_NOTIFICATION_OBSERVABLE)
#define      BEACH_NOTIFICATION_OBSERVABLE
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <notification/observer_flags.hpp>

namespace notification
{
    using atoms::boolean;
    using atoms::stringex;
    class observer;

//--------------------------------------

/// interface for observable objects.
/**
 *  Application of the Observer [GoF] design pattern with variations.
 *  observable is the "subject" participant in the original pattern.
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
class observable
{
public:

    enum observer_flag ///< bitwise values can be combined
    { 
        no_observer_flag,                              ///< == 0x00000000
        observe_destructing,                           ///< == 0x00000001
        next_observer_flag = observe_destructing << 1, ///< == 0x00000002
    };
#if 0 // @@@ FUTURE DESIGN
    /// overrideable: notifes observers of destruction
    /**
     *  subclasses should override this 
     */
    virtual void            prepare_destruction() = 0;
#endif
    virtual stringex        make_name_observable()              const = 0;
        ///< override to provide log tracing detail

    virtual boolean         is_observable( const observable & ) const = 0;

    virtual void            attach_observer( ///< no-op if already attached
        observer & )                                            const = 0;
    virtual void            insert_observer( ///< ...ditto... but inserted in front of others instead of after
        observer & )                                            const = 0;
    virtual void            detach_observer( ///< no-op if not attached
        observer & )                                            const = 0;

    virtual void            notify_observers(
        observer_flags          in_flags,
        const void *            in_affected_object = 0 )        const = 0;

    void                    notify_observers(              
        const void *            in_affected_object = 0 )        const
    {
        notify_observers( no_observer_flag, in_affected_object );
    }
    void                    notify_observers_or_set_flags(
        observer_flags *        inout_observer_flags,
        observer_flags          in_observer_flags,
        const void *            in_affected_object = 0 )        const
    {
        if (inout_observer_flags != 0)
            *inout_observer_flags |= in_observer_flags;
        else
            notify_observers( in_observer_flags, in_affected_object );
    }
    /// @name accumulation feature
    //@{
    virtual observer_flags  get_accumulated_flags()             const = 0;
    virtual boolean         is_accumulating()                   const = 0;

    virtual void            enable_accumulation(
        boolean                 do_clear_flags      = false )   const = 0;

    virtual void            disable_accumulation(
        boolean                 do_clear_flags      = false,
        boolean                 do_notify_observers = false )   const = 0;
        ///< observers only notified if flags are non-zero

    virtual void            flush_accumulation(
        boolean                 do_clear_flags      = true,
        boolean                 do_notify_observers = true )    const = 0;
        ///< observers only notified if flags are non-zero
    //@}

}; // end of class observable

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE
