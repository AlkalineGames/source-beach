#if !defined(BEACH_LIFECYCLE_LOGGER)
#define      BEACH_LIFECYCLE_LOGGER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       logger.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <lifecycle/lifecycle_manager.hpp>

#include <exception>
#include <ostream>
#include <map>

namespace lifecycle
{
    using atoms::boolean;
    using atoms::real;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// interface for a logger of diagnostic messages
/**
 *  This class is coded as a public interface with an
 *  internal or library-bound implementation subclass.
 *  Linkage is only required for code that calls the
 *  static methods.
 *
 *  @note   design patterns applied:
 *              - Diagnostics Logger    [PLoP3]
 *              - Mediator              [GoF]
 *              - Replaceable Singleton [WF]
 *              - Singleton             [GoF]
 */
class logger
{
friend class lifecycle_manager;
public:

    enum category
    {
        no_category,
        category_error,
        category_exception,
        category_information,
        category_progress,
        category_trace,
        category_warning,
        category_count
    };
    typedef std::map<stringex,boolean> labels;

    class interceptor ///< interface
    {
    public:
        virtual void intercept_log(
            category, const stringex & in_message ) = 0;
    };

    /// @name linkage required
    //@{
    static logger & get_singleton()
    {
        return lifecycle_manager::acquire_singleton().get_logger();
    }
    //@}

    virtual boolean is_echoing_information() const = 0;

    /// @name logging selection, should be monitor synchronized
    //@{
    virtual const labels &  get_labels() const = 0;
    virtual boolean         is_including(           const text * in_label ) const = 0;
    virtual void            add_label(              const text * in_label ) = 0;
    virtual void            add_labels(             const text * in_labels[] ) = 0; ///< final pointer must be 0
    virtual void            exclude(                const text * in_label ) = 0;
    virtual void            include(                const text * in_label ) = 0;
    virtual void            set_config_file_prefix( const text * ) = 0;
    virtual void            read_config_file() = 0;
    virtual void            write_config_file() = 0;
    //@}

    /// @name echoing/interception, should be monitor synchronized 
    //@{
    virtual void add_interceptor(       interceptor & )     = 0;
    virtual void remove_interceptor(    interceptor & )     = 0;
    virtual void echo_all_to(           std::ostream * )    = 0;
    //@}

    /// @name logging operations, should be monitor synchronized
    //@{
    virtual void log_echo_information(
        const text * in_message )       = 0;

    virtual void log_error(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message )       = 0;

    virtual void log_exception(
        const text * in_class_name,
        const text * in_method_name,
        const std::exception & e )      = 0;

    virtual void log_information(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message )       = 0;

    virtual void log_progress(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message,
        real         in_percentage )    = 0;

    virtual void log_trace(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message )       = 0;

    virtual void log_trace_entering( ///< traces only if class name is included
        const text * in_class_name,
        const text * in_method_name )   = 0;

    virtual void log_warning(
        const text * in_class_name,
        const text * in_method_name,
        const text * in_message )       = 0;
    //@}

protected:

    static void set_singleton( logger & in_singleton )
    {
        lifecycle_manager::acquire_singleton().set_logger(
            in_singleton );
    }

private:

    /// @name only by lifecycle_manager
    //@{
    static logger & create();
    static void     destroy( logger & );
    //@}
    
}; // end of class logger

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_LOGGER
