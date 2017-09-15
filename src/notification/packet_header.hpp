#if !defined(BEACH_NOTIFICATION_PACKET_HEADER)
#define      BEACH_NOTIFICATION_PACKET_HEADER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       packet_header.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <notification/channel_identifier.hpp>

#include <ostream>

namespace notification
{
    class packet_factory;
    using atoms::byte;

//--------------------------------------

#pragma pack(1)

/**
 *  The packet header class is designed so that specialized
 *  packet header subclasses can be defined and used 
 *  in place of the default packet header in packets.
 */
class packet_header
{
friend class packet_factory;    
public:

    typedef atoms::whole32 TypeId;
    typedef atoms::whole32 Index; 
    typedef atoms::whole32 Count; 
    typedef atoms::whole32 Check; 
    typedef atoms::whole32 data_size; 

    packet_header(
        TypeId              inTypeId,
        Index               inIndex,
        Count               inCount,
        data_size           inDataSize,
        channel_identifier  in_sender_id = 0 )
      :
        _dataSize(          inDataSize ),    
        _priority(          0 ),
        _sender_id(         in_sender_id ),
        _typeId(            inTypeId   ),
        _index(             inIndex    ),
        _count(             inCount    ),
        _check(             0          )
    {
        _headerSize = sizeof(*this);
        // ! SUBCLASSES MUST CHANGE THIS VALUE
    }

    channel_identifier  get_sender_id() const { return _sender_id;  }
    TypeId              getTypeId()     const { return _typeId;     }
    Index               getIndex()      const { return _index;      }
    Count               getCount()      const { return _count;      }
    Check               getCheck()      const { return _check;      }
    data_size           getHeaderSize() const { return _headerSize; }
    data_size           getDataSize()   const { return _dataSize;   }
    byte                getPriority()   const { return _priority;   }

    void                set_sender_id(  channel_identifier  in_id ) { _sender_id = in_id; }
    void                set_type_id(    TypeId              in_id ) { _typeId    = in_id; }

    friend std::ostream & operator <<(
        std::ostream &          inout_stream,
        const packet_header &    in_object )
    {
        inout_stream
            << "sender_id="     << in_object.get_sender_id().getMajor()
            << ':'              << in_object.get_sender_id().getMinor()
            << ",type_id="      << in_object.getTypeId()
            << ",index="        << in_object.getIndex()
            << ",count="        << in_object.getCount()
            << ",check="        << in_object.getCheck()
            << ",header_size="  << in_object.getHeaderSize()
            << ",data_size="    << in_object.getDataSize()
            << ",priority="     << in_object.getPriority();
    }

protected:

    packet_header( const packet_header & rhs )
      :
        _headerSize( rhs._headerSize ),
        _dataSize(   rhs._dataSize   ),
        _priority(   rhs._priority   ),
        _sender_id(  rhs._sender_id  ),
        _typeId(     rhs._typeId     ),
        _index(      rhs._index      ),
        _count(      rhs._count      ),
        _check(      rhs._check      )
    {}
    packet_header & operator =( const packet_header & rhs )
    {
        if ( this != &rhs )
        {
            _headerSize = rhs._headerSize;
            _dataSize   = rhs._dataSize;
            _priority   = rhs._priority;
            _sender_id  = rhs._sender_id;
            _typeId     = rhs._typeId;
            _index      = rhs._index;
            _count      = rhs._count;
            _check      = rhs._check;
        }
        return *this;
    } 

    // ! SUBCLASS CONSTRUCTORS MUST SET
    //   _headerSize USING sizeof(*this)

    data_size           _headerSize;
    data_size           _dataSize;
	byte                _priority;

private:

    channel_identifier  _sender_id;
    TypeId              _typeId;
    Index               _index;
    Count               _count;
    Check               _check;

}; // end of class packet_header

#pragma pack()

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_PACKET_HEADER
