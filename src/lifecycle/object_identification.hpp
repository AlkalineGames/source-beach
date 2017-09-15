#if !defined(BEACH_LIFECYCLE_OBJECT_IDENTIFICATION)
#define      BEACH_LIFECYCLE_OBJECT_IDENTIFICATION
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identification.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stringex.hpp>
#include <lifecycle/object_identifier.hpp>

namespace lifecycle
{
    using atoms::boolean;
    using atoms::stringex;

//--------------------------------------

/// abstract superclass for identification by id and/or name 
/**
 *  @note	design patterns applied:
 *				- Identity Field    [PEAA]
 *				- Name              [AP]
 */
class object_identification
{
public:

    typedef object_identifier   id_value;
    typedef stringex            name;

    static id_value             get_undefined_id();
    static const name &         get_undefined_name();

    virtual ~object_identification();

    /// @name accessor overrideables
    //@{    
    virtual id_value        get_id()    const;  ///< this level returns undefined id
    virtual const name &    get_name()  const;  ///< this level returns undefined name
    virtual boolean         has_id()    const;  ///< this level returns false
    virtual boolean         has_name()  const;  ///< this level returns false
    //@}
    
    boolean has_undefined_id() const
    {
        return has_id() && (get_id() == get_undefined_id());
    }
    boolean has_undefined_name() const
    {
        return has_name() && (get_name() == get_undefined_name());
    }
    boolean is_undefined() const
    {
        return has_undefined_id() || has_undefined_name();
    }
    /** undefined or non-existent (!has) values match any other,
        but then the other component (id or name) must match exactly */
    boolean matches(
        const object_identification &   rhs,
        boolean                         rhs_name_is_regex = false ) const;

    boolean regex_name_matches( const name & ) const;

    /// @name mutator overrideables
    //@{    
    virtual void set_id(        id_value );                 ///< this level does nothing
    virtual void set_id_name(   id_value, const name & );   ///< this level calls set_id(...), set_name(...)
    virtual void set_name(                const name & );   ///< this level does nothing
    //@}

    stringex  make_formatted_string( boolean in_use_regex = false ) const;
    void     parse_formatted_string( const stringex & ); ///< calls set_id_name(...)

protected:

    object_identification();
    object_identification( const object_identification & );

}; // end of class object_identification

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_OBJECT_IDENTIFICATION
