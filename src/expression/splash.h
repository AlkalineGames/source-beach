/*
 * Version 1.91
 * Written by Jim Morris,  morris@netcom.com
 * Kudos to Larry Wall for inventing Perl
 * Copyrights only exist on the regex stuff, and all have been left intact.
 * The only thing I ask is that you let me know of any nifty fixes or
 * additions.
 *
 * Credits:
 * I'd like to thank Michael Golan <mg@Princeton.EDU> for his critiques
 * and clever suggestions. Some of which have actually been implemented
 */

#ifndef	_SPLASH_H
#define	_SPLASH_H

#include <expression/regular_expression.hpp>

#include "range.h"

#include <cstring>

#ifdef	DEBUG
#include	<stdio.h>
#endif

#define	INLINE	inline

namespace expression
{

	using std::cerr;
	using std::endl;
	using std::istream;
	using std::ostream;

	using expression::range;


//************************************************************
// This is the base class for SPList, it handles the underlying
// dynamic array mechanism
//************************************************************

template<class T>
class SPListBase
{
private:
    enum{ALLOCINC=20};
    T *a;
    int cnt;
    int first;
    int allocated;
    int allocinc;
    void grow(int amnt= 0, int newcnt= -1);

protected:
    void compact(const int i);

public:
#ifdef	USLCOMPILER
    // USL 3.0 bug with enums losing the value
    SPListBase(int n= 20)
#else
    SPListBase(int n= ALLOCINC)
#endif
    {
	a= new T[n];
	cnt= 0;
        first= n>>1;
	allocated= n;
	allocinc= n;
#	ifdef	DEBUG
	fprintf(stderr, "SPListBase(int %d) a= %p, first= %d\n", allocinc, a, first);
#	endif
    }

    SPListBase(const SPListBase<T>& n);
    SPListBase<T>& operator=(const SPListBase<T>& n);
    virtual ~SPListBase(){
#       ifdef	DEBUG
	fprintf(stderr, "~SPListBase() a= %p, allocinc= %d\n", a, allocinc);
#       endif
	delete [] a;
    }

    INLINE T& operator[](const int i);
    INLINE const T& operator[](const int i) const;

    int count(void) const{ return cnt; }

    void add(const T& n);
    void add(const int i, const T& n);
    void erase(void){ cnt= 0; first= (allocated>>1);}
};

// forward declarations
class SPStringList;
class Slice;
template <class T> class SPList;
template <class T> class SubList;

//************************************************************
// Slice class to keep track of, and create, slices
//************************************************************

#include <stdarg.h>
class Slice
{
private:
    SPList<range> *rl;

public:
    inline Slice();
    Slice(const char *); // parse the string to get a slice
    Slice(int n, ...); // list of indices to add to slice
    inline Slice(const Slice& slc);
    inline Slice(const range& r);
    inline ~Slice();

    inline int count(void) const;
    inline const range& operator[](int i) const;
    void add(int i); // add one element to slice
    friend ostream& operator<<(ostream&, const Slice&);
};

//************************************************************
// Allows assignment to slices of a list
//************************************************************

template <class T>
class SubList
{
private:
    // This has to be a pointer because we don't know the size of Splice
    // and there is a nasty cyclic interdependency between the next 3 classes
    Slice *sl; // because we may want to use a temp in call T/O convenience with efficiency
    SPList<T>& l;

public:
    SubList(SPList<T>& lst, const Slice& slc);
    SubList(SPList<T>& lst, int st, int len);
    SubList(SPList<T>& lst, const range& r);
    ~SubList();

    SubList<T>& operator=(const SPList<T>& lst);
    friend class SPList<T>;
};

//************************************************************
// SPList
//************************************************************

template <class T>
class SPList: private SPListBase<T>
{
public:

    SPList(int sz= 10): SPListBase<T>(sz){}
    SPList(const SubList<T>& sbl);

    // stuff I want public to see from SPListBase
    T& operator[](const int i){return SPListBase<T>::operator[](i);}
    const T& operator[](const int i) const{return SPListBase<T>::operator[](i);}
    SPListBase<T>::count;   // some compilers don't like this

