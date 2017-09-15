//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       memory_dump.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include <atoms/memory_dump.hpp> // this header

#include <cstdio>

namespace atoms
{

//--------------------------------------

memory_dump::memory_dump()
: _memory(0), _memoryLength(0),
  _currentPosition(0), _absoluteOffset(false)
{
}

//--------------------------------------

void memory_dump::initialize( 
        const byte * mem, 
        whole memLength,
        boolean absoluteOffset )
{
    _memory          = mem;
    _memoryLength    = memLength;
    _currentPosition = mem;
    _absoluteOffset  = absoluteOffset;
}

//--------------------------------------

boolean memory_dump::more()
{
    if ( !_memory )
        return false;

    const byte * end = _memory + _memoryLength;
    if ( _currentPosition < end )
        return true;

    return false;
}

//--------------------------------------

stringex memory_dump::getLine()
{
    char temp[32];

    stringex line = "";
    stringex ascii = "";

    // get offset
    const byte * offset = _currentPosition;
    if ( !_absoluteOffset )
        offset = (const byte *)(offset - _memory);
    std::sprintf(temp,"%p>",offset);
    line += temp;

    // get hex bytes
    const byte * end = _memory + _memoryLength;
    int count = 0;
    while ( count < 16 )
    {
        if ( (count % 4) == 0 )
            line += " ";

        if ( _currentPosition < end ) 
        {
            byte ch = *_currentPosition;
            sprintf(temp,"%02X",ch);
            line += temp;
            if ( (ch < 127) && (ch > 31) )
                ascii += ch;
            else
                ascii += '.';
            _currentPosition++;
        }
        else
        {
            line += "..";
            ascii += ' ';
        }

        count++;
    }

    // append ascii part
    line += " ";
    line += ascii;

    return line;
}

//--------------------------------------

void memory_dump::restart()
{
    _currentPosition = _memory;
}

//--------------------------------------

stringex memory_dump::dump( 
        const byte * mem, 
        whole memLength,
        boolean absoluteOffset )
{
    stringex theDump = "";
    memory_dump dump;
    dump.initialize(mem,memLength,absoluteOffset);

    while ( dump.more() )
    {
        theDump += dump.getLine();
        theDump += "\n";
    }

    return theDump;
}

//--------------------------------------

}; // namespace atoms

//----------------------------------------------------------
// (end of file)
