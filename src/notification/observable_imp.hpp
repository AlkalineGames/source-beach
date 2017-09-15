#if !defined(BEACH_NOTIFICATION_OBSERVABLE_IMP)
#define      BEACH_NOTIFICATION_OBSERVABLE_IMP
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

#include <atoms/allocation.hpp>
#include <notification/observable.hpp>

namespace notification
{
    class observable_rep;

//--------------------------------------

/// implementation superclass for observable subclasses
/**
 *  @note   design patterns applied:
 *              - Handle/Body [PLoP4]
 *              - Observer    [GoF], [PLoP2], [cat]
 */
class observable_imp
    : public virtual observable
{
public:

    BEACH_ALLOCATION_OPERATORS

    observable_imp();         
    virtual ~observable_imp(); ///< notifies with observe_destructing flag

    /** @name shallow copying
     * neither observers nor internal state are copied */
    //@{
    observable_imp(              const observable_imp & );
    observable_imp & operator =( const observable_imp & );
    //@}

    ///@ observable required override
    //@{
    virtual stringex        make_name_observable()              const;
    virtual boolean         is_observable( const observable & ) const;
    virtual void            attach_observer( ///< no-op if already attached
        observer & )                                            const;
    virtual void            insert_observer( ///< ...ditto... but inserted in front of others instead of after
        observer & )                                            const;
    virtual void            detach_observer( ///< no-op if not attached
        observer & )                                            const;
    virtual void            notify_observers(
        observer_flags          in_flags,
        const void *            in_affected_object = 0 )        const;
    virtual observer_flags  get_accumulated_flags()             const;
    virtual boolean         is_accumulating()                   const;
    virtual void            enable_accumulation(
        boolean                 do_clear_flags      = false )   const;
    virtual void            disable_accumulation(
        boolean                 do_clear_flags      = false,
        boolean                 do_notify_observers = false )   const;
    virtual void            flush_accumulation(
        boolean                 do_clear_flags      = true,
        boolean                 do_notify_observers = true )    const;
    //@}

private:

    mutable observable_rep * _rep;

}; // end of class observable_imp

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_IMP