    // add perl-like synonyms
    void reset(void){ this->erase(); }
    int scalar(void) const { return count(); }

    operator void*() { return count()?this:0; } // so it can be used in tests
    int isempty(void) const{ return !count(); } // for those that don't like the above (hi michael)

    T pop(void);

    void push(const T& a){ this->add(a);}
    void push(const SPList<T>& l);

    T shift(void);

    int unshift(const T& a){ this->add(0, a); return count(); }
    int unshift(const SPList<T>& l);

    SPList<T> reverse(void);
    SPList<T> sort();

    SPList<T> splice(int offset, int len, const SPList<T>& l);
    SPList<T> splice(int offset, int len);
    SPList<T> splice(int offset);

    SubList<T> operator()(int st, int len){return SubList<T>(*this, st, len);}
    SubList<T> operator()(const range& r){return SubList<T>(*this, r);}
    SubList<T> operator()(const Slice& slc){return SubList<T>(*this, slc);}
    SubList<T> operator()(const char *s);
};

//****************************************************************
// just a mechanism for self deleteing strings which can be hacked
//****************************************************************

class TempString
{
private:
    char *str;
public:
    TempString(const char *s)
    {
	str= new char[strlen(s) + 1];
        strcpy(str, s);
    }

    TempString(const char *s, int len)
    {
        str= new char[len + 1];
        if(len) strncpy(str, s, len);
        str[len]= '\0';
    }

    ~TempString(){ delete [] str; }

    operator char*() const { return str; }
};

//************************************************************
// This class takes care of the mechanism behind variable
// length strings
//************************************************************

class VarString
{
private:
    enum{ALLOCINC=32};
    char *a;
    int len;
    int allocated;
    int allocinc;
    INLINE void grow(int n= 0);

public:
#ifdef	USLCOMPILER
    // USL 3.0 bug with enums losing the value
    INLINE VarString(int n= 32);
#else
    INLINE VarString(int n= ALLOCINC);
#endif

    INLINE VarString(const VarString& n);
    INLINE VarString(const char *);
    INLINE VarString(const char* s, int n);
    INLINE VarString(char);

    ~VarString(){
#       ifdef	DEBUG
	fprintf(stderr, "~VarString() a= %p, allocinc= %d\n", a, allocinc);
#       endif
	delete [] a;
    }

    VarString& operator=(const VarString& n);
    VarString& operator=(const char *);

    INLINE const char operator[](const int i) const;
    INLINE char& operator[](const int i);

    operator const char *() const{ return a; }

    int length(void) const{ return len; }

    void add(char);
    void add(const char *);
    void add(int, const char *);
    void remove(int, int= 1);

    void erase(void){ len= 0; }
};

class SPStringList;

//************************************************************
// Implements the perl specific string functionality
//************************************************************

class SPString
{
private:
    VarString pstr;  // variable length string mechanism
    class substring;
    friend class substring;

public:

    SPString():pstr(){}
    SPString(const SPString& n) : pstr(n.pstr){}
    SPString(const char *s) : pstr(s){}
    SPString(const char c) : pstr(c){}
    SPString(const substring& sb) : pstr(sb.pt, sb.len){}

    SPString& operator=(const char *s){pstr= s; return *this;}
    SPString& operator=(const SPString& n);
    SPString& operator=(const substring& sb);

    operator const char*() const{return pstr;}
    const char operator[](int n) const{ return pstr[n]; }

    int length(void) const{ return pstr.length(); }

    char chop(void);

    int index(const SPString& s, int offset= 0);
    int rindex(const SPString& s, int offset= -1);
    substring substr(int offset, int len= -1);
    substring substr(const range& r){ return substr(r.start(), r.length());}

    int m(const char *, const char *opts=""); // the regexp match m/.../ equiv
    int m(regular_expression&);
    int m(const char *, SPStringList&, const char *opts="");
    int m(regular_expression&, SPStringList&);

    int tr(const char *, const char *, const char *opts="");
    int s(const char *, const char *, const char *opts="");

    SPStringList split(const char *pat= "[ \t\n]+", int limit= -1);

