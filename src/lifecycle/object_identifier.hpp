#if !defined(BEACH_LIFECYCLE_OBJECT_IDENTIFIER)
#define      BEACH_LIFECYCLE_OBJECT_IDENTIFIER

//----------------------------------------------------------
//	Copyright 2004-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       object_identifier.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

//--------------------------------------

namespace lifecycle
{
        
//--------------------------------------

// primitive type for object identification
/**
 * This type is largest possible size for an object identifier.
 * The actual object identifier type used by a class may be a
 * value-compatible type smaller than this.
 */
typedef atoms::whole64 object_identifier;

/*
    @@@ COMPLETE ALL THIS STUFF IF/WHEN NEEDED
object object_identifier
{
public:

    typedef whole64 value;

    object_identifier( value in_value = 0 )
      :
        _value( in_value )
    {}
    object_identifier( const text * in_name )
    {
        *this = in_name;
    }
    operator const text *() const { return get_name(); }
    operator value()        const { return _value; }

    const text *    get_name()  const;
    value           get_value() const { return _value; }

    object_identifier & operator =( const text * in_name )
    {
        set_name( in_name );
        return *this;
    }
    object_identifier & operator =( value        in_value )
    {
        _value = in_value;
        return *this;
    }

    friend std::ostream & operator <<(
        std::ostream & ostr, const object_identifier & id )
    {
        if ( id.getEnum() < EnumTypeCount )
        {
            ostr << id.getName();
        }
        else
        {
            ostr << whole(id.getValue());
        }
        return ostr;
    }

private:

    value _value;
 
}; // end of object object_identifier
*/
//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: object_identifier.hpp,v $
// Revision 1.3  2006/12/06 23:37:15  cat
// fixed usings
//
// Revision 1.2  2005/08/30 05:11:03  cat
// renamed sanddune to beach
//
// Revision 1.1  2004/07/10 20:55:04  cat
// creation
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_OBJECT_IDENTIFIER
