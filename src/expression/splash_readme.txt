The SPLASH c++ class library
============================

(Small Perl-like List And String Handling class library)


SPLASH is a c++ class library that implements my favourite Perl
constructs.

For those not familiar with Perl, it is an excellent scripting language
by Larry Wall and is available for most platforms.

This Class library provides List and String handling capabilities based
on those provided in Perl, because the Perl constructs are so useful.

Overview
-------- 
In a nut-shell SPLASH provides a Dynamic List template class
(SPList<T>) that allows you to add and extract data from the top of the
list (push & pop), and from the bottom of the list (unshift & shift).
ie a FIFO could be implemented by push'ing data onto the list and
shift'ing data off the list.  The list can be sorted (uses operator< on
the elements) and reversed.  (mylist.sort().reverse() will produce a
list sorted in reverse order).  Another list can be inserted anywhere
in a list, or elements deleted from within the list (splice).  And any
individual element can be accessed using the '[]' operator.

The String class (SPString) implements a Dynamic string which provides
an index() and rindex() function that finds the offset within the
string of a sub-string. A substring may be extracted from the string,
or assigned to within a string (expanding or shrinking the string as
required). The string may be used anywhere a const char * can be used.
The standard comparison functions (< > == etc) are available.  It
allows string concatenation using the '+' and '+=' operator.  It
provides regular expressions (with sub-expression extraction) that can
be easily applied to the strings. A powerful substitute function and
translation function (s() and tr()) are available.

The String List class (SPStringList) is basically a List class with
some added functionality specific to lists of strings. It lets you grep
for a regular expression within the list, returning a list of strings
that match. It lets you generate a list of strings from a single string
by splitting the string at a given regular expression (token parsing).
It lets you generate a single string by concatenating a list of strings
separated by a given string.

The Associative array class (Assoc<T>) lets you keep a list which is
indexed by a string.

All the Classes have fully implemented streams operators for input and
output, to allow convenient file or stream processing.

The Regexp class fully encapsulates the regular expression library, so
you can easily use your own favourite one.

Usage Restrictions
------------------

There are none. This Code is not Copyright, use as you will.  The
regexp code is Copyright by Henry Spencer, see the comments in regex.c
for Copyright info.  The only changes I have made are to the header
file, by adding a c++ prototype field.

Class description
-----------------
The Class Hierarchy and member functions are:-

class SPList<T>
    T& operator[]	// index into list
    void reset()	// clear out list
    int scalar()	// returns number of elements in list
    int count()		// ditto
    T pop()		// returns and removes top of list
    void push(T)	// enters element onto top of list
    void push(SPList<T>) // enters a list of elements onto top of list
    T shift()		// returns & removes element at bottom of list
    int unshift(T)	// enters element into bottom of list
    int unshift(SPList<T>) // enters lists into bottom of list
    SPList<T> reverse()	   // returns reverse order of list
    SPList<T> splice(offset) // removes elements in list from 'offset'
    SPList<T> splice(offset, len) // removes 'len' elements in list
    SPList<T> splice(offset, len, SPList<T>)// replaces elements in list
    SPList<T> sort() // sorts list according to result of '<' operator
    ostream& operator>>() // input stream
    istream& operator<<() // output stream

    class SPStringList // everything SPList does and ...
        int split(str [,pat] [,limit]) // splits string on pattern
	SPString join([pat])	 // concatenates list with 'pat'
	int m(exp, targ) 	 // makes list of sub exp matches
	SPStringList grep(exp) // returns matches in list
	ostream& operator>>()
    	istream& operator<<()

class SPString
    int length()	// length of string
    char chop()		// remove last character in string
    int index(SPString [, offset]) // find string from start
    int rindex(SPString [, offset]) // find string from end
    SPString substr(offset [, len]) // substring works as lvalue as well
    operator[]	// index character
    operator<   // less than
    operator>
    operator<=
    operator>=
    operator==
    operator!=
    operator+	    // concatenate 2 strings
    operator+=	    // as per c
    int m(exp) 	    // return true if regexp matches string
    int m(exp, SPStringList&) // ditto & generates a list of subexpressions
    int tr(exp, rep [,opts]) // translate 'ex'p into 'rep'
    int s(exp, rep [,opts]) // substitute 'exp' with 'rep'
    ostream& operator>>()
    istream& operator<<()

Associative array and helpers
-----------------------------

class Binar<T>	// a key, value pair
    T& value()
    SPString& key()

class Assoc<T>	// an associateive array, loosely based on the perl one
    T& operator(SPString) // equivalent to perl $assoc{"one"} = value
    Binar& operator[n]      // returns n'th entry in associative array
    SPStringList keys()   // returns a list of keys
    SPList<T> values()    // returns a list of values
    int isin(SPString)    // tests if key is in assoc array
    T adelete(SPString)    // deletes given key/value

Other Classes
-------------

VarString	- A variable length string class, used in SPString.

SPListBase<T> 	- is the base class for SPList and handles the
		  auto expanding dynamic array, optimized for
		  prepending and appending data.

TempString 	- makes a copy of a string, and can return a char *
	     	  and will free the storage when done. Something like
		  a cross between strsave() and alloca().

Regexp		- Handles the interface to the regular expression
		  library being used.

Range 		- Simple class to maintain a range, just makes things
		  easier.

For More Info
=============

See readme.2nd for how to build and test, and various caveats.
See splash.doc for documentation on each function.
See sample/*.c++ for examples of how to use splash
See regexp.doc for an explanation of the regexp library used

Distribution
------------

This is available as a compressed tar file for unix or
.zip format for MSDOS compatible names.

Email: morris@netcom.com
get the latest version of SPLASH, which is always available via
anonymous FTP.


site:-
ftp.netcom.com

Path:-
~ftp/pub/mo/morris/splash.tar.Z
~ftp/pub/mo/morris/splash.zip