    int operator<(const SPString& s) const { return (strcmp(pstr, s) < 0); }
    int operator>(const SPString& s) const { return (strcmp(pstr, s) > 0); }
    int operator<=(const SPString& s) const { return (strcmp(pstr, s) <= 0); }
    int operator>=(const SPString& s) const { return (strcmp(pstr, s) >= 0); }
    int operator==(const SPString& s) const { return (strcmp(pstr, s) == 0); }
    int operator!=(const SPString& s) const { return (strcmp(pstr, s) != 0); }

    int operator<(const char *s) const { return (strcmp(pstr, s) < 0); }
    int operator>(const char *s) const { return (strcmp(pstr, s) > 0); }
    int operator<=(const char *s) const { return (strcmp(pstr, s) <= 0); }
    int operator>=(const char *s) const { return (strcmp(pstr, s) >= 0); }
    int operator==(const char *s) const { return (strcmp(pstr, s) == 0); }
    int operator!=(const char *s) const { return (strcmp(pstr, s) != 0); }

    friend int operator<(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) < 0); }
    friend int operator>(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) > 0); }
    friend int operator<=(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) <= 0); }
    friend int operator>=(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) >= 0); }
    friend int operator==(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) == 0); }
    friend int operator!=(const char *s, const SPString& sp)  { return (strcmp(s, sp.pstr) != 0); }

    SPString operator+(const SPString& s) const;
    SPString operator+(const char *s) const;
    SPString operator+(char c) const;
    friend SPString operator+(const char *s1, const SPString& s2);

    SPString& operator+=(const SPString& s){pstr.add(s); return *this;}
    SPString& operator+=(const char *s){pstr.add(s); return *this;}
    SPString& operator+=(char c){pstr.add(c); return *this;}

private:
    void insert(int pos, int len, const char *pt, int nlen);

    // This idea lifted from NIH class library -
    // to handle substring LHS assignment
    // Note if subclasses can't be used then take external and make
    // the constructors private, and specify friend SPString
    class substring
    {
    public:
        int pos, len;
	SPString& str;
	char *pt;
    public:
        substring(SPString& os, int p, int l) : str(os)
	{
	    if(p > os.length()) p= os.length();
	    if((p+l) > os.length()) l= os.length() - p;
	    pos= p; len= l;
	    if(p == os.length()) pt= 0; // append to end of string
	    else pt= &os.pstr[p];       // +++ WARNING this may be illegal as nested classes
	                                // can't access its enclosing classes privates!
	}

        void operator=(const SPString& s)
        {
            if(&str == &s){ // potentially overlapping
		VarString tmp(s);
		str.insert(pos, len, tmp, strlen(tmp));
	    }else str.insert(pos, len, s, s.length());
        }

        void operator=(const substring& s)
        {
	    if(&str == &s.str){ // potentially overlapping
		VarString tmp(s.pt, s.len);
		str.insert(pos, len, tmp, strlen(tmp));
	    }else str.insert(pos, len, s.pt, s.len);
        }

        void operator=(const char *s)
        {
            str.insert(pos, len, s, strlen(s));
        }
    };
};

//************************************************************
// SPStringList
//************************************************************

class SPStringList: public SPList<SPString>
{
public:
    SPStringList(int sz= 6):SPList<SPString>(sz){}
    // copy lists, need to duplicate all internal strings
    SPStringList(const SPStringList& n);

    SPStringList& operator=(const SPList<SPString>& n);

    int split(const char *str, const char *pat= "[ \t\n]+", int limit= -1);
    SPString join(const char *pat= " ");
    int m(const char *rege, const char *targ, const char *opts=""); // makes list of sub exp matches
    friend SPStringList m(const char *pat, const char *str, const char *opts);
    SPStringList grep(const char *rege, const char *opts=""); // trys rege against elements in list
};

//************************************************************
// Streams operators
//************************************************************

template <class T>
istream& operator>>(istream& ifs, SPList<T>& arr)
{
T a;
    // Should I reset arr first?
    arr.reset(); // I think so, to be consistent

    while(ifs >> a){
	arr.push(a);
//	cout << "<" << a << ">" << endl;
    };
    return ifs;
}

template <class T>
ostream& operator<<(ostream& os,  const SPList<T>& arr)
{

    for(int i=0;i<arr.count();i++){
#ifdef	TEST
	os << "[" << i << "]" << arr[i] << " ";
    }
    os << endl;
#else
	os << arr[i] << endl;
    }
