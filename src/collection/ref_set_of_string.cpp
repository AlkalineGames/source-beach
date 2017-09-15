//----------------------------------------------------------
//  Copyright 2011-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_set_of_string.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <collection/ref_set_of_string.hpp> // this header

namespace collection
{

//--------------------------------------
//  public methods
//--------------------------------------

ref_set_of_string::ref_set_of_string() 
{}

//--------------------------------------

ref_set_of_string::ref_set_of_string(
    const atoms::destroyer_typed<stringex> & d )
  :
    ref_set<stringex>( d )
{}

//--------------------------------------

ref_set_of_string::ref_set_of_string(
    const ref_set_of_string & rhs ) 
  :
    ref_set<stringex>( rhs )
{} 

//--------------------------------------

const ref_set_of_string & 
ref_set_of_string::operator =(
    const ref_set_of_string & rhs )
{
    *this = rhs;
}

//--------------------------------------

ref_set_of_string::const_iterator
ref_set_of_string::find_match(
    const stringex & in_string ) const
{
    // $$$$$$ RIDICULOUSLY INEFFICIENT
    const_iterator iter( begin() );
    while (    ( iter != end())
            && (*iter != in_string) )
    {
        iter++;
    }
    return iter;
}

//--------------------------------------

ref_set_of_string::const_iterator
ref_set_of_string::find_match(
    const text * in_text ) const
{
    if ( in_text != 0 )
    {
        // $$$$$$ RIDICULOUSLY INEFFICIENT
        for ( const_iterator iter( begin() ); iter != end(); iter++ )
        {
            if ( *iter == in_text )
            {
                return iter;
            }
        }
    }
    return end();
}

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
// (end of file)
