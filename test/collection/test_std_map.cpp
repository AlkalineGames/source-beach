//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_std_map.cpp
 *  @note       platform independent, Standard C++
 *  @author     Shawn Barham
 */
//----------------------------------------------------------

#include "test_std_map.hpp"

#include <atoms/stringex.hpp>
#include <cppunit/TestCaller.h>

#include <map>

namespace collection
{
    using namespace atoms;

//--------------------------------------
//  internal definitions
//--------------------------------------

typedef std::less<int> mapcmp;
typedef std::map<int, test_std_map::test_element*, mapcmp> emap;

class oemap : public emap
{
public:
    oemap() {}
    virtual ~oemap()
    {
        int index, id;
        const char * text;
        test_std_map::test_element * ele;
        const_iterator iter;
        for ( iter = begin();
              iter != end();
              iter++ )
        {
            index = (*iter).first;
            ele   = (*iter).second;
            id    = ele->get_id();
            text  = ele->get_text();
            delete ele;
        }
    }
    void insert( int index, test_std_map::test_element * ele)
    {
        (*this)[index] = ele;
    }
};

//--------------------------------------
//  public methods
//--------------------------------------

test_std_map::test_std_map()
  :
    CppUnit::TestCase( "test_std_map" )
{}

//--------------------------------------

void
test_std_map::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_std_map>(
        "test_std_map_basic", &test_std_map::test_std_map_basic, *this ) );

    suite->addTest( new CppUnit::TestCaller<test_std_map>(
        "test_std_map_typedef", &test_std_map::test_std_map_typedef, *this ) );

    suite->addTest( new CppUnit::TestCaller<test_std_map>(
        "test_std_map_ref", &test_std_map::test_std_map_ref, *this ) );

    suite->addTest( new CppUnit::TestCaller<test_std_map>(
        "test_std_map_owned", &test_std_map::test_std_map_owned, *this ) );
}

//--------------------------------------

struct ltstr
{
    bool operator()(const char* s1, const char* s2) const
    {
        return std::string( s1 ) < s2;
    }
};

//--------------------------------------

void
test_std_map::test_std_map_basic()
{
    std::map<const char*, int, ltstr> months;

    months["january"]   = 31;
    months["february"]  = 28;
    months["march"]     = 31;
    months["april"]     = 30;
    months["may"]       = 31;
    months["june"]      = 30;
    months["july"]      = 31;
    months["august"]    = 31;
    months["september"] = 30;
    months["october"]   = 31;
    months["november"]  = 30;
    months["december"]  = 31;

    std::map<const char*, int, ltstr>::iterator cur  = months.find("june");
    std::map<const char*, int, ltstr>::iterator prev = cur;
    std::map<const char*, int, ltstr>::iterator next = cur;
    ++next;
    --prev;

    const char * p_name = (*prev).first;
    const char * c_name = (*cur).first;
    const char * n_name = (*next).first;

    int p_count = (*prev).second;
    int c_count = (*cur).second;
    int n_count = (*next).second;

    CPPUNIT_ASSERT( std::string( p_name ) == "july" );
    CPPUNIT_ASSERT( p_count == 31 );

    CPPUNIT_ASSERT( std::string( c_name ) == "june" );
    CPPUNIT_ASSERT( c_count == 30 );

    CPPUNIT_ASSERT( std::string( n_name ) == "march" );
    CPPUNIT_ASSERT( n_count == 31 );
}

//--------------------------------------

void
test_std_map::test_std_map_typedef()
{
    typedef std::map<const char*, int, ltstr> month_list;
    month_list months;

    months["january"]   = 31;
    months["february"]  = 28;
    months["march"]     = 31;
    months["april"]     = 30;
    months["may"]       = 31;
    months["june"]      = 30;
    months["july"]      = 31;
    months["august"]    = 31;
    months["september"] = 30;
    months["october"]   = 31;
    months["november"]  = 30;
    months["december"]  = 31;

    month_list::iterator cur  = months.find("june");
    month_list::iterator prev = cur;
    month_list::iterator next = cur;
    ++next;
    --prev;

    const char * p_name = (*prev).first;
    const char * c_name = (*cur).first;
    const char * n_name = (*next).first;

    int p_count = (*prev).second;
    int c_count = (*cur).second;
    int n_count = (*next).second;

    CPPUNIT_ASSERT( std::string( p_name ) == "july" );
    CPPUNIT_ASSERT( p_count == 31 );

    CPPUNIT_ASSERT( std::string( c_name ) == "june" );
    CPPUNIT_ASSERT( c_count == 30 );

    CPPUNIT_ASSERT( std::string( n_name ) == "march" );
    CPPUNIT_ASSERT( n_count == 31 );
}

//--------------------------------------

void
test_std_map::test_std_map_ref()
{
    typedef std::less<int> mapcmp;
    typedef std::map<int, test_std_map::test_element*, mapcmp> emap;

    emap elements;
    elements[105] = new test_std_map::test_element(105,"Eggplant");
    elements[106] = new test_std_map::test_element(106,"Fig");
    elements[107] = new test_std_map::test_element(107,"Grape");
    elements[101] = new test_std_map::test_element(101,"Apple");
    elements[104] = new test_std_map::test_element(104,"Date");
    elements[102] = new test_std_map::test_element(102,"Banana");
    elements[103] = new test_std_map::test_element(103,"Cranberry");

    emap::iterator cur  = elements.find(104); // "Date"
    emap::iterator prev = cur;
    emap::iterator next = cur;
    ++next;
    --prev;

    test_std_map::test_element * ele;
    const char * text;
    int index, id;

    index = (*prev).first;
    ele   = (*prev).second;
    id    = ele->get_id();
    text  = ele->get_text();
    CPPUNIT_ASSERT( id == index );
    CPPUNIT_ASSERT( std::string( text ) == "Cranberry" );

    index = (*cur).first;
    ele   = (*cur).second;
    id    = ele->get_id();
    text  = ele->get_text();
    CPPUNIT_ASSERT( id == index );
    CPPUNIT_ASSERT( std::string( text ) == "Date" );

    index = (*next).first;
    ele   = (*next).second;
    id    = ele->get_id();
    text  = ele->get_text();
    CPPUNIT_ASSERT( id == index );
    CPPUNIT_ASSERT( std::string( text ) == "Eggplant" );

    emap::const_iterator iter;
    for ( iter = elements.begin();
          iter != elements.end();
          iter++ )
    {
        index = (*iter).first;
        ele   = (*iter).second;
        delete ele;
    }
}

//--------------------------------------

void
test_std_map::test_std_map_owned()
{
    oemap * elements = new oemap;
    elements->insert( 105, new test_std_map::test_element(105,"Eggplant") );
    elements->insert( 106, new test_std_map::test_element(106,"Fig") );
    elements->insert( 107, new test_std_map::test_element(107,"Grape") );
    elements->insert( 101, new test_std_map::test_element(101,"Apple") );
    elements->insert( 104, new test_std_map::test_element(104,"Date") );
    elements->insert( 102, new test_std_map::test_element(102,"Banana") );
    elements->insert( 103, new test_std_map::test_element(103,"Cranberry") );
    delete elements;
}

//--------------------------------------

// virtual
int
test_std_map::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_std_map::setUp()
{}

//--------------------------------------

// virtual
void
test_std_map::tearDown()
{}

//--------------------------------------

test_std_map::test_element::test_element(
    whole16         id,
    const char *    text )
  :
    _id(            id ),
    _text(          text )
{}

//--------------------------------------

test_std_map::test_element::~test_element()
{}

//--------------------------------------

}; // end of namespace collection

//----------------------------------------------------------
// (end of file)
