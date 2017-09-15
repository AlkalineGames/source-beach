#if !defined(BEACH_NOTIFICATION_DISTRIBUTED_COMMAND)
#define      BEACH_NOTIFICATION_DISTRIBUTED_COMMAND
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_distributed.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/stream_adapter_echo.hpp> // @@@ YUCK
#include <notification/channel.hpp>
#include <notification/command_packeted.hpp>

namespace notification
{
    using atoms::stream_adapter_echo; // @@@ YUCK

//--------------------------------------

/// ROMP distributed command, abstract superclass
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
class command_distributed
    : public command_packeted
{
friend class command_distributed_group;
public:

    enum { default_priority = command_packeted::default_priority + 20 };

    virtual ~command_distributed();

    virtual command_distributed * clone() const; ///< prototype method override

    // channel information
    //  populated by command_distributed_group::spawn();

    channel *           getChannel()     { return _channel;     }
    channel_identifier  getSource()      { return _source;      }
    channel_identifier  getDestination() { return _destination; }

    // serialization

    friend std::ostream & operator <<(
        std::ostream &, const command_distributed & );

    /// @warning @@@ THIS IS A REALLY CRAPPY WAY TO DO THIS
    friend stream_adapter_echo & operator <<(
        stream_adapter_echo & esa, const command_distributed & dc )
    {
        esa.get_stream_real() << dc;
        if ( esa.get_stream_echo() != 0 )
            *esa.get_stream_echo() << dc;
        return esa;
    }

protected:

    command_distributed( const text * in_name = 0 );
    command_distributed( const command_distributed & );

private:

    channel *           _channel;
    channel_identifier  _source;
    channel_identifier  _destination;
};

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_DISTRIBUTED_COMMAND
