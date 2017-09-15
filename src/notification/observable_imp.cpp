//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_imp.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable_imp.hpp> // this header

#include <atoms/primitives.hpp>
#include <atoms/stream_string.hpp>
#include <collection/ref_list.hpp>
#include <lifecycle/logger.hpp>
#include <notification/observer.hpp>

#include <iostream>

#define BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 0
#define BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES 0

namespace notification
{
    using namespace atoms;
    using namespace lifecycle;

//--------------------------------------
//  internal definitions
//--------------------------------------

struct observer_name {
    observer &          _observer;
    stringex            _name;
    const text *        _text_name;
    observer_name(
        observer &    in_observer )
      :
        _observer(    in_observer ),
        _name(        in_observer.make_name_observer() ),
        _text_name(     _name )
    {}
};

typedef collection::ref_list<observer> observers;
typedef collection::ref_list<observer_name> observer_names;

//--------------------------------------

class observable_rep {
public:

    observers       _observers;
    observer_flags  _accumulated_flags;
    boolean         _is_accumulating;

#if BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 
    atoms::byte     _corruption_buffer[64];
    boolean         _is_corrupted;
    boolean         _is_destroyed;
#endif
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
    observer_names  _observer_names;
    stringex        _name_observable;
    const text *    _text_name_observable;
#endif

    BEACH_ALLOCATION_OPERATORS

    observable_rep()
      :
        _accumulated_flags( 0 ),
        _is_accumulating(   false )
#if BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 
       ,_is_corrupted(      false ),
        _is_destroyed(      false )
#endif
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
       ,_text_name_observable( 0 )
#endif
    {
#if BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 
        for (atoms::whole i = 0; i < sizeof(_corruption_buffer); i++)
            _corruption_buffer[i] = 0;
#endif
    }
    void check_corruption();

    void notify_observers(
        const observable_imp &  in_handle,
        observer_flags          in_flags,
        const void *            in_affected_object );

