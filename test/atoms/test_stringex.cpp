//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_stringex.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_stringex.hpp"

namespace atoms
{

//--------------------------------------
//  internal definitions
//--------------------------------------

static const text sample_text_1[] =
    "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789";

static const text sample_text_2[] =
    "~!@#$%^&*()[]{}<>,./?'\";:\\`";

static stringex string_static( "string_static" );

//--------------------------------------
//  public methods
//--------------------------------------

test_stringex::test_stringex()
  :
    CppUnit::TestCase( "test_stringex" )
{}

//--------------------------------------

void
test_stringex::register_tests(
    CppUnit::TestSuite * suite )
{

    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_empty_string", &test_stringex::test_create_empty_string, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_on_heap", &test_stringex::test_create_on_heap, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_on_stack", &test_stringex::test_create_on_stack, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_copy_on_heap", &test_stringex::test_create_copy_on_heap, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_copy_on_stack", &test_stringex::test_create_copy_on_stack, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_create_copy_on_return", &test_stringex::test_create_copy_on_return, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_character", &test_stringex::test_construct_from_zero_character, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_character_with_count", &test_stringex::test_construct_from_zero_character_with_count, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_literal", &test_stringex::test_construct_from_zero_literal, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_literal_with_count", &test_stringex::test_construct_from_zero_literal_with_count, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_pointer", &test_stringex::test_construct_from_zero_pointer, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_from_zero_pointer_with_count", &test_stringex::test_construct_from_zero_pointer_with_count, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_assign_zero_character", &test_stringex::test_assign_zero_character, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_assign_zero_pointer", &test_stringex::test_assign_zero_pointer, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_construct_fill_char", &test_stringex::test_construct_fill_char, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_case_conversion", &test_stringex::test_case_conversion, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_erase_white_space", &test_stringex::test_erase_white_space, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_less_than_greater_than", &test_stringex::test_less_than_greater_than, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_resize", &test_stringex::test_resize, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_compare_case_insensitive", &test_stringex::test_compare_case_insensitive, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_find", &test_stringex::test_find, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_rfind", &test_stringex::test_rfind, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_find_first_of", &test_stringex::test_find_first_of, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_find_last_of", &test_stringex::test_find_last_of, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_substring", &test_stringex::test_substring, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_replace", &test_stringex::test_replace, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_insert", &test_stringex::test_insert, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_is_empty", &test_stringex::test_is_empty, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_compare", &test_stringex::test_compare, *this ) );
    suite->addTest( new CppUnit::TestCaller<test_stringex>(
        "test_starts_with", &test_stringex::test_starts_with, *this ) );
}

//--------------------------------------

void
test_stringex::test_create_empty_string()
{
    stringex s1(stringex::get_empty_text());
    stringex s2=stringex::get_empty_string();
    //stringex s2(stringex::get_empty_string());
    CPPUNIT_ASSERT( std::string( s1.get_text() ) == s2.get_text() );
}

//--------------------------------------

void
test_stringex::test_create_on_heap()
{
    stringex * s = new stringex( sample_text_1 );
    CPPUNIT_ASSERT( std::string( s->get_text() ) == sample_text_1 );
    delete s;
}

//--------------------------------------

void
test_stringex::test_create_on_stack()
{
    stringex s( sample_text_1 );
    CPPUNIT_ASSERT( std::string( s.get_text() ) == sample_text_1 );
}

//--------------------------------------

void
test_stringex::test_create_copy_on_heap()
{
    stringex * s = new stringex( sample_text_1 );
    stringex * t = new stringex( *s );
    delete s;
    CPPUNIT_ASSERT( std::string( t->get_text() ) == sample_text_1 );
    delete t;
}

//--------------------------------------

void
test_stringex::test_create_copy_on_stack()
{
    stringex s( sample_text_1 );
    {
        stringex t( s );
        CPPUNIT_ASSERT( std::string( t.get_text() ) == sample_text_1 );
    }
}

//--------------------------------------

void
test_stringex::test_create_copy_on_return()
{
    stringex s( make_copy_of_sample_text_1() );
    CPPUNIT_ASSERT( std::string( s.get_text() ) == sample_text_1 );
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_character()
{
    stringex s1;
    CPPUNIT_ASSERT( s1.get_size() == 0 );
    CPPUNIT_ASSERT( s1.get_text()[0] == '\0' );

    stringex s2('\0');
    CPPUNIT_ASSERT( s2.get_size() == 0 );
    CPPUNIT_ASSERT( s2.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_character_with_count()
{
    char value='\0';
    int count = 99;
    stringex s( count, value );
    CPPUNIT_ASSERT( s.get_size() == 99 );
    for ( whole i = 0; i <= count; i++ )
    {
        CPPUNIT_ASSERT( s.get_text()[i] == '\0' );
    }
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_literal()
{
    stringex s( 0 );
    CPPUNIT_ASSERT( s.get_size() == 0 );
    CPPUNIT_ASSERT( s.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_literal_with_count()
{
    stringex s( 99, 0 );
    CPPUNIT_ASSERT( s.get_size() == 99 );
    for ( size_type i = 0; i <= 99; i++ )
    {
        CPPUNIT_ASSERT( s.get_text()[i] == '\0' );
    }
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_pointer()
{
    char * value_ptr = 0;
    stringex s( value_ptr );
    CPPUNIT_ASSERT( s.get_size() == 0 );
    CPPUNIT_ASSERT( s.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_construct_from_zero_pointer_with_count()
{
    size_type count = 99;
    stringex s(  count,0 );
    CPPUNIT_ASSERT( s.get_size() == 99 );
    CPPUNIT_ASSERT( s.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_assign_zero_character()
{
    stringex s( sample_text_1 );
    s = 0;
    CPPUNIT_ASSERT( s.get_size() == 0 );
    CPPUNIT_ASSERT( s.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_assign_zero_pointer()
{
    stringex s( sample_text_1 );
    char * value_ptr = 0;
    s = value_ptr;
    CPPUNIT_ASSERT( s.get_size() == 0 );
    CPPUNIT_ASSERT( s.get_text()[0] == '\0' );
}

//--------------------------------------

void
test_stringex::test_construct_fill_char()
{
    char value_ptr = 'A';
    stringex s( 99, value_ptr);
    CPPUNIT_ASSERT( s.get_size() == 99 );
    CPPUNIT_ASSERT( s.get_text()[0] == value_ptr );
    for ( size_type i = 0; i < 99; i++ )
    {
        CPPUNIT_ASSERT( s.get_text()[i] == value_ptr );
    }
    CPPUNIT_ASSERT( s.get_text()[s.get_size()] == '\0' );

    stringex ss( 99, 'B');
    CPPUNIT_ASSERT( ss.get_size() == 99 );
    CPPUNIT_ASSERT( ss.get_text()[0] == 'B' );
    for ( size_type j = 0; j < 99; j++ )
    {
        CPPUNIT_ASSERT( ss.get_text()[j] == 'B' );
    }
    CPPUNIT_ASSERT( ss.get_text()[ss.get_size()] == '\0' );

}

//--------------------------------------

void
test_stringex::test_case_conversion()
{
    stringex str1L = "this is a test.";
    stringex str1U = "THIS IS A TEST.";
    stringex str2L = "abcdefghijklmnopqrstuvwxyz";
    stringex str2U = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    stringex str2M = "AbCdEfGhIjklMnopQrStuVWxYz";
    stringex str3  = "1234567890-=!@#$%^&*()-={}[];':\",./<>?\\|`~";

    stringex temp = str1L;
    CPPUNIT_ASSERT( temp.to_upper()  == str1U );
    CPPUNIT_ASSERT( temp.to_lower()  == str1L );
    temp = str2L;
    CPPUNIT_ASSERT( temp.to_upper()  == str2U );
    CPPUNIT_ASSERT( temp.to_lower()  == str2L );

    temp = str2M;
    CPPUNIT_ASSERT( temp.to_upper()  == str2U );
    temp = str2M;
    CPPUNIT_ASSERT( temp.to_lower()  == str2L );

    temp = str3;
    CPPUNIT_ASSERT( temp.to_lower()  == str3 );
    CPPUNIT_ASSERT( temp.to_upper()  == str3 );
}

//--------------------------------------

void
test_stringex::test_erase_white_space()
{
    stringex str1   = "This is a test.";
    stringex str1B  = "   This is a test.";
    stringex str1A  = "This is a test.    ";
    stringex str1BW = " \t  This is a test.";
    stringex str1AW = "This is a test. \t\r\n  ";

    stringex temp = str1;
    CPPUNIT_ASSERT( temp.erase_leading_blanks()       == str1 );
    temp = str1;
    CPPUNIT_ASSERT( temp.erase_leading_whitespace()   == str1 );
    temp = str1;
    CPPUNIT_ASSERT( temp.erase_trailing_blanks()      == str1 );
    temp = str1;
    CPPUNIT_ASSERT( temp.erase_trailing_whitespace()  == str1 );

    temp = str1B;
    CPPUNIT_ASSERT( temp.erase_leading_blanks()       == str1 );
    temp = str1B;
    CPPUNIT_ASSERT( temp.erase_leading_whitespace()   == str1 );
    temp = str1B;
    CPPUNIT_ASSERT( temp.erase_trailing_blanks()      != str1 );
    temp = str1B;
    CPPUNIT_ASSERT( temp.erase_trailing_whitespace()  != str1 );

    temp = str1A;
    CPPUNIT_ASSERT( temp.erase_leading_blanks()       != str1 );
    temp = str1A;
    CPPUNIT_ASSERT( temp.erase_leading_whitespace()   != str1 );
    temp = str1A;
    CPPUNIT_ASSERT( temp.erase_trailing_blanks()      == str1 );
    temp = str1A;
    CPPUNIT_ASSERT( temp.erase_trailing_whitespace()  == str1 );

    temp = str1BW;
    CPPUNIT_ASSERT( temp.erase_leading_blanks()       != str1 );
    temp = str1BW;
    CPPUNIT_ASSERT( temp.erase_leading_whitespace()   == str1 );
    temp = str1BW;
    CPPUNIT_ASSERT( temp.erase_trailing_blanks()      != str1 );
    temp = str1BW;
    CPPUNIT_ASSERT( temp.erase_trailing_whitespace()  != str1 );

    temp = str1AW;
    CPPUNIT_ASSERT( temp.erase_leading_blanks()       != str1 );
    temp = str1AW;
    CPPUNIT_ASSERT( temp.erase_leading_whitespace()   != str1 );
    temp = str1AW;
    CPPUNIT_ASSERT( temp.erase_trailing_blanks()      != str1 );
    temp = str1AW;
    CPPUNIT_ASSERT( temp.erase_trailing_whitespace()  == str1 );
}

//--------------------------------------

void
test_stringex::test_less_than_greater_than()
{
    stringex str1  = "ABC";
    stringex str2  = "XYZ";
    stringex str3  = "AB";
    stringex str4  = "persistence_settings";
    stringex str5  = "graphics_settings";

    CPPUNIT_ASSERT( str1 < str2 );
    CPPUNIT_ASSERT( str2 > str1 );
    CPPUNIT_ASSERT( str3 < str1 );
    CPPUNIT_ASSERT( str4 > str5);
    CPPUNIT_ASSERT( str5 < str4);
}

//--------------------------------------

void
test_stringex::test_resize()  
{
    stringex str1  = "ABC";
    str1.resize(13);
    CPPUNIT_ASSERT( str1.get_size()== 13 );
}

//--------------------------------------

void
test_stringex::test_compare_case_insensitive()
{
    stringex s(     "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );
    CPPUNIT_ASSERT( s.compare_case_insensitive(
                    "abcdefghijklmnopqrstuvwxyz0123456789" ) == 0 );
    CPPUNIT_ASSERT( s.compare_case_insensitive(
                    "abcdefghijklmnopqrstuvwxyz" ) == 10 );
    CPPUNIT_ASSERT( s.compare_case_insensitive(
                    "abcdefghijklmnopqrstuvwxyz0123456789*****" ) == -1 );
    CPPUNIT_ASSERT( s.compare_case_insensitive(
                    "mbcdefghijklmnopqrstuvwxyz0123456789" ) == -12 );
    CPPUNIT_ASSERT( s.compare_case_insensitive(
                    "abcdefghijklmnopqrstuvwxym0123456789" ) == 13 );
}

//--------------------------------------

void
test_stringex::test_find()
{
    stringex str1  = "MY NAME IS DAVE MY NAME IS DAVE";
    stringex fnd1  = "NAME";

    CPPUNIT_ASSERT( str1.find(fnd1)== 3 );
    CPPUNIT_ASSERT( str1.find(fnd1,10)== 19 );
    CPPUNIT_ASSERT( str1.find("XYZ")== stringex::npos );
    CPPUNIT_ASSERT( str1.find("MY NAME")== 0 );
}

//--------------------------------------

void
test_stringex::test_rfind()
{
    stringex str1  = "MY NAME IS DAVE MY NAME IS DAVE";
    stringex fnd1  = "NAME";

    CPPUNIT_ASSERT( str1.rfind(fnd1)== 19 );
    CPPUNIT_ASSERT( str1.rfind("XYZ")== stringex::npos );
    CPPUNIT_ASSERT( str1.rfind("MY NAME")== 16 );
}

//--------------------------------------

void
test_stringex::test_find_first_of()
{
    stringex str1  = "this//is//a//file//spec.lwo";

    CPPUNIT_ASSERT( str1.find_first_of("//")== 4 );
    CPPUNIT_ASSERT( str1.find_first_of("ba")== 10 );
}

//--------------------------------------

void
test_stringex::test_find_last_of()
{
    stringex str1  = "this//is//a//file//spec.lwo";
    stringex str2  = "spec.lwo";

    whole    epos  = str1.find_last_of(":/");

    CPPUNIT_ASSERT( epos == 18 );

    stringex str3 = str1.substr(epos+1);
    CPPUNIT_ASSERT( str3==str2);
}

//--------------------------------------

void
test_stringex::test_substring()
{
    stringex str1  = "0123456789";
    stringex str2  = "01234";
    stringex str3  = "56789";
    stringex subs1 = str1.substr(0,5);
    stringex subs2 = str1.substr(5,5);

    CPPUNIT_ASSERT( str2.compare(subs1)== 0 );
    CPPUNIT_ASSERT( str3.compare(subs2)== 0 );
}

//--------------------------------------

void
test_stringex::test_replace()
{
    stringex str1  = "MY NAME IS XXXX, HELLO";
    stringex str2  = "DAVE";
    stringex str3  = "MY NAME IS DAVE, HELLO";

    stringex str4  = "MY NAME IS XXXX, HELLO";
    stringex str5  = "TANSY";
    stringex str6  = "MY NAME IS TANSY, HELLO";

    str1.replace(11,4,str2);
    str4.replace(11,4,str5);

    //logger::acquire_default_instance().log_information("a","b",str1);

    CPPUNIT_ASSERT( str1.compare(str3)== 0 );
    CPPUNIT_ASSERT( str4.compare(str6)== 0 );

    stringex str_a;
    stringex str_a_compare("a");
    stringex str_ab_compare("ab");
    str_a.replace(0,1,"a");

    CPPUNIT_ASSERT( str_a.compare(str_a_compare)== 0 );

    str_a.replace(1,1,"b");
    CPPUNIT_ASSERT( str_a.compare(str_ab_compare)== 0 );
}

//--------------------------------------

void
test_stringex::test_insert()
{

    stringex str1  = "MY NAME IS , HELLO";
    stringex str2  = "DAVE";
    stringex str3  = "MY NAME IS DAVE, HELLO";

    str1.insert(11,str2);

    CPPUNIT_ASSERT( str1.compare(str3)== 0 );

    whole pos=0;
    stringex insert_string_a("a");
    stringex insert_string_b("b");
    stringex str4;

    str4.insert(pos,insert_string_a);
    CPPUNIT_ASSERT( str4.compare("a")== 0 );

    str4.insert(++pos,insert_string_b);
    CPPUNIT_ASSERT( str4.compare("ab")== 0 );

    str4.insert(++pos,insert_string_b);
    CPPUNIT_ASSERT( str4.compare("abb")== 0 );
}

//--------------------------------------

void
test_stringex::test_is_empty()
{
    stringex str1  = "MY NAME IS , HELLO";
    stringex str2;

    boolean t = str1.is_empty();

    CPPUNIT_ASSERT( str1.get_size()!=0 );
    CPPUNIT_ASSERT( !str1.empty());
    CPPUNIT_ASSERT( !str1.is_empty());
    CPPUNIT_ASSERT( str2.is_empty());
}

//--------------------------------------

void
test_stringex::test_compare()
{
    stringex str1  = "event";
    stringex str2  = "event_channel";
    stringex str3  = "event";

    CPPUNIT_ASSERT( str1.compare(str2)!= 0 );
    CPPUNIT_ASSERT( str1.compare(str3)== 0 );
}

//--------------------------------------

void
test_stringex::test_starts_with()
{
    stringex str1  = "event";
    stringex str2  = "event_channel";
    stringex str3  = "event";

    CPPUNIT_ASSERT( str1.starts_with(str2)== 0 );
    CPPUNIT_ASSERT( str1.starts_with(str3)== 0 );
}

//--------------------------------------

// virtual
int
test_stringex::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_stringex::setUp()
{
//    _stringex = new stringex;
}

//--------------------------------------

// virtual
void
test_stringex::tearDown()
{
//    delete _stringex;
}

//--------------------------------------
//  private methods
//--------------------------------------

stringex
test_stringex::make_copy_of_sample_text_1()
{
    stringex s( sample_text_1 );
    return s;
}

//--------------------------------------

}; // end of namespace atoms

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<atoms::test_stringex>;

//----------------------------------------------------------
// (end of file)
