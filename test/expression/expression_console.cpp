//----------------------------------------------------------
//  Copyright 2005-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       expression_console.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <version_beach.h>
#include <atoms/stringex.hpp>
#include <expression/regular_expression.hpp>
#include <expression/splash.h>

#if 0 // PCRE MATCHING ALWAYS PRODUCES FALSE FOR SOME REASON
#include <pcrecpp.h>
#endif

#if 0 // C++11 SUPPORT IS NOT COMPLETE IN GCC
//#include <regex>
#endif
#include <string>
#include <iostream>

using namespace atoms;
using expression::regular_expression;
using expression::SPString;
using expression::SPStringList;

//--------------------------------------
//  global methods
//--------------------------------------

int
main(
    int argc, char * argv[] )
{
    std::cout
        << "Beach Expression Framework version "
        << VERSION_BEACH
        << ", console utility" << std::endl;
    stringex regexstr, matchstr;
    text inputtext[1024];
    while ( true )
    {
        std::cout
            << "=============================" << std::endl
            << "Enter c to keep current value, or q to quit:" << std::endl
            << "regular expression --> ";
        std::memset( inputtext, 0, sizeof(inputtext) );
        std::cin.getline( inputtext, sizeof(inputtext)-1, '\n' );
        stringex regentry( inputtext );
        if ( (regentry == "q") || (regentry == "Q") )
        {
            break;
        }
        if ( (regentry != "c") && (regentry != "C") )
        {
            regexstr = regentry;
        }
        std::cout << "   matching string --> ";
        std::memset( inputtext, 0, sizeof(inputtext) );
        std::cin.getline( inputtext, sizeof(inputtext)-1, '\n' );
        stringex matchentry( inputtext );
        if ( (matchentry == "q") || (matchentry == "Q") )
        {
            break;
        }
        if ( (matchentry != "c") && (matchentry != "C") )
        {
            matchstr = matchentry;
        }
#if 0 // C++11 SUPPORT IS NOT COMPLETE IN GCC
        // C++11 results
        std::regex stdregex( regexstr );
        std::cmatch stdcmatch;
        bool matches = std::regex_search(
           matchstr.get_text(), stdcmatch, stdregex );
        std::cout
            //<< "\-----------------------------" << std::endl
            // !!! FAILS TO LINK WITH stlport IF WE STREAM A stringex WITHOUT USING get_text()
            << "regular expression  == \"" << regexstr.get_text() << '"' << std::endl
            << "   matching string  == \"" << matchstr.get_text() << '"' << std::endl
            << "\n\n-----------------------------" << std::endl
            << "regex_search(...)   == " << (matches ? "true" : "false" )
            << "matchresults.size() == " << matchresults.size();
        for ( int i = 0; i < matchresults.size(); i++ )
        {
            std::cout << '[' << i << "] == " << matchresults[i] << std::endl;
        }
#endif
#if 0 // PCRE MATCHING ALWAYS PRODUCES FALSE FOR SOME REASON
        // PCRE results
        pcrecpp::RE rex( regexstr );
        std::string matchresults[16];
        bool matches = rex.FullMatch( matchstr.get_text(),
            &matchresults[ 0], &matchresults[ 1], &matchresults[ 2], &matchresults[ 3],
            &matchresults[ 4], &matchresults[ 5], &matchresults[ 6], &matchresults[ 7],
            &matchresults[ 8], &matchresults[ 9], &matchresults[10], &matchresults[11],
            &matchresults[12], &matchresults[13], &matchresults[14], &matchresults[15] );
        std::cout
            << "----------------------" << std::endl
            << "PCRE:" << std::endl
            << "regular expression == \"" << regexstr.get_text() << '"' << std::endl
            << "   matching string == \"" << matchstr.get_text() << '"' << std::endl
            << "rex.FullMatch(...) == " << (matches ? "true" : "false" ) << std::endl;
        for ( int i = 0; i < 16; i++ )
        {
            if ( matchresults[i].empty() )
            {
                break;
            }
            std::cout << "    [" << i << "] == " << matchresults[i] << std::endl;
        }
#endif
        // EXPRESSION results
        regular_expression re( regexstr );
        int matchresult = re.match( matchstr.get_text() );
        SPStringList strlist;
        SPString str( matchstr );
        str.m( re, strlist );
        std::cout
            << "----------------------" << std::endl
            << "EXPRESSION:" << std::endl
            << "regular expression         == \"" << regexstr.get_text() << '"' << std::endl
            << "   matching string         == \"" << matchstr.get_text() << '"' << std::endl
            << "regular_expression.match() == " << matchresult << std::endl
            << "SPStringList.m(...), count == " << strlist.count() << std::endl;
        for ( int i = 0; i < strlist.count(); i++ )
        {
            std::cout << "    [" << i << "] == \"" << strlist[i] << '"' << std::endl;
        }
    }
    return 0;
}

//--------------------------------------
//  template instantiations
//--------------------------------------

#if 0 // C++11 SUPPORT IS NOT COMPLETE IN GCC
template class std::basic_regex<char, std::regex_traits<char> >;
template class std::match_results<const char*>;
template bool std::regex_search(const char*,std::cmatch,std::regex,std::regex_constants::match_flag_type);
#endif

//----------------------------------------------------------
// (end of file)