    void trace_if_logging(
        const observable &      in_observable,
        const observer &        in_observer,
        const text *            in_name_method ) const;

}; // end of class observable_imp

//--------------------------------------

static const text name_class_this[] = "observable";

//--------------------------------------
//  internal methods
//--------------------------------------

void
observable_rep::check_corruption()
{
#if BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 
    if (_is_corrupted)
        return;
    for (atoms::whole i = 0; i < sizeof(_corruption_buffer); i++)
    {
        if (_corruption_buffer[i] != 0) {
            std::cout << "!!! observable_imp is corrupted"; 
            _is_corrupted = true;
            break;
        }
    }
#endif
}

//--------------------------------------

void
observable_rep::notify_observers(
    const observable_imp &  in_handle,
    observer_flags          in_flags,
    const void *            in_affected_object )
{
    check_corruption();
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
    _name_observable = in_handle.make_name_observable();
    _text_name_observable = _name_observable;
#endif
    observer * lastobserver = 0;
    for (observers::iterator
         i(    _observers.begin() ),
         iend( _observers.end() );
         i != iend; ) // no increment here
    {
        observer & obs = *i;
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
        const text * textnameobserver = 0;
        for (observer_names::iterator
             i(    _observer_names.begin() ),
             iend( _observer_names.end() );
             i != iend; i++ )
            if (&i->_observer == &obs) {
                textnameobserver = i->_name;    
                break;
            }
#endif
        obs.update_observer( in_handle, in_affected_object, in_flags );
        // !!! if this gets detached from the observer
        // !!! during the above call, the iterator will
        // !!! be invalidated, so reestablish it
        if (_observers.begin() == _observers.end())
            break; /// short-circuit
        i    = _observers.find_iterator( obs ); // $$$
        iend = _observers.end();
        if (i != iend) {
            lastobserver = &obs;
            ++i;
        } else { // !!! observer was detached
            if (lastobserver == 0)
                i = _observers.begin();
            else {
                i = _observers.find_iterator( *lastobserver );
                ++i;
            }
        }
    }
}

//--------------------------------------

void
observable_rep::trace_if_logging(
    const observable &  in_observable,
    const observer &    in_observer,
    const text *        in_name_method ) const
{
    logger & log = logger::get_singleton();
    if (!log.is_including( name_class_this ))
        return;
    stream_string_o sso;
    sso << "this <"         << std::hex << this
        << '/'              << in_observable.make_name_observable()
        << "> observer <"   << std::hex << &in_observer
        << '/'              << in_observer.make_name_observer()
        << '>';
    log.log_trace( name_class_this, in_name_method, sso.str().c_str() );
}

//--------------------------------------
//  public methods
//--------------------------------------

observable_imp::observable_imp()
  :
    _rep( 0 )
{}

//--------------------------------------

// virtual
observable_imp::~observable_imp()
{
    notify_observers( observe_destructing );
    if (_rep != 0) { 
#if BEACH_NOTIFICATION_OBSERVABLE_CHECK_CORRUPTION 
        _rep->check_corruption();
        _rep->_is_destroyed = true;
#endif
        delete _rep;
        _rep = 0;
    }
}

//--------------------------------------

observable_imp::observable_imp(
    const observable_imp & )
  :
    _rep( 0 )
{
    // nothing copied
}

//--------------------------------------

observable_imp &
observable_imp::operator =(
    const observable_imp & )
{
    // nothing copied
    return *this;
}

//--------------------------------------

// virtual
stringex
observable_imp::make_name_observable() const
{
    return 0;
}

//--------------------------------------

// virtual
boolean
observable_imp::is_observable(
    const observable & rhs ) const
{
    return static_cast<const observable*>(this) == &rhs;
}

//--------------------------------------

// virtual
void
observable_imp::attach_observer(
    observer & in_observer ) const
{
    if (_rep == 0)
        _rep = new observable_rep;
    else { // no-op if observer already attached
        _rep->check_corruption();
        if (   _rep->_observers.find_iterator( in_observer )
            != _rep->_observers.end() )
            return;
    }
    _rep->_observers.add( in_observer );
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
    _rep->_observer_names.add( *(new observer_name( in_observer )) );
#endif
    _rep->trace_if_logging( *this, in_observer, "attach_observer(...)" );
}

//--------------------------------------

// virtual
void
observable_imp::insert_observer(
    observer & in_observer ) const
{
    if (_rep == 0)
        _rep = new observable_rep;
    else { // no-op if observer already attached
        _rep->check_corruption();
        if (   _rep->_observers.find_iterator( in_observer )
            != _rep->_observers.end())
            return;
    }
    _rep->_observers.insert( _rep->_observers.begin(), in_observer );
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
    _rep->_observer_names.insert( _rep->_observer_names.begin(),
        *(new observer_name( in_observer )) );
#endif
    _rep->trace_if_logging( *this, in_observer, "insert_observer(...)" );
}

//--------------------------------------

// virtual
void 
observable_imp::detach_observer(
    observer & in_observer ) const
{
    if ( _rep == 0 )
        return;
    _rep->check_corruption();
    // no-op if observer isn't attached
    _rep->_observers.erase_first( in_observer );
#if BEACH_NOTIFICATION_OBSERVABLE_TRACK_NAMES
    for (observer_names::iterator
         i(    _rep->_observer_names.begin() ),
         iend( _rep->_observer_names.end() );
         i != iend; i++ )
        if (&i->_observer == &in_observer) {
            _rep->_observer_names.erase( i );
            break;
        }
#endif
    _rep->trace_if_logging( *this, in_observer, "detach_observer(...)" );
}

//--------------------------------------

// virtual
void
observable_imp::notify_observers(
    observer_flags  in_flags,
    const void *    in_affected_object ) const
{
    if (_rep == 0)
        return;
    _rep->check_corruption();
    if (_rep->_is_accumulating)
        _rep->_accumulated_flags |= in_flags;
    else
        _rep->notify_observers( *this, in_flags, in_affected_object );
}

//--------------------------------------

// virtual
observer_flags
observable_imp::get_accumulated_flags() const
{
    if (_rep == 0)
        return 0;
    return _rep->_accumulated_flags;
}

//--------------------------------------

// virtual
boolean
observable_imp::is_accumulating() const
{
    if (_rep == 0)
        return false;
    return _rep->_is_accumulating;
}

//--------------------------------------

// virtual
void
observable_imp::enable_accumulation(
    boolean do_clear_flags ) const
{
    if (_rep == 0)
        _rep = new observable_rep;
    _rep->_is_accumulating = true;
    if (do_clear_flags)
        _rep->_accumulated_flags = 0;
}

//--------------------------------------

// virtual
void
observable_imp::disable_accumulation(
    boolean do_clear_flags,
    boolean do_notify_observers ) const
{
    if (_rep == 0)
        return;
    if (do_notify_observers && (_rep->_accumulated_flags != 0))
        _rep->notify_observers( *this, _rep->_accumulated_flags, 0 );
    if (do_clear_flags)
        _rep->_accumulated_flags = 0;
    _rep->_is_accumulating = false;
}

//--------------------------------------

// virtual
void
observable_imp::flush_accumulation(
    boolean do_clear_flags,
    boolean do_notify_observers ) const
{
    if (_rep == 0)
        return;
    if (do_notify_observers && (_rep->_accumulated_flags != 0))
        _rep->notify_observers( *this, _rep->_accumulated_flags, 0 );
    if (do_clear_flags)
        _rep->_accumulated_flags = 0;
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// (end of file)