#endif
    return os;
}

istream& operator>>(istream& ifs, SPString& s);
istream& operator>>(istream& ifs, SPStringList& sl);
ostream& operator<<(ostream& os,  const SPString& arr);
ostream& operator<<(ostream& os,  const SPStringList& arr);

//************************************************************
// Implementation of template functions for splistbase
//************************************************************

template <class T>
INLINE T& SPListBase<T>::operator[](const int i)
{
    assert((i >= 0) && (first >= 0) && ((first+cnt) <= allocated));
    int indx= first+i;

    if(indx >= allocated){  // need to grow it
	grow((indx-allocated)+allocinc, i+1); // index as yet unused element
	indx= first+i;			  // first will have changed in grow()
    }
    assert(indx >= 0 && indx < allocated);

    if(i >= cnt) cnt= i+1;  // it grew
    return a[indx];
}

template <class T>
INLINE const T& SPListBase<T>::operator[](const int i) const
{
     assert((i >= 0) && (i < cnt));
     return a[first+i];
}

template <class T>
SPListBase<T>::SPListBase(const SPListBase<T>& n)
{
    allocated= n.allocated;
    allocinc= n.allocinc;
    cnt= n.cnt;
    first= n.first;
    a= new T[allocated];
    for(int i=0;i<cnt;i++) a[first+i]= n.a[first+i];
#ifdef	DEBUG
    fprintf(stderr, "SPListBase(SPListBase&) a= %p, source= %p\n", a, n.a);
#endif

}

template <class T>
SPListBase<T>& SPListBase<T>::operator=(const SPListBase<T>& n){
//  cout << "SPListBase<T>::operator=()" << endl;
    if(this == &n) return *this;
#ifdef	DEBUG
    fprintf(stderr, "~operator=(SPListBase&) a= %p\n", a);
#endif
    delete [] a; // get rid of old one
    allocated= n.allocated;
    allocinc= n.allocinc;
    cnt= n.cnt;
    first= n.first;
    a= new T[allocated];
    for(int i=0;i<cnt;i++) a[first+i]= n.a[first+i];
#ifdef	DEBUG
    fprintf(stderr, "operator=(SPListBase&) a= %p, source= %p\n", a, n.a);
#endif
    return *this;
}
/*
** increase size of array, default means array only needs
** to grow by at least 1 either at the end or start
** First tries to re-center the first pointer
** Then will increment the array by the inc amount
*/
template <class T>
void SPListBase<T>::grow(int amnt, int newcnt){
int newfirst;

    if(amnt <= 0){ // only needs to grow by 1
        newfirst= (allocated>>1) - (cnt>>1); // recenter first
        if(newfirst > 0 && (newfirst+cnt+1) < allocated){ // this is all we need to do
            for(int i=0;i<cnt;i++){ // move rest up or down
                int idx= (first > newfirst) ? i : cnt-1-i;
                a[newfirst+idx]= a[first+idx];
	    }
#ifdef DEBUG
            fprintf(stderr, "SPListBase::grow() moved a= %p, first= %d, newfirst= %d, amnt= %d, cnt= %d, allocated= %d\n",
                    a, first, newfirst, amnt, cnt, allocated);
#endif
           first= newfirst;
           return;
        }
    }

    // that wasn't enough, so allocate more space
    if(amnt <= 0) amnt= allocinc; // default value
    if(newcnt < 0) newcnt= cnt;   // default
    allocated += amnt;
    T *tmp= new T[allocated];
    newfirst= (allocated>>1) - (newcnt>>1);
    for(int i=0;i<cnt;i++) tmp[newfirst+i]= a[first+i];
#ifdef	DEBUG
    fprintf(stderr, "SPListBase::grow() a= %p, old= %p, allocinc= %d, first= %d, amnt= %d, cnt= %d, allocated= %d\n",
            tmp, a, allocinc, first, amnt, cnt, allocated);
    fprintf(stderr, "~SPListBase::grow() a= %p\n", a);
#endif
    delete [] a;
    a= tmp;
    first= newfirst;
}

