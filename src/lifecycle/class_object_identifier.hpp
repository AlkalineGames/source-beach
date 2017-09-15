#if !defined(BEACH_LIFECYCLE_CLASS_OBJECT_IDENTIFIER)
#define      BEACH_LIFECYCLE_CLASS_OBJECT_IDENTIFIER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_object_identifier.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>

#include <ostream>

namespace lifecycle
{
    using atoms::boolean;
    using atoms::boolean;
    using atoms::whole;
    using atoms::whole8;
    using atoms::whole16;
    using atoms::whole32;
    using atoms::whole64;

//--------------------------------------

/// template for a combined class and object identifier

template <class CID, class OID>
class class_object_identifier
{
public:

    typedef CID class_id;
    typedef OID object_id;

    class_object_identifier( atoms::no_init_type ) {}
    class_object_identifier( CID inclass_id = 0, OID inobject_id = 0 )
      : _class_id( inclass_id ), _object_id( inobject_id ) {}
    ~class_object_identifier() {}

    int operator ==( const class_object_identifier & rhs ) const
    {   return (_class_id == rhs._class_id) && (_object_id == rhs._object_id); }

    int operator !=( const class_object_identifier & rhs ) const
    {   return (_class_id != rhs._class_id) || (_object_id != rhs._object_id); }

    CID     get_class_id()  const { return _class_id;  }
    OID     get_object_id() const { return _object_id; }
    boolean is_zero()       const { return (_class_id == 0) && (_object_id == 0); }

    class_object_identifier & operator =(
        const class_object_identifier & rhs )
    {
        if ( &rhs != this )
        {
            _class_id  = rhs._class_id;
            _object_id = rhs._object_id;
        }
        return *this;
    }    
    class_object_identifier & operator ++()
    {   
		++_object_id;
		return *this;
	}
    void set_class_id(  CID inclass_id  ) { _class_id  = inclass_id;  }
    void set_object_id( OID inobject_id ) { _object_id = inobject_id; }

    friend std::ostream & operator <<(
        std::ostream & ostr, const class_object_identifier & id )
    {
        ostr << whole(id._class_id) << '/' // @@@ MAY TRUNCATE LARGE VALUES
             << whole(id._object_id);      // ...ditto...
        return ostr;
    }

private:

    CID _class_id;
    OID _object_id;

}; // end of template class class_object_identifier

//--------------------------------------

typedef class_object_identifier<whole8,whole8>   few_few_identifier;
typedef class_object_identifier<whole8,whole16>  few_several_identifier;
typedef class_object_identifier<whole8,whole32>  few_many_identifier;
typedef class_object_identifier<whole8,whole64>  few_vast_identifier;
typedef class_object_identifier<whole16,whole8>  several_few_identifier;
typedef class_object_identifier<whole16,whole16> several_several_identifier;
typedef class_object_identifier<whole16,whole32> several_many_identifier;
typedef class_object_identifier<whole16,whole64> several_vast_identifier;
typedef class_object_identifier<whole32,whole8>  many_few_identifier;
typedef class_object_identifier<whole32,whole16> many_several_identifier;
typedef class_object_identifier<whole32,whole32> many_many_identifier;
typedef class_object_identifier<whole32,whole64> many_vast_identifier;
typedef class_object_identifier<whole64,whole8>  vast_few_identifier;
typedef class_object_identifier<whole64,whole16> vast_several_identifier;
typedef class_object_identifier<whole64,whole32> vast_many_identifier;
typedef class_object_identifier<whole64,whole64> vast_vast_identifier;

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_CLASS_OBJECT_IDENTIFIER
