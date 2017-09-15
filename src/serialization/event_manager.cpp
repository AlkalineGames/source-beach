//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       event_manager.cpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <serialization/event_manager.hpp> // this header

#include <collection/list_of_string.hpp>
#include <invocation/command_kill.tpp>
#include <lifecycle/logger.hpp>
#include <lifecycle/object_catalog_utility.hpp>
#include <notification/event.hpp>
#include <notification/event_channel.hpp>
#include <notification/event_handler.hpp>
#include <serialization/event_serializable.hpp>
#include <serialization/event_channel_serializable.hpp>
#include <serialization/reader.hpp>
#include <serialization/serializable_spec.hpp>

namespace serialization
{
    using namespace atoms;
    using collection::list_of_string;
    using lifecycle::logger;

//--------------------------------------
//  internal definitions
//--------------------------------------

class event_handler_null
   : public event_handler
#if 0
     public serializable_factory
#endif
{
public:

    event_handler_null()
      :
        event_handler( "(null)" )
    {}
    virtual ~event_handler_null() {}

    /// @event_handler overrides
    //@{
    virtual boolean handle_event(
        const event &       in_event,
        virtual_object *    in_subject )
    {
        return true;
    }
    //@
#if 0
    /// @name serializable_factory overrides
    //@{
    virtual serializable *   acquire(
        context &               in_context,
        serializable_spec &     inout_spec,
        reader *                in_state_reader );
    //@}
#endif

    void substitute_for(
        const text * in_name )
    {
        for ( list_of_string::iterator
              iter( _substitution_names.begin() );
              iter != _substitution_names.end();
              iter++ )
        {
            if ( *iter == in_name )
            {
                return;
            } 
        }
        stringex handlername( in_name );
        _substitution_names.push_back( handlername );
        stringex logmsg( "Null event handler is substituting for <" );
        logmsg += handlername;
        logmsg += ">.";
        logger::get_singleton().log_information( 0, 0, logmsg );
    }

private:

    list_of_string _substitution_names;

}; // end of class event_handler_null

//--------------------------------------

/// internal implementation subclass

class event_manager_imp
    : public event_manager
{
friend class invocation::command_kill<event_manager>;
friend class lifecycle::object_catalog_utility<event_manager,event_manager>;
public:

    BEACH_ALLOCATION_OPERATORS

    event_manager_imp();
    virtual ~event_manager_imp();

    /// @@@ TODO - RESPONSE FROM POST_EVENT
    virtual boolean                 post_event(
                                        const event & );
    virtual boolean                 post_event(
                                        const text *     in_name,
                                        virtual_object * in_subject = 0 );

    virtual const event_channel &   register_event_channel(
                                        const text * in_name );
    virtual const event_channel *   find_event_channel_by_name_const(
                                        const text * in_name );
    virtual       event_channel *   find_event_channel_by_name(
                                        const text * in_name );

	virtual const event &           register_event(
                                        const text * in_name );
	virtual const event *           find_event_by_name_const(
                                        const text * in_name );
    virtual       event *           find_event_by_name(
                                        const text * in_name );

    virtual void                    register_event_handler(
                                        event_handler & );
    virtual void                    unregister_event_handler(
                                        event_handler & );
    virtual const event_handler *   find_event_handler_by_name(
                                        const text * in_event_name );
    virtual void                    install_event_handler_null();

    /// @name serializable_factory overrides
    //@{
    virtual serializable *   acquire(
        context &               in_context,
        serializable_spec &     inout_spec,
        reader *                in_state_reader );
    //@}

private:

    typedef collection::ref_list<event_channel>    channels;
    typedef collection::ref_list<event> 		    events;
    typedef collection::ref_list<event_handler>    handlers;

	event &         add_new_event(          const text * in_name );
    event_channel & add_new_event_channel(  const text * in_name );

    channels                _channels;
    events		            _events;
    handlers                _handlers;
    event_handler_null *    _handler_null;

}; // end of class event_manager_imp

//--------------------------------------

static const text this_class_name[]
    = "event_manager";

static event_manager * singleton_cached = 0;
    
//--------------------------------------
//  internal publi methods
//--------------------------------------

event_manager_imp::event_manager_imp()
  :
    _channels( atoms::destroyer<event_channel>() ),
    _events( atoms::destroyer<event>() ),
    //_handlers(own_it)  the handlers are singletons and owned by the singletons
    _handler_null( 0 )
{}

//--------------------------------------

// virtual
event_manager_imp::~event_manager_imp()
{
    delete _handler_null;
}

//--------------------------------------

boolean
event_manager_imp::post_event(
    const event & in_event )
{
    static const text this_method_name[]
        = "post_event( const event & )";

    stringex errmsg;
    do
    {
        if ( in_event.get_event_channel() == 0 )
        {
            errmsg  = "event \"";
            errmsg += in_event.get_name();
            errmsg += "\" has no channel";
            break;
        }
        return in_event.get_event_channel()->post_event(
                    in_event, 0 );
    }
    while ( false );
    logger::get_singleton().log_error(
        this_class_name, this_method_name, errmsg );
    return false;
}

//--------------------------------------

boolean
event_manager_imp::post_event(
    const text *        in_event_name,
    virtual_object *    in_subject )
{
    static const text this_method_name[]
        = "post_event( const text * )";

    stringex errmsg;
    do
    {
        const event * ev = find_event_by_name_const(
            in_event_name );
        if ( ev == 0 )
        {
            errmsg  = "event named \"";
            errmsg += in_event_name;
            errmsg += "\" is not registered ";
            break;
        }
        return post_event( *ev );
        if ( ev->get_event_channel() == 0 )
        {
            errmsg  = "event \"";
            errmsg += in_event_name;
            errmsg += "\" has no channel";
            break;
        }
        return ev->get_event_channel()->post_event(
                *ev, in_subject );
    }
    while ( false );
    logger::get_singleton().log_error(
        this_class_name, this_method_name, errmsg );
    return false;
}

//--------------------------------------

const event *
event_manager_imp::find_event_by_name_const(
    const text * in_event_name )
{
    for ( events::const_iterator
          i( _events.begin() ); i != _events.end(); i++ )
    {
        const event & entry = *i;
        if ( entry.get_name().compare(
                in_event_name ) == 0 )
        {
            return &entry;
        }
    }
    return 0;
}

//--------------------------------------

event *
event_manager_imp::find_event_by_name(
    const text * in_event_name )
{
    return const_cast<event*>(
        find_event_by_name_const(
            in_event_name ));
}

//--------------------------------------

const event &
event_manager_imp::register_event(
    const text * in_event_name )
{
    static const text this_method_name[]
        = "register_event(...);";

    const event * entry = find_event_by_name( in_event_name );
    if ( entry != 0 )
    {
        return *entry;
    }
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        log.log_trace( this_class_name, this_method_name,
            in_event_name );
    }
    return add_new_event( in_event_name );
}