template <class T>
void SPListBase<T>::add(const T& n){
    if(cnt+first >= allocated) grow();
    assert((cnt+first) < allocated);
    a[first+cnt]= n;
#ifdef DEBUG
    fprintf(stderr, "add(const T& n): first= %d, cnt= %d, idx= %d, allocated= %d\n",
                first, cnt, first+cnt, allocated);
#endif
    cnt++;
}

template <class T>
void SPListBase<T>::add(const int ip, const T& n){
    assert(ip >= 0 && ip <= cnt);
    if(ip == 0){ // just stick it on the bottom
    	if(first <= 0) grow(); // make room at bottom for one more
    	assert(first > 0);
        first--;
        a[first]= n;
    }else{
        if((first+cnt+1) >= allocated) grow(); // make room at top for one more
        assert((first+cnt) < allocated && (first+ip) < allocated);
        for(int i=cnt;i>ip;i--) // shuffle up
	    a[first+i]= a[(first+i)-1];
        a[first+ip]= n;
    }
#ifdef DEBUG
    fprintf(stderr, "add(const int ip, const T& n): first= %d, cnt= %d, idx= %d, allocated= %d\n",
                first, cnt, first+ip, allocated);
#endif
    cnt++;
}

template <class T>
void SPListBase<T>::compact(const int n){ // shuffle down starting at n
int i;
    assert((n >= 0) && (n < cnt));
    if(n == 0) first++;
    else for(i=n;i<cnt-1;i++){
	    a[first+i]= a[(first+i)+1];
    }
    cnt--;
}

//************************************************************
// implementation of template functions for SPList
//************************************************************
template <class T>
T SPList<T>::pop(void)
{
T tmp;
int n= count()-1;
    if(n >= 0){
	tmp= (*this)[n];
	this->compact(n);
    }
    return tmp;
}

template <class T>
T SPList<T>::shift(void)
{
T tmp= (*this)[0];
    this->compact(0);
    return tmp;
}

template <class T>
void SPList<T>::push(const SPList<T>& l)
{
    for(int i=0;i<l.count();i++)
	this->add(l[i]);
}

template <class T>
int SPList<T>::unshift(const SPList<T>& l)
{
    for(int i=l.count()-1;i>=0;i--)
	unshift(l[i]);
    return count();
}

template <class T>
SPList<T> SPList<T>::reverse(void)
{
    SPList<T> tmp;
    for(int i=count()-1;i>=0;i--)
	tmp.add((*this)[i]);

    return tmp;
}

template <class T>
SPList<T> SPList<T>::sort(void)
{
SPList<T> tmp(*this);
int n= tmp.scalar();

    for(int i=0;i<n-1;i++)
	for(int j=n-1;i<j;j--)
	    if(tmp[j] < tmp[j-1]){
		T temp = tmp[j];
		tmp[j] = tmp[j-1];
		tmp[j-1]= temp;
	    }

    return tmp;
}

template <class T>
SPList<T> SPList<T>::splice(int offset, int len, const SPList<T>& l)
{
SPList<T> r= splice(offset, len);

    if(offset > count()) offset= count();
    for(int i=0;i<l.count();i++){
	this->add(offset+i, l[i]);	// insert into list
    }
    return r;
}

template <class T>
SPList<T>  SPList<T>::splice(int offset, int len)
{
SPList<T> r;
int i;

    if(offset >= count()) return r;
    for(i=offset;i<offset+len;i++){
    	r.add((*this)[i]);
    }

    for(i=offset;i<offset+len;i++)
	this->compact(offset);
    return r;
}

template <class T>
SPList<T>  SPList<T>::splice(int offset)
{
SPList<T> r;
int i;

    if(offset >= count()) return r;
    for(i=offset;i<count();i++){
	r.add((*this)[i]);
    }

    int n= count(); // count() will change so remember what it is
    for(i=offset;i<n;i++)
	this->compact(offset);
    return r;
}

template <class T>
SubList<T> SPList<T>::operator()(const char *s)
{
    return SubList<T>(*this, Slice(s));
}
//************************************************************
// VarString Implementation
//************************************************************

