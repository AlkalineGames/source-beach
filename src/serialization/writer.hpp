#if !defined(BEACH_SERIALIZATION_WRITER)
#define      BEACH_SERIALIZATION_WRITER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       writer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace atoms
{
    class stringex;
};

namespace chain
{
    class context;
};

namespace serialization
{
    class selector;
    class serializable;
    class serializable_spec;
    using atoms::integer;
    using atoms::integer32;
    using atoms::boolean;
    using atoms::real;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;
    using atoms::whole16;
    using atoms::whole32;
    using atoms::whole64;
    using chain::context;

//--------------------------------------

/// interface for serializable writers
/**
 *  This class is implemented as an abstract superclass
 *  rather than a pure interface so that subclasses do not
 *  have to override every operation. Subclass methods
 *  should not call any of these methods as they will log
 *  errors if called. 
 *
 *  The variations to the original design pattern for each
 *  method are: the additional selector parameter, the
 *  additional label parameter, and that override is not
 *  required. 
 *
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */      
class writer
{
public:

    virtual ~writer();

    /// @name Serializer operations
    //@{
    virtual void write_boolean(         const selector *, const text * in_label, boolean );
    virtual void write_enum(            const selector *, const text * in_label, const text * names[], whole in_name_count, integer );
    virtual void write_integer(         const selector *, const text * in_label, integer );
    virtual void write_integer32(       const selector *, const text * in_label, integer32 );
    virtual void write_ordered_real(    const selector *, const text * in_label, const real[],  whole in_count );
    virtual void write_ordered_whole(   const selector *, const text * in_label, const whole[], whole in_count );
    virtual void write_real(            const selector *, const text * in_label, real );
    virtual void write_string(          const selector *, const text * in_label, const stringex & );
    virtual void write_text(            const selector *, const text * in_label, const text * in_text );
    virtual void write_whole(           const selector *, const text * in_label, whole );
    virtual void write_whole16(         const selector *, const text * in_label, whole16 );
    virtual void write_whole32(         const selector *, const text * in_label, whole32 );
    virtual void write_whole64(         const selector *, const text * in_label, whole64 );

    virtual void write_object(          const selector *, const selector * in_identity_selector, const text * in_label, serializable * ); ///< variation: object can be null
    virtual void write_root(            const selector *, serializable & );
    virtual void write_root( context &, const selector *, serializable & );
    //@}

    /// @name Serializer extensions
    //@{
    virtual void write_all(             const selector *, serializable & );
    virtual void write_spec(            const selector *, const text * in_label, const serializable_spec & );
    virtual void write_value(           const selector *, const selector * in_member_selector, const text * in_label, serializable & in_value );
    virtual boolean write_newline(); ///< returns false if it does nothing, @@@ KIND OF A HACK UNTIL WE USE XML
    //@}
   
protected:
 
    writer();

};  // end of class writer

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_WRITER