//--------------------------------------

const event_channel *
event_manager_imp::find_event_channel_by_name_const(
    const text * in_event_channel_name )
{
    for ( channels::const_iterator
          i( _channels.begin() ); i != _channels.end(); i++ )
    {
        const event_channel & entry = *i;
        if ( entry.get_name().compare(
                in_event_channel_name ) == 0 )
        {
            return &entry;
        }
    }
    return 0;
}

//--------------------------------------

event_channel *
event_manager_imp::find_event_channel_by_name(
    const text * in_event_channel_name )
{
    return const_cast<event_channel*>(
        find_event_channel_by_name_const(
            in_event_channel_name ));
}

//--------------------------------------

const event_channel &
event_manager_imp::register_event_channel(
    const text * in_event_channel_name)
{
    static const text this_method_name[]
        = "register_event_channel(...);";

    const event_channel * entry =
        find_event_channel_by_name_const( in_event_channel_name );
    if ( entry != 0 )
    {
        return *entry;
    }
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        log.log_trace( this_class_name, this_method_name,
            in_event_channel_name );
    }
    return add_new_event_channel( in_event_channel_name );
}

//--------------------------------------

void
event_manager_imp::register_event_handler(
    event_handler & in_handler )
{
    static const text this_method_name[]
        = "register_event_handler(...);";

    if ( _handlers.contains( in_handler ) )
    {
        return;
    }
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        log.log_trace( this_class_name, this_method_name,
            in_handler.get_name()  );
    }
    _handlers.add( in_handler );
}

//--------------------------------------

