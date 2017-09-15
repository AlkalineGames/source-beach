//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       buffer.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/buffer.hpp> // this header

#include <atoms/allocation.hpp>

#include <cstring>

namespace atoms
{

//--------------------------------------
//  public methods
//--------------------------------------

buffer::buffer( unsigned long size, bool saveHistory )
: _save_history(saveHistory)
{
	_buffer_size = size;
	_buffer = ( size ? (new BEACH_ALLOCATION unsigned char [size]) : 0 );
	_get_pos = _buffer;
	_add_pos = _buffer;
}

//--------------------------------------

buffer::buffer( const buffer & rhs )
{
	_buffer = 0;
    *this = rhs;
}

//--------------------------------------

buffer::~buffer()
{
	BEACH_DELETE_WITHOUT_DESTRUCT(_buffer);
	_buffer = 0;
}

//--------------------------------------

buffer & 
buffer::operator = ( const buffer & rhs )
{
    if ( &rhs == this )
        return *this;

    _save_history = rhs._save_history;
    copyBuffer( rhs, 0, _save_history );

    return *this;
}

//--------------------------------------

bool 
buffer::isEmpty() const
{
	return ( _get_pos == _add_pos ) ? true : false;
}

//--------------------------------------

void 
buffer::clear()
{
	_get_pos = _buffer;
	_add_pos = _buffer;
}

//--------------------------------------

unsigned long 
buffer::appendData( const unsigned char * bytes, unsigned long length )
{
    // ensure pointers are reset to beginning of buffer
    if ( !_save_history && isEmpty() )
        clear();

    // append the data
	if ( length )
	{
        ensureAvailableWriteSpace( length, true );
        unsigned char * p = getWritePosition();
        ::memcpy( p, bytes, length );
        advanceWritePosition( length );
    }
    return length;
}

//--------------------------------------

unsigned long 
buffer::appendData( const buffer & data )
{ 
    return appendData( data.getReadPosition(), data.getDataLength() );
}

//--------------------------------------

unsigned long 
buffer::getData( unsigned char * bytes, unsigned long length )
{
	unsigned long len = getDataLength();
    if ( len > length )
        len = length;

    if ( len < 1 )
        return 0;

    unsigned char * p = getReadPosition();
    ::memcpy( bytes, p, len );
    advanceReadPosition( len );

    return len;
}

//--------------------------------------

unsigned long
buffer::getAvailableWriteSpace()
{
    unsigned long usedSpace = (_buffer ? (_add_pos - _buffer) : 0);
    unsigned long availableSpace = (_buffer ? (_buffer_size - usedSpace) : 0);
    return availableSpace;
}

//--------------------------------------

void 
buffer::ensureAvailableWriteSpace( unsigned long length, bool optimize )
{
    unsigned long usedSpace = (_buffer ? (_add_pos - _buffer) : 0);
    unsigned long availableSpace = (_buffer ? (_buffer_size - usedSpace) : 0);
    if ( availableSpace < length )
    {
        unsigned long growSize = usedSpace + length;
        if ( optimize && _buffer )
            growSize *= 2;
        growBuffer( growSize );
    }
}

//--------------------------------------

void 
buffer::advanceWritePosition( long length )
{
    if ( !_buffer )
        return;

    _add_pos += length;
    if ( _add_pos > (_buffer + _buffer_size) )
    {
        _add_pos = _buffer + _buffer_size;
    }
    if ( _add_pos < _get_pos )
        _add_pos = _get_pos;
}

//--------------------------------------

void 
buffer::advanceReadPosition( long length )
{
    if ( !_buffer )
        return;

    _get_pos += length; 
    if ( _get_pos > _add_pos ) 
        _get_pos = _add_pos;
    if ( _get_pos < _buffer )
        _get_pos = _buffer;
}

//--------------------------------------
//  private methods
//--------------------------------------

void 
buffer::growBuffer( unsigned long new_size )
{
	if ( new_size <= _buffer_size )
		return;

    copyBuffer( *this, new_size, _save_history );
}

//--------------------------------------

void 
buffer::copyBuffer( 
    const buffer & fromBuf, 
    unsigned long new_size,
    bool saveHistory )
{
    if ( new_size < 0 )
        new_size = 1;

    unsigned char * start_pos = (saveHistory ? fromBuf._buffer : fromBuf._get_pos);
    unsigned long copy_length = (fromBuf._add_pos - start_pos);
    if ( new_size < copy_length )
        new_size = copy_length;
    unsigned char * new_data = new unsigned char [new_size];
    if ( copy_length > 0 )
        ::memcpy( new_data, start_pos, copy_length );

    BEACH_DELETE_WITHOUT_DESTRUCT(_buffer);
    _buffer_size = new_size;
	_buffer = new_data;
	_get_pos = _buffer + (fromBuf._get_pos - start_pos);
	_add_pos = _buffer + copy_length;
}

//--------------------------------------

bool 
buffer::operator == ( const buffer & rhs ) const
{
    if ( this == &rhs )
    {
        return true;
    }
    unsigned char * ptr1 = this->getReadPosition();
    unsigned long len1 = this->getDataLength();
    unsigned char * ptr2 = rhs.getReadPosition();
    unsigned long len2 = rhs.getDataLength();

    if ( len1 != len2 )
    {
        return false;
    }
    if ( !len1 )
    {
        return true;
    }
    int rc = ::memcmp( ptr1, ptr2, len1 );
    return (rc ? false : true);
}

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
// (end of file)
