#if !defined(BEACH_ATOMS_BUFFER)
#define      BEACH_ATOMS_BUFFER
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       buffer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>

namespace atoms
{

//--------------------------------------

class buffer
{
public:

    BEACH_ALLOCATION_OPERATORS

	buffer( unsigned long size = 0, bool saveHistory = false );
	buffer( const buffer & rhs );
	~buffer();

    // copy a buffer
    buffer & operator = ( const buffer & rhs );

    // -- check for empty/full buffer --
	bool isEmpty() const;

    // -- delete all data in the buffer --
    void clear();

    // -- adding data to the buffer --
    unsigned long appendData( const unsigned char * bytes, unsigned long length );
    unsigned long appendData( const char * bytes, unsigned long length ) 
           { return appendData( (unsigned char *)bytes, length ); }
    unsigned long appendData( const buffer & data );

	// -- retrieving buffer data --
	unsigned long getData( unsigned char * bytes, unsigned long length );
	unsigned long getDataLength() const // bytes of data avalable to get
           { return (_add_pos - _get_pos); }
    void restart() { _get_pos = _buffer; } // read from beginning again

    // direct buffer access for adding data
    unsigned long getAvailableWriteSpace();
    void ensureAvailableWriteSpace( unsigned long length, bool optimize = false );
    unsigned char * getWritePosition() const { return _add_pos; }
    void advanceWritePosition( long length );
    unsigned long getBufferSize() const { return _buffer_size; }

    // direct buffer access for reading data
    unsigned char * getReadPosition() const { return _get_pos;  }
    void advanceReadPosition( long length );

    // get actual buffer
    unsigned char * getBuffer() const { return _buffer; }

    // compare the contents of two buffers
    bool operator == ( const buffer & rhs ) const;
    bool operator != ( const buffer & rhs ) const { return (*this == rhs) ? false : true; }

private:

	void growBuffer( unsigned long new_length );
    void copyBuffer( const buffer & fromBuf, 
                     unsigned long new_size,
                     bool saveHistory );

	unsigned char * _buffer;        // pointer to allocated buffer
	unsigned long   _buffer_size;
	unsigned char * _get_pos;
	unsigned char * _add_pos;
    bool _save_history;
};

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_BUFFER