void
event_manager_imp::unregister_event_handler(
    event_handler & in_handler )
{
    static const text this_method_name[]
        = "register_event_handler(...);";

    if ( _handlers.contains( in_handler ) )
    {
        return;
    }
    logger & log = logger::get_singleton();
    if ( log.is_including( this_class_name ) )
    {
        log.log_trace( this_class_name, this_method_name,
            in_handler.get_name()  );
    }
    _handlers.erase_first( in_handler );
}

//--------------------------------------

const event_handler *
event_manager_imp::find_event_handler_by_name(
    const text * in_event_handler_name )
{
    for ( handlers::const_iterator
          i( _handlers.begin() ); i != _handlers.end(); i++ )
    {
        const event_handler & entry = *i;
        if ( entry.get_name().compare(
                in_event_handler_name ) == 0 )
        {
            return &entry;
        }
    }
    if ( _handler_null != 0 )
    {
        _handler_null->substitute_for( in_event_handler_name );
    }
    return _handler_null;
}

//--------------------------------------

void
event_manager_imp::install_event_handler_null()
{
    if ( _handler_null == 0 )
    {
        _handler_null = new event_handler_null;
    }
}

//--------------------------------------

// virtual
serializable *
event_manager_imp::acquire(
    context &           in_context,
    serializable_spec & inout_spec,
    reader *            in_state_reader )
{
    static const text this_method_name[]
        = "acquire( const spec &, reader * );";

    serializable * ser = 0;

    if ( inout_spec._class_id == event_serializable::get_class_id() )
    {
        const event & constev =
            register_event( inout_spec._object_name );
        event & ev = const_cast<event&>(constev);
        event_extension * ext = ev.get_extension();
        if ( ext == 0 )
        {
            event_serializable * eser =
                new event_serializable( ev );
            ev.set_class_id( inout_spec._class_id );  // should probably do this in register_event
            ev.set_extension( eser );
            ser = eser;
        }
        else
        {
            ser = dynamic_cast<event_serializable*>(ext);
            if ( ser == 0 )
            {
                stringex errmsg( "extension object of event class \"" );
                errmsg += ev.get_class_name();
                errmsg += "\" is not a event_serializable";
                logger::get_singleton().log_error(
                    this_class_name, this_method_name, errmsg );
            }
        }
        if ( (ser != 0) && (in_state_reader != 0) )
        {
            ser->read_from( in_context, *in_state_reader );
        }
    }
    else if ( inout_spec._class_id == event_channel_serializable::get_class_id() )
    {
        const event_channel & constevch =
            register_event_channel( inout_spec._object_name );
        event_channel & evch = const_cast<event_channel&>(constevch);
        evch.set_class_id( inout_spec._class_id ); // should probably do this in register_event_channel
        event_channel_extension * ext = evch.get_extension();
        if ( ext == 0 )
        {
            event_channel_serializable * eser =
                new event_channel_serializable( evch );
            evch.set_extension( eser );
            ser = eser;
        }
        else
        {
            ser = dynamic_cast<event_channel_serializable*>(ext);
            if ( ser == 0 )
            {
                stringex errmsg( "extension object of event_channel \"" );
                errmsg += evch.get_name();
                errmsg += "\" is not a event_serializable";
                logger::get_singleton().log_error(
                    this_class_name, this_method_name, errmsg );
            }
        }
        if ( (ser != 0) && (in_state_reader != 0) )
        {
            ser->read_from( in_context, *in_state_reader );
        }
    }
    return ser;
}

//--------------------------------------
//  internal private methods
//--------------------------------------

event &
event_manager_imp::add_new_event(
    const text * in_class_name )
{
    event & entry = *(new event(in_class_name,0));
    _events.add( entry );
    return entry;
}

//--------------------------------------

event_channel &
event_manager_imp::add_new_event_channel(
    const text * in_event_name )
{
    event_channel & entry = *(new event_channel(in_event_name));
    _channels.add( entry );
    return entry;
}

//--------------------------------------
//  public methods
//--------------------------------------

// static
event_manager &
event_manager::acquire_singleton()
{
    return lifecycle::object_catalog_utility<event_manager,event_manager_imp>
            ::acquire_object( this_class_name, &singleton_cached );
}

//--------------------------------------

}; // end of namespace notification

//--------------------------------------
//  template instantiations
//--------------------------------------

template class invocation::command_kill<serialization::event_manager>;

//----------------------------------------------------------
// (end of file)
