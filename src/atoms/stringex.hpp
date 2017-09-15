#if !defined(BEACH_ATOMS_STRINGEX)
#define      BEACH_ATOMS_STRINGEX
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       stringex.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/atoms_allocator.hpp>
#include <atoms/primitives.hpp>

#include <string>

namespace atoms
{

//--------------------------------------

/// stringex's std superclass parameterized with our allocator
/**
 *  atoms_allocator is passed to std::basic_string so that its
 *  dynamic allocations occur through the allocation_center
 *  when the lifecycle_manager is used.
 *
 *  @note: string_basic objects must not be declared with
 *          static storage duration if the allocation_center 
 *          and lifecycle_manager are used because the
 *          lifecycle_manager will be destroyed before
 *          the destructor for any static declared basic_string.
 */
typedef std::basic_string<char,std::char_traits<char>,atoms_allocator<char> >
    string_basic;

//--------------------------------------

/// string extended
/**
 *  Enhancement of the Standard C++ string type.
 *  One of the main enhancements is the ability
 *  to pass 0 (null pointer) wherever a char *
 *  parameter is used--without it crashing.
 *
 *  atoms_allocator is passed to std::basic_string so that its
 *  dynamic allocations occur through the allocation_center
 *  when the lifecycle_manager is used.
 *
 *  @note: stringex objects must not be declared with
 *          static storage duration if the allocation_center
 *          and lifecycle_manager are used because the
 *          lifecycle_manager will be destroyed before
 *          the destructor for any static declared stringex.
 */
class stringex
    : public string_basic
{
public:

    BEACH_ALLOCATION_OPERATORS

    static const stringex   get_empty_string()  { return 0;  } // $$$
    static const text *     get_empty_text()    { return ""; } // $$$

    /// default constructor (not provided by superclass)
    stringex() : string_basic( get_empty_text() ) {}

    /// @name same constructors as superclass
    /** except that text pointers can be zero, safely */
    //@{
    stringex( const string_basic & rhs )
      : string_basic( rhs )
    {}
    stringex( const string_basic & rhs, size_type pos, size_type n, const allocator_type & al = allocator_type() )
      :
        string_basic( rhs, pos, n, al )
    {}
    stringex( const value_type * s, size_type n, const allocator_type & al = allocator_type() )
      :
        string_basic( ((s != 0) ? s : get_empty_text()), n, al )
    {}
    stringex( const value_type * s, const allocator_type & al = allocator_type() )
      :
        string_basic( ((s != 0) ? s : get_empty_text()), al )
    {}
    stringex( size_type n, value_type c, const allocator_type & al = allocator_type() )
      :
        string_basic( n, c, al )
    {}
    stringex( iterator first, iterator last, const allocator_type & al = allocator_type() )
      :
        string_basic( first, last, al )
    {}
    //@}

    /// @name assignment & operators (same as superclass except return type)
    //@{
    stringex & operator=( const string_basic & rhs )
    {   return static_cast<stringex&>(string_basic::operator=( rhs )); }

    stringex & operator=( const value_type * rhs )
    {   return (rhs != 0) ? static_cast<stringex&>(string_basic::operator=( rhs ))
                          : static_cast<stringex&>(erase()); }

    stringex & operator=( int rhs ) ///< eliminates ambiguous overload for = 0
    {   return (rhs != 0) ? static_cast<stringex&>(string_basic::operator=( value_type(rhs) ))
                          : static_cast<stringex&>(erase()); }

    stringex & operator=( value_type rhs )
    {   return static_cast<stringex&>(string_basic::operator=( rhs )); }
      
    stringex & operator+=( const string_basic & rhs )
    {   return static_cast<stringex&>(string_basic::operator+=( rhs )); }

    stringex & operator+=( const value_type * rhs )
    {   return (rhs != 0) ? static_cast<stringex&>(string_basic::operator+=( rhs ))
                          : static_cast<stringex&>(*this); }

    stringex & operator+=( value_type rhs )
    {   return static_cast<stringex&>(string_basic::operator+=( rhs )); }
    //@}

    /// @name compare(...) same as superclass
    /** except that text pointers can be zero, safely */
    //@{
    int compare( const string_basic & str ) const
    {
        return string_basic::compare( str );
    }
    int compare( size_type pos, size_type n, const string_basic & str ) const
    {
        return string_basic::compare( pos, n, str );
    }
    int compare( size_type pos1, size_type n1, const string_basic & str,
                 size_type pos2, size_type n2 ) const
    {
        return string_basic::compare( pos1, n1, str, pos2, n2 );
    }
    int compare( const value_type * s ) const
    {
        if ( s == 0 )
        {
            return get_size();
        }
        else
        {
            return string_basic::compare( s );
        }
    }
    int compare( size_type pos, size_type n, const value_type * s ) const
    {
        if ( s == 0 )
        {
            return get_size();
        }
        else
        {
            return string_basic::compare( pos, n, s );
        }
    }
    int compare( size_type pos, size_type n1, const value_type * s, size_type n2 ) const
    {
        if ( s == 0 )
        {
            return get_size(); 
        }
        else
        {
            return string_basic::compare( pos, n1, s, n2 );
        }
    }
    //@}
    int compare_case_insensitive( const value_type * s ) const;

    /// @name implicit and explicit conversions to character array
    //@{
    const text * get_text() const   { return c_str(); }
          text * get_text_nc()      { return const_cast<text*>(get_text()); }
    operator const text *() const   { return get_text(); }
    operator       text *()         { return get_text_nc(); }
    //@}

    /// @name enhancements
    //@{
    boolean     is_valid_pos( int pos ) const
    {
        return ((pos != npos) && (pos >= 0) && (pos < size()));
    }
    integer     starts_with( const stringex & ) const;
    integer     starts_with( const text * )     const;

    stringex    right( size_t in_length ) const;
    stringex &  to_lower();
    stringex &  to_upper();

    stringex &  erase_leading_blanks();
    stringex &  erase_leading_whitespace();
    stringex &  erase_trailing_blanks();
    stringex &  erase_trailing_whitespace();

    stringex &  find_erase( ///< calls find(...) then erase(...) if found
        const stringex &, size_type pos = 0 );

    /// find prefix before separator, strip it and return it
    stringex    extract_prefix( text in_separator );
    //@}

    /// @name synonyms
    //@{
    boolean     is_empty()   const { return empty();  }
    size_type   get_size()   const { return size();   }
    size_type   get_length() const { return length(); }
    //@}

}; // end of class stringex

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_ATOMS_STRINGEX
