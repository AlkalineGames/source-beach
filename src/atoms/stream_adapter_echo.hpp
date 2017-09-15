#if !defined(BEACH_ATOMS_STREAM_ADAPTER_ECHO)
#define      BEACH_ATOMS_STREAM_ADAPTER_ECHO
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stream_adapter_echo.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>

#include <ostream>

namespace atoms
{

//--------------------------------------

/// stream adapter that echos output to an additional stream
/**
 *  Unfortunately an object adapter is required because none
 *  of the stream operations are virtual. Thus an instance
 *  of stream_adapter_echo has the same operations as a
 *  stream object, but is not substitutable for a stream
 *  object.
 *
 *  @note   design patterns applied:
 *              - Adapter [GoF]
 */      
class stream_adapter_echo
{
public:
   
    BEACH_ALLOCATION_OPERATORS
 
    stream_adapter_echo(
        std::ostream & in_stream_real,
        std::ostream * in_stream_echo = 0 )
      :
        _stream_real( in_stream_real ),
        _stream_echo( in_stream_echo )
    {}

    stream_adapter_echo(
        stream_adapter_echo & rhs )
      :
        _stream_real( rhs._stream_real ),
        _stream_echo( rhs._stream_echo )
    {}

    const std::ostream & get_stream_real_const() const  { return _stream_real; }
          std::ostream & get_stream_real()              { return _stream_real; }

    const std::ostream * get_stream_echo_const() const  { return _stream_echo; }
          std::ostream * get_stream_echo()              { return _stream_echo; }

    void echo_to( std::ostream * es ) { _stream_echo = es; }

    /// @name std::ostream adaption methods
    // !!! add other std::ostream methods on an as-needed basis
    //@{
    stream_adapter_echo & operator<<(
        std::ostream & (*pf)( std::ostream & ) )
    {
        ((*pf)(_stream_real));
        if ( _stream_echo != 0 )
        {                    
            ((*pf)(*_stream_echo));
        }
        return *this;
    }
    stream_adapter_echo & operator<<(
        std::ios & (*pf)( std::ios & ) )
    {
        (*pf)(*(std::ios *)&_stream_real);
        if ( _stream_echo != 0 )
        {                
            (*pf)(*(std::ios *)_stream_echo);
        }
        return *this;
    }
    stream_adapter_echo & operator<<(
        std::ios_base & (*pf)( std::ios_base & ) )
    {
        (*pf)(*(std::ios_base *)&_stream_real);
        if ( _stream_echo != 0 )
        {                    
            (*pf)(*(std::ios_base *)_stream_echo);
        }
        return *this;
    }
    stream_adapter_echo & operator<<( bool n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( short n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( unsigned short n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( int n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( unsigned int n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
            *_stream_echo << n;
        return *this;
    }
    stream_adapter_echo & operator<<( long n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( unsigned long n )
    {
        _stream_real << n;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << n;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( float f )
    {
        _stream_real << f;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << f;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( double f )
    {
        _stream_real << f;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << f;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( long double f )
    {
        _stream_real << f;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << f;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( atoms::integer64 i )
    {
        _stream_real << i;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << i;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( atoms::whole64 w )
    {
        _stream_real << w;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << w;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( const void *p )
    {
        _stream_real << p;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << p;
        }
        return *this;
    }
    stream_adapter_echo & operator<<( std::streambuf *sb )
    {
        _stream_real << sb;
        if ( _stream_echo != 0 )
        {
            *_stream_echo << sb;
        }            
        return *this;
    }
    //@}

private:

    std::ostream & _stream_real;
    std::ostream * _stream_echo;

}; // end of class stream_adapter_echo

//--------------------------------------

/// @name stream_adapter_echo binary operators
//@{
inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const char *_X )
{
    _O.get_stream_real() << _X;
    if ( _O.get_stream_echo() != 0 )
    {
        *_O.get_stream_echo() << _X;
    }
    return _O;
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, char _C )
{
    _O.get_stream_real() << _C;
    if ( _O.get_stream_echo() != 0 )
    {
        *_O.get_stream_echo() << _C;
    }
    return _O;
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const signed char *_X )
{
    return (_O << (const char *)_X);
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const signed char _C )
{
    return (_O << (char)_C);
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const unsigned char *_X )
{
    return (_O << (const char *)_X);
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const unsigned char _C )
{
    return (_O << (char)_C);
}

//--------------------------------------

inline
stream_adapter_echo &
operator<<(
    stream_adapter_echo & _O, const signed short *_X )
{
    return (_O << (const wchar_t *)_X);
}
//@}

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_STREAM_ADAPTER_ECHO