INLINE VarString::VarString(int n)
{
    a= new char[n];
    *a= '\0';
    len= 0;
    allocated= n;
    allocinc= n;
#   ifdef	DEBUG
    fprintf(stderr, "VarString(int %d) a= %p\n", allocinc, a);
#   endif
}

INLINE VarString::VarString(const char* s)
{
    int n= strlen(s) + 1;
    a= new char[n];
    strcpy(a, s);
    len= n-1;
    allocated= n;
    allocinc= ALLOCINC;
#   ifdef	DEBUG
    fprintf(stderr, "VarString(const char *(%d)) a= %p\n", allocinc, a);
#   endif
}

INLINE VarString::VarString(const char* s, int n)
{
    a= new char[n+1];
    if(n) strncpy(a, s, n);
    a[n]= '\0';
    len= n;
    allocated= n+1;
    allocinc= ALLOCINC;
#   ifdef	DEBUG
    fprintf(stderr, "VarString(const char *, int(%d)) a= %p\n", allocinc, a);
#   endif
}

INLINE VarString::VarString(char c)
{
    int n= 2;
    a= new char[n];
    a[0]= c; a[1]= '\0';
    len= 1;
    allocated= n;
    allocinc= ALLOCINC;
#   ifdef	DEBUG
    fprintf(stderr, "VarString(char (%d)) a= %p\n", allocinc, a);
#   endif
}


INLINE ostream& operator<<(ostream& os,  const VarString& arr)
{
#ifdef TEST
    os << "(" << arr.length() << ")" << (const char *)arr;
#else
    os << (const char *)arr;
#endif

    return os;
}

INLINE const char VarString::operator[](const int i) const
{
     assert((i >= 0) && (i < len) && (a[len] == '\0'));
     return a[i];
}

INLINE char& VarString::operator[](const int i)
{
     assert((i >= 0) && (i < len) && (a[len] == '\0'));
     return a[i];
}

INLINE VarString::VarString(const VarString& n)
{
    allocated= n.allocated;
    allocinc= n.allocinc;
    len= n.len;
    a= new char[allocated];
    strcpy(a, n.a);
#ifdef	DEBUG
    fprintf(stderr, "VarString(VarString&) a= %p, source= %p\n", a, n.a);
#endif

}

//************************************************************
// Sublist and Slice stuff
//************************************************************

template <class T>
SubList<T>::SubList(SPList<T>& lst, const Slice& slc) : l(lst)
{
    sl= new Slice(slc);
}

template <class T>
SubList<T>::SubList(SPList<T>& lst, int st, int len) : l(lst)
{
    sl= new Slice(range(st, st+len-1));
}

template <class T>
SubList<T>::SubList(SPList<T>& lst, const range& r) : l(lst)
{
    sl= new Slice(r);
}

template <class T>
SubList<T>::~SubList()
{
    delete sl;
}

template <class T>
SubList<T>& SubList<T>::operator=(const SPList<T>& lst)
{
int n= 0;
    for(int i=0;i<sl->count();i++){
	for(int j=(*sl)[i].start();j<=(*sl)[i].end();j++){
            if(n < lst.count()) l[j]= lst[n++];
        }
    }
    return *this;
}

template <class T>
SPList<T>::SPList(const SubList<T>& sbl)
{
    for(int i=0;i<sbl.sl->count();i++){
	for(int j=(*sbl.sl)[i].start();j<=(*sbl.sl)[i].end();j++)
	    (*this).push(sbl.l[j]);
    }
}

//************************************************************
// Slice inline stuff
//************************************************************

inline Slice::Slice(const range& r)
{
    rl= new SPList<range>;
    rl->push(r);
}

inline Slice::Slice()
{
    rl= new SPList<range>;
}

inline Slice::Slice(const Slice& slc)
{
    rl= new SPList<range>(*slc.rl);
}


inline Slice::~Slice()
{
    delete rl;
}

inline int Slice::count(void) const
{
    return rl->count();
}

inline const range& Slice::operator[](int i) const
{
    return (*rl)[i];
}


// For Old-timers compatibility
typedef SPStringList PerlStringList;
typedef SPString PerlString;
#define PerlList SPList


//--------------------------------------

}; // end of namespace expression

#endif // _SPLASH_H
