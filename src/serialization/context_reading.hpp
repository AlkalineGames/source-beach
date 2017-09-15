#if !defined(BEACH_ATOMS_CONTEXT_READING)
#define      BEACH_ATOMS_CONTEXT_READING
//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       context_reading.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/context.hpp>
#include <notification/channel_identifier.hpp>

namespace serialization
{
    class selector;
    using chain::context;
    using chain::context_linked;
    using notification::channel_identifier;

//--------------------------------------

/// context for write operatons
/**
 *  @note   design patterns applied:
 *              - Encapsulate Context [PLoP5]
 */
class context_reading
    : public context_linked
{
public:

    static class_identity acquire_class_id();
        ///< @@@ should templatize this method

    /// @name subclassing protocol
    //@{
    static const context_reading * cast_from( const linked & in_linked )  { return context_linked::cast_from   <context_reading>( in_linked ); }
    static       context_reading * cast_from_nc(    linked & in_linked )  { return context_linked::cast_from_nc<context_reading>( in_linked ); }
    static const context_reading * find_in(  const context & in_context ) { return context_linked::find_in     <context_reading>( in_context ); }
    static       context_reading * find_in_nc(     context & in_context ) { return context_linked::find_in_nc  <context_reading>( in_context ); }
    //@}

    context_reading();

    const channel_identifier *  get_sender_id() const { return _sender_id; }
    void                        set_sender_id( const channel_identifier * in_sender_id )
    {
        _sender_id = in_sender_id;
    }

private:

    /// @name copy operations not implemented
    //@{
    context_reading(              const context_reading & );
    context_reading & operator =( const context_reading & );
    //@}

    const channel_identifier * _sender_id;
    
}; // end of class context_reading

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_ATOMS_CONTEXT_READING
