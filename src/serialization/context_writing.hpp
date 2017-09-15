#if !defined(BEACH_SERIALIZATION_CONTEXT_WRITING)
#define      BEACH_SERIALIZATION_CONTEXT_WRITING
//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       context_writing.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/context.hpp>

namespace serialization
{
    class selector;
    using chain::context;
    using chain::context_linked;

//--------------------------------------

/// context for write operatons
/**
 *  @note   design patterns applied:
 *              - Encapsulate Context [PLoP5]
 */
class context_writing
    : public context_linked
{
public:

    struct class_id_substitution
    {    
        class_identity _id_original;
        class_identity _id_substitute;
    };
    static class_identity acquire_class_id();
        ///< @@@ should templatize this method

    /// @name subclassing protocol
    //@{
    static const context_writing * cast_from( const linked & in_linked )  { return context_linked::cast_from   <context_writing>( in_linked ); }
    static       context_writing * cast_from_nc(    linked & in_linked )  { return context_linked::cast_from_nc<context_writing>( in_linked ); }
    static const context_writing * find_in(  const context & in_context ) { return context_linked::find_in     <context_writing>( in_context ); }
    static       context_writing * find_in_nc(     context & in_context ) { return context_linked::find_in_nc  <context_writing>( in_context ); }
    //@}

    context_writing();

    const class_id_substitution &   get_class_id_substitution() const { return _class_id_substitution; }
    void                            set_class_id_substitution(
        class_identity                          in_id_original,
        class_identity                          in_id_substitute )
    {
        _class_id_substitution._id_original   = in_id_original;
        _class_id_substitution._id_substitute = in_id_substitute;
    }
    const selector *    get_selector_nested() const { return _selector_nested; }
    void                set_selector_nested( const selector * sel )
    {
        _selector_nested = sel;
    }

private:

    /// @name copy operations not implemented
    //@{
    context_writing(              const context_writing & );
    context_writing & operator =( const context_writing & );
    //@}

    class_id_substitution   _class_id_substitution;
    const selector *        _selector_nested;
    
}; // end of class context_writing

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_CONTEXT_WRITING
