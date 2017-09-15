For support Email to morris@netcom.com

I would welcome bug reports for a while!
Also comments are always welcome.

The latest version of SPLASH is always available via anonymous
FTP from netcom.com in pub/mo/morris/splash.tar.Z (for Unix and gcc)
and pub/mo/morris/splash.zip (for MSDOS)

Introducing SPLASH
==================

SPLASH is a c++ class library that implements my favourite perl
constructs.  Obviously I can't duplicate all the functionality of perl,
and wouldn't need to as perl already exists!! However I find this
useful, because it allows me to do Perl-like things in my programs.

This Code is not copyright, use as you will.  The regexp code is by
Henry Spencer, see the comments for Copyright info.  The only changes I
have made are to the header file, by adding a c++ prototype field.

The Class Hierarchy and member functions are are fully described in
the file splash.doc
	     
Building NOTES
==============
This must be compiled with a 3.0 or greater c++ compiler that can
handle Templates and nested classes.

It has been tested on Borland c++ v4.0 and USL-based 3.0 cfront.
GCC v2.6.3 will compile it with -fno-implicit-templates, and explicit
template declarations in a single file. ie if when you link and gcc
complains about undefined functions that are templates, you must add
an explicit template declaration for each template you use in one file.
eg you get the following errors...

assoc.o: In function `main':
assoc.cc:22: undefined reference to `operator<<(ostream &, Assoc<int> &)'
assoc.cc:602: undefined reference to `SPListBase<Binar<int> >::count(void) const
assoc.o: In function `SPList<Binar<int> >::shift(void)':
assoc.o: In function `SPList<Binar<int> >::push(SPList<Binar<int> > const &)':
assoc.cc:621: undefined reference to `SPListBase<Binar<int> >::count(void) const

you would add the following to the .cc file:-
template ostream& operator<<(ostream &, Assoc<int> const &);
template class SPList<Binar<int> >;
template class SPListBase<Binar<int> >;

See the samples and the test files.

To build:

compile splash.cpp and regex.c. Link in with your App.
Include splash.h, (and assoc.h if used).

> cc -c regex.c
> CC -c splash.cpp
> CC yourapp.cpp splash.o regex.o -o yourapp

To test:

> CC -DTEST spltest.cpp splash.cpp regex.o -o spltest
> spltest > x
> diff x splash.v

and

> CC -DTEST slicetst.cpp splash.o regex.o -o slicetst
> slicetst > x
> diff x slicetst.v

This will do a full regression test. splash.v & slicetst.v contains the
sample output of a correct run, so no differences should be
encountered.

regex.c is not an ANSI c file, so you will have to turn off prototype
checking on your ANSI c compiler (or select kr checking).

Some of the samples use a file called tracer.h, this is a fairly useful
Debugging helper grabbed from the net and slightly modified. I include
tracer.h and tracer.cpp for completeness, however they are not required.

CAVEATS (known ones that is)
=======
This is not an optimised implementation, by any stretch of the
imagination. It is a quick and dirty, "but it works" one.

No "out of memory checking" is done, I thought I'd wait for
exceptions!!

I have taken a few liberties in translating the selected perl
functionality into a class library, apologies to Larry Wall, and
anyone else this may offend.  You are welcome to fix it, just tell me
how you did it.

A SPList<T> can only contain a list of type T, it cannot, as yet,
have multiple types in the same list. (This is feasible but messy).

Assigning to an element of a SPList that is greater than the current
length of the SPList will expand the list as in perl, but the values
in the newly created elements will be undefined, unlike perl. Except
SPStringList which will create empty strings. Also if <T> is a class
then the values will be whatever the default constructor creates.

Anything that you make a SPList out of must define an operator<(),
for the sort routine. Its ok if it is a dummy.

The first index of a list is always 0. (Again this could be fixed).

Unlike perl you can also access characters within
a SPString using the '[]' syntax. But you must use substr() to
change them.

