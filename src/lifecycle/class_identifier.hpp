#if !defined(BEACH_LIFECYCLE_CLASS_IDENTIFIER)
#define      BEACH_LIFECYCLE_CLASS_IDENTIFIER
//----------------------------------------------------------
//	Copyright 2004-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_identifier.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace lifecycle
{
    using atoms::text;
    using atoms::whole16;
        
//--------------------------------------

/// offset where dynamically generated class id values start

enum { class_identifier_generation_offset = 33000 };

/// increment between newly generated class id values

enum { class_identifier_generation_increment = 100 };

//--------------------------------------

/// primitive type for class identification

typedef whole16 class_identifier;
/*
    @@@ COMPLETE ALL THIS STUFF IF/WHEN NEEDED
class class_identifier
{
public:

    typedef whole16 value;

    class_identifier( value in_value = 0 )
      :
        _value( in_value )
    {}
    class_identifier( const text * in_name )
    {
        *this = in_name;
    }
    operator const text *() const { return get_name(); }
    operator value()        const { return _value; }

    const text *    get_name()  const;
    value           get_value() const { return _value; }

    class_identifier & operator =( const text * in_name )
    {
        set_name( in_name );
        return *this;
    }
    class_identifier & operator =( value        in_value )
    {
        _value = in_value;
        return *this;
    }

    friend std::ostream & operator <<(
        std::ostream & ostr, const class_identifier & id )
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
 
}; // end of class class_identifier
*/
//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_CLASS_IDENTIFIER
