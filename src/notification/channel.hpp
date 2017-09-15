#if !defined(BEACH_NOTIFICATION_CHANNEL)
#define      BEACH_NOTIFICATION_CHANNEL
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       channel.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/string.hpp>
#include <notification/channel_identifier.hpp>
#include <notification/observable_imp.hpp>

namespace notification
{
    class packet;

//--------------------------------------

class channel
    : public virtual observable_imp
{
public:

    typedef channel_identifier Identity;

    channel( Identity );
    virtual ~channel();

    Identity getId() const { return _id; }

    virtual String getLocationName( Identity ) const; // returns ""
    //  override this to provide informative names for locations

    // communication overrideables (passes to packet handler)

    virtual void receive( const packet & ); // anonymous
    virtual void receive( const packet &, Identity inSource );
    virtual void receive( const packet &, Identity inSource, Identity inDestination );

    // ... (these do nothing)

    virtual void send( // multiplex
        const packet &,
        boolean     in_be_guaranteed = false );

    virtual void send(
        const packet &,
        Identity    in_destination,
        boolean     in_be_guaranteed = false );

protected:

    // change identification

    void setId( Identity inId ) { _id = inId; }

private: 
    
    // copy operations not implemented
    channel(              const channel & );
    channel & operator =( const channel & );

    Identity _id;

}; // end of class channel

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_CHANNEL
