#if !defined(BEACH_TAXONOMY_PROPERTY_GROUP)
#define      BEACH_TAXONOMY_PROPERTY_GROUP
//----------------------------------------------------------
//  Copyright 2002-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       property_group.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <collection/ref_map_by_string.hpp>

namespace taxonomy
{
    class property_group;
    using atoms::boolean;
    using atoms::pointer;
    using atoms::real;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;

//--------------------------------------

typedef whole property_index;
typedef real Scalar; ///< @deprecated

//--------------------------------------

/// surrogate to a property provided by a property_group
/**
 *  this also serves as an iterator.
 *
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */     
class property_surrogate
//    : public property
//          @@@ REFACTOR TO IMPLEMENT property INTERFACE
{
friend class property_catalog;
friend class property_group;
public:

    property_surrogate()
      :
        _group( 0 ),
        _index( 0 )
    {}
    property_surrogate(
        const property_surrogate & rhs )
      :
        _group( rhs._group ),
        _index( rhs._index )
    {}
    ~property_surrogate()
    {}

    void                    first();
    void                    last();
    void                    next();
    void                    previous();
    boolean                 is_valid()  const { return _index != 0; }
    const text *            get_name()  const;
    const property_group *  get_group() const; ///< returns 0 if not a group
    stringex                get_value() const;
    pointer                 get_value_pointer() const;
    real                    get_value_scalar() const;
    boolean                 set_value(
        const text *            in_value,
        stringex *              out_error_message );
        ///< out_error_message not set if _group == 0
    boolean                 set_value_pointer(
        pointer                 in_value,
        stringex *              out_error_message );
        ///< out_error_message not set if _group == 0

private:
    
    property_surrogate(
        property_group & in_group )
      :
        _group( &in_group )
    {
        first();
    }
    property_surrogate(
        property_group & in_group,
        property_index   in_index )
      :
        _group( &in_group ),
        _index( in_index )
    {}
    property_group * _group;
    property_index   _index;

}; // end of class property_surrogate

//--------------------------------------

/// abstract superclass for objects that provide properties
/**
 *  @note   design patterns applied:
 *              - Iterator [GoF]
 */     
class property_group
{
friend class property_surrogate;
public:

    const property_surrogate find_property_const(
        const text * in_name ) const
    {
        property_index index = get_property_index( in_name );
        return property_surrogate( 
            const_cast<property_group&>(*this), index );
    }
    property_surrogate find_property(
        const text * in_name )
    {
        property_index index = get_property_index( in_name );
        return property_surrogate( *this, index );
    }
    const property_surrogate get_properties_const() const
    {
        return property_surrogate( 
            const_cast<property_group&>(*this) );
    }
    property_surrogate get_properties()
    {
        return property_surrogate( *this );
    }

    /// @name intended overrideables
    //@{
    virtual whole           get_property_count() const; ///< returns 0 at this level
    virtual const text **   get_property_names() const; ///< returns 0 at this level
    virtual stringex        get_property_value() const; ///< returns "n properties" (n==count) at this level
    //@}
    
    virtual ~property_group(); ///< @@@ MUST BE PUBLIC FOR collection::TypedMap<T>

protected:

    property_group();
      
    /// @name intended overrideables, do nothing at this level
    //@{
    virtual const property_group *  get_property_group( property_index ) const;
    virtual stringex                get_property_value( property_index ) const;
    virtual boolean                 set_property_value( ///< returns true if successful
        property_index                  in_index,
        const text *                    in_value,
        stringex *                      out_error_message );

    virtual pointer                 get_property_value_pointer( property_index ) const; /// @deprecated
    virtual real                    get_property_value_scalar(  property_index ) const; /// @deprecated

    virtual boolean                 set_property_value_pointer( /// @deprecated
        property_index                  in_index,
        pointer                         in_value,
        stringex *                      out_error_message );
    //@}

    /// @name utilities for subclasses
    //@{
    const text *    get_boolean_text( boolean ) const;

    boolean         set_boolean_value(  ///< returns false if input text is invalid
        const text *    in_text,
        boolean &       out_value,
        stringex *      out_error_message ) const;

    void            set_error_cannot_change_property(
        stringex *      out_error_message ) const;
    void            set_error_invalid_property_index(
        stringex *      out_error_message ) const;
    //@}
    
private:
    
    property_index get_property_index(
        const text * in_name ) const;
    
}; // end of class property_group

//--------------------------------------

typedef collection::ref_map_by_string<property_group> 
    property_groups;

//--------------------------------------

inline
void
property_surrogate::first()
{
    if (   (_group != 0)
        && (_group->get_property_count() > 0) )
    {
        _index = 1;
    }
    else
    {
        _index = 0;
    }
};

//--------------------------------------

inline
void
property_surrogate::last()
{
    if ( _group != 0 )
    {
        _index = _group->get_property_count();
    }
    else
    {
        _index = 0;
    }
};

//--------------------------------------

inline
void
property_surrogate::next()
{
    if (   (_group != 0)
        && (_index != 0)
        && (_index < _group->get_property_count()) )
    {
        ++_index;
    }
    else
    {
        _index = 0;
    }
};

//--------------------------------------

inline
void
property_surrogate::previous()
{
    if (   (_group != 0)
        && (_index >  0)
        && (_index <= _group->get_property_count()) )
    {
        ++_index;
    }
    else
    {
        _index = 0;
    }
};

//--------------------------------------

inline
const text *
property_surrogate::get_name() const
{
    if (   (_group != 0)
        && (_index >  0)
        && (_index <= _group->get_property_count()) )
    {
        return _group->get_property_names()[_index-1];
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

inline
const property_group *
property_surrogate::get_group() const
{
    if ( _group != 0 )
    {
        return _group->get_property_group( _index );
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

inline
stringex
property_surrogate::get_value() const
{
    if ( _group != 0 )
    {
        return _group->get_property_value( _index );
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

inline
pointer
property_surrogate::get_value_pointer() const
{
    if ( _group != 0 )
    {
        return _group->get_property_value_pointer( _index );
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

inline
boolean
property_surrogate::set_value(
    const text * in_value,
    stringex *   out_error_message )
{
    if ( _group != 0 )
    {
        return _group->set_property_value( 
            _index, in_value, out_error_message );
    }
    else
    {
        return false;
    }
}

//--------------------------------------

inline
boolean
property_surrogate::set_value_pointer(
    pointer     in_value,
    stringex *  out_error_message )
{
    if ( _group != 0 )
    {
        return _group->set_property_value_pointer( 
            _index, in_value, out_error_message );
    }
    else
    {
        return false;
    }
}

//--------------------------------------

inline
real
property_surrogate::get_value_scalar() const
{
    if ( _group != 0 )
    {
        return _group->get_property_value_scalar( _index );
    }
    else
    {
        return 0;
    }
}

//--------------------------------------

}; // end of namespace taxonomy

//----------------------------------------------------------
#endif // BEACH_TAXONOMY_PROPERTY_GROUP