Note that SPStrings cannot have embedded '\0' like perl, this
is an efficiency trade off, because '\0' as a terminator is so
ingrained in c++ and c strings. (This could be fixed by carefully
replacing all str... functions with mem... functions

Regular Expressions
-------------------

Regular expressions may be slightly different, I used the straight
Henry Spencer version. I'm not sure what changes Larry made to them.
(It definitely doesn't support \w \b \s \S \d \D, or global match
mode). - If someone can make Larry's regexp stuff into a stand-alone
package like the original regex stuff, then I'll use it!

The g & o options are not supported in the m() functions.
I will try to support the 'g' option for m() in a list context.

SPStringList::m(exp, targ) and SPString::m(exp, list) are used to
simulate $&, $0 - $9 in perl. In both cases the list gets loaded with
the subexpression matches. The 0'th element is equivalent to $& in perl
and the 1'st element is equivalent to $1 etc.

Note that in the SPStringlist::m() member function, result lists are
appended whereas in SPString::m(s, list) 'list' is reset first.
eg
{
SPString s;
SPStringList l1, l2;

	s= "hello frobo goodbye";
	l1.push("was here first1"); l2.push("was here first2");
	s.m("(.*)frobo(.*)", l2); // Overwrites l with new list
	l1.m("(.*)frobo(.*)", s); // appends l with new list
// produces this result:
// l2[0] is "hello frobo goodbye"	// equiv of $&
// l2[1] is "hello "			// equiv of $1
// l2[2] is " goodbye"			//	    $2
// and
// l1[0] is "was here first"
// l1[1] is "hello frobo goodbye"	// equiv of $&
// l1[2] is "hello "			//          $1
// l1[3] is " goodbye"			//	    $2
// an l1.reset() preceding the l1.m() would get rid of l1[0] in the
// above example.	
}

To get the exact perl semantics of the m function in a list context
you can use the global m() function as follows:-
{
SPStringList sl;
sl = m("(..) (..)", "ab cd ef"); // sl[0] gets "ab", sl[1] gets "cd"
}

SP expressions (s/123/$&*2/e) in a substitute command
(SPString::s()) are obviously not done. However $& and $0-$9 are
correctly expanded and substituted.

Also remember that if you want to put a \ in the regular expression
then you must actually type \\ as the c compiler will interpret a \ for
you. What happens to things like \t is up to your compiler.


I/O
---
I/O is done using standard c++ streams. I think this is ok, although
some perl-ism maybe introduced one day.
eg to copy a text file a line at a time:-
{
ifstream fin("file1.txt");
ofstream fout("file2.txt");
SPString si;

    while(fin >> si) fout << si << endl;
}

This will read the entire file into a SPStringList:-
{
SPStringList l;
ifstream fin("file1.txt");

	fin >> l;
}

One nifty outcome of using streams this way is the following syntax
will load a SPStringList and SPList<T> in a reasonably compact
way:-
{
SPStringList slist;
strstream ss;
    ss << "one\n" << "two\nthree\nfour\n";
    ss >> slist; // creates a 4 element string list

strstream iss;
SPList<int> il;

    iss << "1 2 3 4 5 6 7 8 9 10" << endl; // quick load an integer array
    iss >> il; // creates a 10 element integer list
}


Iterators
---------
There is no class iterator per-se, but all lists (including Assoc) allow
an index to step through the list one by one. So iteration can be
achieved, albeit clumsily.
eg

SPList<int> intlist;

for(int i=0;i<inlist.scalar();i++){
	cout << intlist[i];
}

There is a header file called splistit.h that implements a simple iterator
and FOREACH macro using the above technique.

A SPList or SPStringList may be used in an if statement to test
if the list is empty or not.
eg
{
SPList<int> il;

	if(il) cout << "List is not empty" << endl;
	else il.push(1);
}

==========
Disclaimer
==========

This is a personal work, use as-is with no express or implied warranty and no 
responsibility for  misuse or problems.
