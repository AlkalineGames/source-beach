//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       logger.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/logger.hpp> // this header

#include <atoms/allocation.hpp>
#include <atoms/stream_string.hpp>
#include <collection/ref_list.hpp>
#include <lifecycle/guard.hpp>
#include <lifecycle/lock_factory.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

#include <fstream>

namespace lifecycle
{
    using namespace atoms;
    using expression::regular_expression;
    using expression::SPString;
    using expression::SPStringList;

//--------------------------------------
//  internal definitions
//--------------------------------------

/// base implementation of a diagnostic logger 
/**
 *  @note   design patterns applied:
 *              - Diagnostics Logger    [PLoP3]
 *              - Replaceable Singleton [WF]
 *              - Singleton             [GoF]
 */
class logger_imp
    : public logger
{
friend class logger;
public:

    BEACH_ALLOCATION_OPERATORS

    logger_imp();
    virtual ~logger_imp();

    virtual boolean is_echoing_information() const;

    /// @name logging selection, monitor synchronized
    //@{
    virtual const labels &  get_labels() const;
    virtual boolean         is_including(           const text * in_label ) const;
    virtual void            add_label(              const text * in_label );
    virtual void            add_labels(             const text * in_labels[] ); ///< final pointer must be 0
    virtual void            exclude(                const text * in_label );
    virtual void            include(                const text * in_label );
    virtual void            set_config_file_prefix( const text * );
    virtual void            read_config_file();
    virtual void            write_config_file();
    //@}

    /// @name echoing/interception, monitor synchronized 
    //@{
    virtual void add_interceptor(       interceptor & );
    virtual void remove_interceptor(    interceptor & );
    virtual void echo_all_to(           std::ostream * );
    //@}

    /// @name logging operations, monitor synchronized
    //@{
    virtual void log_echo_information(
        const text * in_message );

    virtual void log_error(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message );

    virtual void log_exception(
        const text * in_class_name,
        const text * in_method_name,
        const std::exception & e );

    virtual void log_information(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message );

    virtual void log_progress(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message,
        real         in_percentage );

    virtual void log_trace(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message );

    virtual void log_trace_entering( ///< traces only if class name is included
        const text * in_class_name,
        const text * in_method_name );

    virtual void log_warning(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message );
    //@}

private:

    typedef collection::ref_list<interceptor> interceptors;

    boolean internal_is_echoing_information() const;

    void internal_echo_all_to( std::ostream * );

    void internal_log(
        std::ostream &  out_stream,
        std::ostream *  out_stream_echo,
        category        in_category,
        const text *    in_prefix,
        const text *    in_class_name,
        const text *    in_method_name,
        const text *    in_message );

    void internal_log_interceptors(
        category        in_category,
        const text *    in_message );

    void internal_log_echo_information( const text * in_message );
    void internal_log_error(            const text * in_class_name, const text * in_method_name, const text * in_message );
    void internal_log_exception(        const text * in_class_name, const text * in_method_name, const std::exception & );
    void internal_log_information(      const text * in_class_name, const text * in_method_name, const text * in_message );
    void internal_log_progress(         const text * in_class_name, const text * in_method_name, const text * in_message, real in_percentage );
    void internal_log_trace(            const text * in_class_name, const text * in_method_name, const text * in_message );
    void internal_log_warning(          const text * in_class_name, const text * in_method_name, const text * in_message );

    stringex        _config_file_prefix;
    labels          _labels;
    interceptors    _interceptors;
    lock &          _monitor_lock;
    std::ostream *  _ostream_error;
    std::ostream *  _ostream_exception;
    std::ostream *  _ostream_information;
    std::ostream *  _ostream_progress;
    std::ostream *  _ostream_trace;
    std::ostream *  _ostream_warning;
    std::ostream *  _echo_ostream_error;
    std::ostream *  _echo_ostream_exception;
    std::ostream *  _echo_ostream_information;
    std::ostream *  _echo_ostream_progress;
    std::ostream *  _echo_ostream_trace;
    std::ostream *  _echo_ostream_warning;

}; // end of class logger_imp

//--------------------------------------

static const text this_class_name[]
    = "logger";

static const text default_instance_name[]
    = "logger_default";

static const char config_file_name[]
    = "logger_config.txt";

static regular_expression include_expression(
    "^[ \t]*include[ \t]+([^ \t]+)$", regular_expression::nocase );

static logger_imp * cached_default_instance = 0;

//--------------------------------------
//  internal public methods
//--------------------------------------

logger_imp::logger_imp()
  :
    _monitor_lock( lock_factory::get_singleton().create_lock() ),
    _ostream_error(             &std::cerr ),
    _ostream_exception(         &std::cerr ),
    _ostream_information(       &std::cout ),
    _ostream_progress(          &std::clog ),
    _ostream_trace(             &std::cout ),
    _ostream_warning(           &std::cerr ),
    _echo_ostream_error(        0 ),
    _echo_ostream_exception(    0 ),
    _echo_ostream_information(  0 ),
    _echo_ostream_progress(     0 ),
    _echo_ostream_trace(        0 ),
    _echo_ostream_warning(      0 )
{
    read_config_file();
}

//--------------------------------------

// virtual
logger_imp::~logger_imp()
{
    lock_factory::get_singleton().destroy_lock( _monitor_lock );
}

//--------------------------------------

// virtual
boolean 
logger_imp::is_echoing_information() const
{
    return internal_is_echoing_information();
}

//--------------------------------------

// virtual
const logger::labels &
logger_imp::get_labels() const
{
    return _labels;
}

//--------------------------------------

// virtual
void
logger_imp::add_label(
    const text * in_label )
{
    if ( in_label == 0 )
    {
        return;
    }
    guard monitor( _monitor_lock );
    _labels.insert( labels::value_type( in_label, false ) );
}

//--------------------------------------

// virtual
void
logger_imp::add_labels(
    const text * in_labels[] )
{
    if ( in_labels == 0 )
    {
        return;
    }
    guard monitor( _monitor_lock );
    for ( size_type index = 0; ; index++ )
    {
        const text * label = in_labels[index];        
        if ( label == 0 )
        {
            break;
        }
        _labels.insert( labels::value_type( label, false ) );
    }
}

//--------------------------------------

// virtual
boolean
logger_imp::is_including(
    const text * in_label ) const
{
    if ( in_label == 0 )
    {
        return false;
    }
    guard monitor( _monitor_lock );
    labels::const_iterator labiter = _labels.find( in_label );
    return (labiter != _labels.end()) && labiter->second;
}

//--------------------------------------

// virtual
void
logger_imp::exclude(
    const text * in_label )
{
    if ( in_label == 0 )
    {
        return;
    }
    guard monitor( _monitor_lock );
    labels::iterator labiter = _labels.find( in_label );
    if ( labiter != _labels.end() )
    {
        labiter->second = false;
    }
    else
    {
        _labels.insert( labels::value_type( in_label, false ) );
    }
}

//--------------------------------------

// virtual
void
logger_imp::include(
    const text * in_label )
{
    if ( in_label == 0 )
    {
        return;
    }
    guard monitor( _monitor_lock );
    labels::iterator labiter = _labels.find( in_label );
    if ( labiter != _labels.end() )
    {
        labiter->second = true;
    }
    else
    {
        _labels.insert( labels::value_type( in_label, true ) );
    }
}

//--------------------------------------

// virtual
void
logger_imp::set_config_file_prefix(
    const text * in_prefix )
{
    _config_file_prefix = in_prefix;
}

//--------------------------------------

// virtual
void
logger_imp::read_config_file()
{
    stringex filespec( _config_file_prefix );
    filespec += config_file_name;
    std::ifstream configfile( filespec );
    while ( configfile.good() && (!configfile.eof()) )
    {
        SPString unparsed;
        SPStringList parsed;
        configfile >> unparsed;
        unparsed.m( include_expression, parsed );
        if ( parsed.count() > 1 )
        {
            include( parsed[1] );
        }
    }
}

//--------------------------------------

// virtual
void
logger_imp::write_config_file()
{
    stringex filespec( _config_file_prefix );
    filespec += config_file_name;
    std::ofstream configfile( filespec );
    if ( configfile.good() )
    {
        for ( logger::labels::const_iterator
              labiter(   _labels.begin() );
              labiter != _labels.end();
              labiter++ )
        {
            if ( labiter->second )
            {
                configfile << "include " << labiter->first << std::endl;
            }
        }
    }
}

//--------------------------------------

// virtual
void
logger_imp::add_interceptor(
    interceptor & in_interceptor )
{
    static const text this_method_name[]
        = "add_interceptor(...)";

    guard monitor( _monitor_lock );
    if ( _interceptors.contains( in_interceptor ) )
    {
        internal_log_error( 
            this_class_name, this_method_name,
            "interceptor already registered" );
    } 
    else
    {
        _interceptors.push_back( in_interceptor );
    }
}

//--------------------------------------

// virtual
void
logger_imp::remove_interceptor(
    interceptor & in_interceptor )
{
    static const text this_method_name[]
        = "remove_interceptor(...)";

    guard monitor( _monitor_lock );
    if ( ! _interceptors.erase_first( in_interceptor ) )
    {
        internal_log_error( 
            this_class_name, this_method_name,
            "interceptor is not registered" );
    } 
}

//--------------------------------------

// virtual
void
logger_imp::echo_all_to(
    std::ostream * out_stream )
{
    guard monitor( _monitor_lock );
    internal_echo_all_to( out_stream );
}

//--------------------------------------

// virtual
void 
logger_imp::log_echo_information(
    const text * in_message )
{
    guard monitor( _monitor_lock );
    internal_log_echo_information( in_message );
}

//--------------------------------------

// virtual
void
logger_imp::log_error(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    guard monitor( _monitor_lock );
    internal_log_error(
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

// virtual
void
logger_imp::log_exception(
    const text *            in_class_name,
    const text *            in_method_name,
    const std::exception &  in_exception )
{
    guard monitor( _monitor_lock );
    internal_log_exception(
        in_class_name,
        in_method_name,
        in_exception );
}

//--------------------------------------

// virtual
void
logger_imp::log_information(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    guard monitor( _monitor_lock );
    internal_log_information(
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

// virtual
void
logger_imp::log_progress(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message,
    real         in_percentage )
{
    guard monitor( _monitor_lock );
    internal_log_progress(
        in_class_name,
        in_method_name,
        in_message,
        in_percentage );
}

//--------------------------------------

// virtual
void
logger_imp::log_trace(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    guard monitor( _monitor_lock );
    internal_log_trace(
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

// virtual
void
logger_imp::log_trace_entering(
    const text * in_class_name,
    const text * in_method_name )
{
    if ( is_including( in_class_name ) )
    {
        log_trace( in_class_name, in_method_name,
            "entering" );
    }
}

//--------------------------------------

// virtual
void
logger_imp::log_warning(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    guard monitor( _monitor_lock );
    internal_log_warning(
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------
//  internal private methods
//--------------------------------------

boolean 
logger_imp::internal_is_echoing_information() const
{
    return _echo_ostream_information != 0;
};

//--------------------------------------

void
logger_imp::internal_echo_all_to(
    std::ostream * in_ostream )
{
    _echo_ostream_error         = in_ostream;
    _echo_ostream_exception     = in_ostream;
    _echo_ostream_information   = in_ostream;
    _echo_ostream_progress      = in_ostream;
    _echo_ostream_trace         = in_ostream;
    _echo_ostream_warning       = in_ostream;
}

//--------------------------------------

void
logger_imp::internal_log(
    std::ostream &  out_stream,
    std::ostream *  out_stream_echo,
    category        in_category,
    const text *    in_prefix,
    const text *    in_class_name,
    const text *    in_method_name,
    const text *    in_message )
{
    stringex str( in_prefix );
    if ( in_class_name != 0 )
    {
        str += in_class_name;
        str += '.';
    }
    if ( in_method_name != 0 )
    {
        str += in_method_name;
        if ( in_message != 0 )
        {
            str += ": ";
        }
    }
    if ( in_message != 0 )
    {
        str += in_message;
    }
    internal_log_interceptors(
        in_category, str );

    out_stream << str << std::endl;
    if ( out_stream_echo != 0 )
    {
        *out_stream_echo << str << std::endl;
    }
}

//--------------------------------------

void
logger_imp::internal_log_interceptors(
    category        in_category,
    const text *    in_message )
{
    for ( interceptors::iterator
          i( _interceptors.begin() );
          i != _interceptors.end(); i++ )
    {
        i->intercept_log(
            in_category, in_message );
    }
}

//--------------------------------------

void
logger_imp::internal_log_echo_information(
    const text * in_message )
{
    internal_log_interceptors(
        category_information,
        in_message != 0 ? in_message : "" );

    if ( _echo_ostream_information != 0 )
    {
        if ( in_message != 0 )
        {
            *_echo_ostream_information << in_message;
        }
        *_echo_ostream_information << std::endl;
    }
}

//--------------------------------------

void
logger_imp::internal_log_error(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    internal_log(
        *_ostream_error,
        _echo_ostream_error,
        category_error,
        "!! ", // prefix
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

void
logger_imp::internal_log_exception(
    const text *            in_class_name,
    const text *            in_method_name,
    const std::exception &  in_exception )
{
    stringex message( in_exception.what() );
/*
    !!! was supported by the now deprecated exception subclass
    message += " thrown by ";
    message += in_exception.where();
*/
    message += " caught by ";

    internal_log(
        *_ostream_exception,
        _echo_ostream_exception,
        category_exception,
        "!!! ", // prefix
        in_class_name,
        in_method_name,
        message );
}

//--------------------------------------

void
logger_imp::internal_log_information(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    internal_log(
        *_ostream_information,
        _echo_ostream_information,
        category_information,
        0, // prefix
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

void
logger_imp::internal_log_progress(
    const text *    in_class_name,
    const text *    in_method_name,
    const text *    in_message,
    real            in_percentage )
{
    stream_string_o sso;
    sso << in_message << ' '
        << in_percentage << '%';

    internal_log(
        *_ostream_progress,
        _echo_ostream_progress,
        category_progress,
        0, // prefix
        in_class_name,
        in_method_name,
        sso.str().c_str() );
}

//--------------------------------------

void
logger_imp::internal_log_trace(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    internal_log(
        *_ostream_trace,
        _echo_ostream_trace,
        category_trace,
        "# ", // prefix
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------

void
logger_imp::internal_log_warning(
    const text * in_class_name,
    const text * in_method_name,
    const text * in_message )
{
    internal_log(
        *_ostream_warning,
        _echo_ostream_warning,
        category_warning,
        "! ", // prefix
        in_class_name,
        in_method_name,
        in_message );
}

//--------------------------------------
//  private methods
//--------------------------------------

// static
logger &
logger::create()
{
    return *(new logger_imp);
}

//--------------------------------------

// static
void
logger::destroy(
    logger & in_singleton )
{
    delete &static_cast<logger_imp&>(in_singleton);
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
