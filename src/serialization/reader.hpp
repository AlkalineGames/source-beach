#if !defined(BEACH_SERIALIZATION_READER)
#define      BEACH_SERIALIZATION_READER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       reader.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace chain
{
    class context;
};

namespace serialization
{
    class selector;
    class serializable;
    class serializable_factory;
    class serializable_source;
    class serializable_spec;
    using atoms::integer;
    using atoms::integer32;
    using atoms::boolean;
    using atoms::real;
    using atoms::size_type;
    using atoms::stringex;
    using atoms::text;
    using atoms::whole;
    using atoms::whole16;
    using atoms::whole32;
    using atoms::whole64;
    using chain::context;

//--------------------------------------

/// interface to a serializable reader
/**
 *  This class is implemented as an abstract superclass
 *  rather than a pure interface so that subclasses do
 *  not have to override every operation. Subclass
 *  methods should not call any of these methods as
 *  they will generate errors if called.
 *
 *  The variations to the original design pattern for each
 *  method are: the additional selector parameter, the
 *  additional label parameter, and that override is not
 *  required.
 *
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */
class reader
{
public:

    virtual ~reader();

    const stringex & get_base_directory() const { return _base_directory; }

    /// @name Serializer operations
    //@{
    virtual boolean read_boolean(       const selector *, const text * in_label, boolean &  out_value );
    virtual boolean read_enum(          const selector *, const text * in_label, const text * names[], whole in_name_count, integer & out_value );
    virtual boolean read_integer(       const selector *, const text * in_label, integer &  out_value );
    virtual boolean read_integer32(     const selector *, const text * in_label, integer32 & out_value );
    virtual boolean read_ordered_real(  const selector *, const text * in_label, real       out_values[], whole in_count,   whole in_position_count = 0  );
    virtual boolean read_ordered_whole( const selector *, const text * in_label, whole      out_values[], whole in_count );
    virtual boolean read_real(          const selector *, const text * in_label, real &     out_value,   whole in_position_count = 0  );
    virtual boolean read_string(        const selector *, const text * in_label, stringex & out_string,  whole in_position_count = 0  );
    virtual boolean read_text(          const selector *, const text * in_label, text       out_text[], size_type in_text_length );
    virtual boolean read_whole(         const selector *, const text * in_label, whole &    out_value );
    virtual boolean read_whole16(       const selector *, const text * in_label, whole16 &  out_value );
    virtual boolean read_whole32(       const selector *, const text * in_label, whole32 &  out_value );
    virtual boolean read_whole64(       const selector *, const text * in_label, whole64 &  out_value );

    virtual boolean read_object(        const selector *, const text * in_label, serializable * & out_object, whole in_position_count = 0  );
    virtual boolean read_root(          serializable * & out_root, serializable_source * in_source = 0 );
    virtual boolean read_root( context &, serializable * & out_root, serializable_source * in_source = 0 );
    //@}

    /// @name Serializer extensions
    //@{
    virtual boolean read_all(           serializable & );
    virtual boolean read_spec(          const selector *, const text * in_label, serializable_spec & out_spec );
    virtual boolean read_state(         serializable & out_object );
    virtual boolean read_statement(     serializable & out_object );
    virtual boolean read_value(         const selector *, const text * in_label, serializable & out_value );

    virtual void    add_dependency(     serializable & );
    virtual boolean has_field(          const selector *, const text * in_label );
    //@}

    // @@@ SHOULD BE MADE INTO A GENERIC PROPERTIES
    //  ... get_properties() const
    virtual boolean is_importing() const;

protected:

    reader( const stringex * in_base_directory = 0 );

private:

    stringex _base_directory;

};  // end of class reader

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_READER
