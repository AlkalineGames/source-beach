#if !defined(BEACH_ATOMS_MEMORY_DUMP)
#define      BEACH_ATOMS_MEMORY_DUMP
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       memory_dump.hpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>

namespace atoms
{

//--------------------------------------

class memory_dump
{
public:

    BEACH_ALLOCATION_OPERATORS

	memory_dump();

	void initialize( 
		const byte * mem, 
		whole memLength,
		boolean absoluteOffset = false );

	void initialize( 
		const char * mem, 
		whole memLength,
		boolean absoluteOffset = false )
	{ initialize( (byte*)mem, memLength, absoluteOffset ); }

	// returns true if there are more dump lines
	boolean more();

	// get a dump line
	stringex getLine();

	// start dumping from the beginning
	void    restart();

	// quick dump, returns a standard format dump
	static stringex dump( 
		const byte * mem, 
		whole memLength,
		boolean absoluteOffset = false );
	static stringex dump( 
		const char * mem, 
		whole memLength,
		boolean absoluteOffset = false )
	{ return dump( (byte*)mem, memLength, absoluteOffset ); }

private:

	const byte *  _memory;
	whole         _memoryLength;
	const byte *  _currentPosition;
	boolean       _absoluteOffset;
};

//--------------------------------------

}; // namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_MEMORYDUMP
