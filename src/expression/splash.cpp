/*
 * Version 1.91
 * Written by Jim Morris,  morris@netcom.com
 * Kudos to Larry Wall for inventing Perl
 * Copyrights only exist on the regex stuff,  and all
 * have been left intact.
 * The only thing I ask is that you let me know of any nifty fixes or
 * additions.
 * Credits:
 * I'd like to thank Michael Golan <mg@Princeton.EDU> for his critiques
 * and clever suggestions. Some of which have actually been implemented
 */

//--------------------------------------
//  Modifications by World Fusion
//--------------------------------------
//  2004.10.03: removed include of
//              <malloc.h> because FreeBSD
//              says malloc is provided by
//              <stdlib.h>h
//
//  1997.09.28: changed include of
//              <iostream.h> to <iostream>
//              and added using std::cout
//--------------------------------------

#include "splash.h"

#include <atoms/stringex.hpp>

#include <cstdlib>

namespace expression
{
    using atoms::stringex;
	using expression::range;
    using std::cout;

//************************************************************
// VarString Implementation
//************************************************************

VarString& VarString::operator=(const char *s)
{
    int nl= strlen(s);
    if(nl+1 >= allocated) grow((nl-allocated)+allocinc);
    assert(allocated > nl+1);
    strcpy(a, s);
    len= nl;
    return *this;
}

VarString& VarString::operator=(const VarString& n)
{
    if(this != &n){
	if(n.len+1 >= allocated){ // if it is not big enough
#	    ifdef	DEBUG
	    fprintf(stderr, "~operator=(VarString&) a= %p\n", a);
#	    endif
	    delete [] a; // get rid of old one
	    allocated= n.allocated;
	    allocinc= n.allocinc;
	    a= new char[allocated];
#	    ifdef	DEBUG
	    fprintf(stderr, "operator=(VarString&) a= %p, source= %p\n", a, n.a);
#	    endif
	}
        len= n.len;
	strcpy(a, n.a);
    }
    return *this;
}

void VarString::grow(int n)
{
    if(n == 0) n= allocinc;
    allocated += n;
    char *tmp= new char[allocated];
    strcpy(tmp, a);
#ifdef	DEBUG
    fprintf(stderr, "VarString::grow() a= %p, old= %p, allocinc= %d\n", tmp, a, allocinc);
    fprintf(stderr, "~VarString::grow() a= %p\n", a);
#endif
    delete [] a;
    a= tmp;
}

void VarString::add(char c)
{
    if(len+1 >= allocated) grow();
    assert(allocated > len+1);
    a[len++]= c; a[len]= '\0';
}

void VarString::add(const char *s)
{
    int nl= strlen(s);
    if(len+nl >= allocated) grow(((len+nl)-allocated)+allocinc);
    assert(allocated > len+nl);
    strcat(a, s);
    len+=nl;
}

void VarString::add(int ip, const char *s)
{
    int nl= strlen(s);
    if(len+nl >= allocated) grow(((len+nl)-allocated)+allocinc);
    assert(allocated > len+nl);
    memmove(&a[ip+nl], &a[ip], (len-ip)+1); // shuffle up
    memcpy(&a[ip], s, nl);
    len+=nl;
    assert(a[len] == '\0');
}

void VarString::remove(int ip, int n)
{
    assert(ip+n <= len);
    memmove(&a[ip], &a[ip+n], (len-ip)-n+1); // shuffle down
    len-=n;
    assert(a[len] == '\0');
}

//************************************************************
// SPString stuff
//************************************************************

// assignments
SPString& SPString::operator=(const SPString& n)
{
    if(this == &n) return *this;
    pstr= n.pstr;
    return *this;
}

SPString& SPString::operator=(const substring& sb)
{
    VarString tmp(sb.pt, sb.len);
    pstr= tmp;
    return *this;
}

// concatenations
SPString SPString::operator+(const SPString& s) const
{
    SPString ts(*this);
    ts.pstr.add(s);
    return ts;
}

SPString SPString::operator+(const char *s) const
{
    SPString ts(*this);
    ts.pstr.add(s);
    return ts;
}

SPString SPString::operator+(char c) const
{
    SPString ts(*this);
    ts.pstr.add(c);
    return ts;
}

SPString operator+(const char *s1, const SPString& s2)
{
    SPString ts(s1);
    ts = ts + s2;
//    cout << "s2[0] = " << s2[0] << endl; // gives incorrect error
    return ts;
}

//************************************************************
// other stuff
//************************************************************

char SPString::chop(void)
{
    int n= length();
    if(n <= 0) return '\0'; // empty
    char tmp= pstr[n-1];
    pstr.remove(n-1);
    return tmp;
}

int SPString::index(const SPString& s, int offset)
{
    if(offset < 0) offset= 0;
    for(int i=offset;i<length();i++){
	if(strncmp(&pstr[i], s, s.length()) == 0) return i;
    }

    return -1;
}

int SPString::rindex(const SPString& s, int offset)
{
    if(offset == -1) offset= length()-s.length();
    else offset= offset-s.length()+1;
    if(offset > length()-s.length()) offset= length()-s.length();

    for(int i=offset;i>=0;i--){
	if(strncmp(&pstr[i], s, s.length()) == 0) return i;
    }
    return -1;
}

SPString::substring SPString::substr(int offset, int len)
{
    if(len == -1) len= length() - offset; // default use rest of string
    if(offset < 0){
	offset= length() + offset;  // count from end of string
	if(offset < 0) offset= 0;   // went too far, adjust to start
    }
    return substring(*this, offset, len);
}

// this is private
// it shrinks or expands string as required
void SPString::insert(int pos, int len, const char *s, int nlen)
{
    if(pos < length()){ // nothing to delete if not true
	if((len+pos) > length()) len= length() - pos;
	pstr.remove(pos, len);  // first remove subrange
    }else pos= length();

    VarString tmp(s, nlen);
    pstr.add(pos, tmp);	    // then insert new substring
}

int SPString::m(regular_expression& r)
{
    return r.match(*this);
}

int SPString::m(const char *pat, const char *opts)
{
int iflg= strchr(opts, 'i') != NULL;
    regular_expression r(pat, iflg?regular_expression::nocase:0);
    return m(r);
}

int SPString::m(regular_expression& r, SPStringList& psl)
{

    //logger::acquire_default_instance().log_error(
    //    "SPString", "m(regular_expression& r, SPStringList& psl)","IN");

    if(!r.match(*this))
    {
    //logger::acquire_default_instance().log_error(
    //    "SPString", "m(regular_expression& r, SPStringList& psl)","OUT A");
		return 0;
	}
    psl.reset();    // clear it first
    range rng;
    for (int i=0; i<r.groups(); i++){
        rng= r.getgroup(i);
	psl.push(substr(rng.start(), rng.length()));
    }
    //logger::acquire_default_instance().log_error(
    //    "SPString", "m(regular_expression& r, SPStringList& psl)","OUT B");

    return r.groups();
}


int SPString::m(const char *pat, SPStringList& psl, const char *opts)
{
int iflg= strchr(opts, 'i') != NULL;
    regular_expression r(pat, iflg?regular_expression::nocase:0);
    return m(r, psl);
}

//
// I know! This is not fast, but it works!!
//
int SPString::tr(const char *sl, const char *rl, const char *opts)
{
    if(length() == 0 || strlen(sl) == 0) return 0;

    int cflg= strchr(opts, 'c') != NULL; // thanks Michael
    int dflg= strchr(opts, 'd') != NULL;
    int sflg= strchr(opts, 's') != NULL;

    int i, cnt= 0, flen= 0;
    SPString t;
    unsigned char lstc= '\0', fr[256];

    // build search array, which is a 256 byte array that stores the index+1
    // in the search string for each character found, == 0 if not in search
    memset(fr, 0, 256);
    for(i=0;i<strlen(sl);i++){
	if(i && sl[i] == '-'){ // got a range
	    assert(i+1 < strlen(sl) && lstc <= sl[i+1]); // sanity check
	    for(unsigned char c=lstc+1;c<=sl[i+1];c++){
		fr[c]= ++flen;
	    }
	    i++; lstc= '\0';
	}else{
	    lstc= sl[i];
	    fr[sl[i]]= ++flen;
	}
    }

    int rlen;
    // build replacement list
    if((rlen=strlen(rl)) != 0){
	for(i=0;i<rlen;i++){
	    if(i && rl[i] == '-'){ // got a range
		assert(i+1 < rlen && t[t.length()-1] <= rl[i+1]); // sanity check
		for(char c=t[i-1]+1;c<=rl[i+1];c++) t += c;
		i++;
	    }else t += rl[i];
	}
    }

    // replacement string that is shorter uses last character for rest of string
    // unless the delete option is in effect or it is empty
    while(!dflg && rlen && flen > t.length()){
	t += t[t.length()-1]; // duplicate last character
    }

    rlen= t.length(); // length of translation string

    // do translation, and deletion if dflg (actually falls out of length of t)
    // also squeeze translated characters if sflg

    SPString tmp; // need this in case dflg, and string changes size
    for(i=0;i<length();i++){
	int off;
	if(cflg){ // complement, ie if NOT in f
	    char rc= !dflg ? t[t.length()-1] : '\0'; // always use last character for replacement
	    if((off=fr[(*this)[i]]) == 0){ // not in map
		cnt++;
		if(!dflg && (!sflg || tmp.length() == 0 || tmp[tmp.length()-1] != rc))
		    tmp += rc;
	    }else tmp += (*this)[i]; // just stays the same
	}else{ // in fr so substitute with t, if no equiv in t then delete
	    if((off=fr[(*this)[i]]) > 0){
		off--; cnt++;
		if(rlen==0 && !dflg && (!sflg || tmp.length() == 0 || tmp[tmp.length()-1] != (*this)[i])) tmp += (*this)[i]; // stays the same
		else if(off < rlen && (!sflg || tmp.length() == 0 || tmp[tmp.length()-1] != t[off]))
		    tmp += t[off]; // substitute
	    }else tmp += (*this)[i]; // just stays the same
	}
    }

    *this= tmp;
    return cnt;
}

int SPString::s(const char *exp, const char *repl, const char *opts)
{
int gflg= strchr(opts, 'g') != NULL;
int iflg= strchr(opts, 'i') != NULL;
int cnt= 0;
regular_expression re(exp, iflg?regular_expression::nocase:0);
range rg;

    if(re.match(*this)){
	// OK I know, this is a horrible hack, but it seems to work
	if(gflg){ // recursively call s() until applied to whole string
	    rg= re.getgroup(0);
	    if(rg.end()+1 < length()){
		SPString st(substr(rg.end()+1));
//		cout << "Substring: " << st << endl;
		cnt += st.s(exp, repl, opts);
		substr(rg.end()+1)= st;
//		cout << "NewString: " << *this << endl;
	    }
	}

	if(!strchr(repl, '$')){ // straight, simple substitution
	    rg= re.getgroup(0);
	    substr(rg.start(), rg.length())= repl;
	    cnt++;
	}else{ // need to do subexpression substitution
	    char c;
	    const char *src= repl;
	    SPString dst;
	    int no;
	    while ((c = *src++) != '\0') {
		if(c == '$' && *src == '&'){
		    no = 0; src++;
		}else if(c == '$' && '0' <= *src && *src <= '9')
		    no = *src++ - '0';
		else no = -1;

		if(no < 0){	/* Ordinary character. */
		    if(c == '\\' && (*src == '\\' || *src == '$'))
			c = *src++;
		    dst += c;
		}else{
		    rg= re.getgroup(no);
		    dst += substr(rg.start(), rg.length());
		}
	    }
	    rg= re.getgroup(0);
	    substr(rg.start(), rg.length())= dst;
	    cnt++;
	}

	return cnt;
    }
    return cnt;
}

SPStringList SPString::split(const char *pat, int limit)
{
SPStringList l;

    l.split(*this, pat, limit);
    return l;
}

//************************************************************
// SPStringList stuff
//************************************************************

int SPStringList::split(const char *str, const char *pat, int limit)
{
regular_expression re(pat);
range rng;
SPString s(str);
int cnt= 1;

    if(*pat == '\0'){ // special empty string case splits entire thing
	while(*str){
	    s= *str++;
	    push(s);
	}
	return count();
    }

    if(stringex( pat ) == "' '"){ // special awk case
	char *p, *ws= " \t\n";
	TempString t(str); // can't hack users data
	p= strtok(t, ws);
	while(p){
	    push(p);
	    p= strtok(NULL, ws);
	}
	return count();
    }

    while(re.match(s) && (limit < 0 || cnt < limit)){ // find separator
	rng= re.getgroup(0); // full matched string (entire separator)
	push(s.substr(0, rng.start()));
	for(int i=1;i<re.groups();i++){
	    push(s.substr(re.getgroup(i))); // add subexpression matches
	}

	s= s.substr(rng.end()+1);
	cnt++;
    }
    if(s.length()) push(s);

    if(limit < 0){ // strip trailing null entries
	int off= count()-1;
	while(off >= 0 && (*this)[off].length() == 0){
	    off--;
	}
	splice(off+1);
    }
    return count();
}

SPString SPStringList::join(const char *pat)
{
SPString ts;

    for(int i=0;i<count();i++){
	ts += (*this)[i];
	if(i<count()-1) ts += pat;
    }
    return ts;
}


SPStringList::SPStringList(const SPStringList& n)
{
    for(int i=0;i<n.count();i++){
	push(n[i]);
    }
}

SPStringList& SPStringList::operator=(const SPList<SPString>& n)
{
    if(this == &n) return *this;
    // erase old one
    reset();

    for(int i=0;i<n.count();i++){
	push(n[i]);
    }
    return *this;
}

int SPStringList::m(const char *rege, const char *targ, const char *opts)
{
int iflg= strchr(opts, 'i') != NULL;
regular_expression r(rege, iflg?regular_expression::nocase:0);
    if(!r.match(targ)) return 0;
    range rng;
    for (int i=0; i<r.groups(); i++){
        rng= r.getgroup(i);
	push(SPString(targ).substr(rng.start(), rng.length()));
    }
    return r.groups();
}

SPStringList SPStringList::grep(const char *rege, const char *opts)
{
SPStringList rt;
int iflg= strchr(opts, 'i') != NULL;

    regular_expression rexp(rege, iflg?regular_expression::nocase:0);    // compile once
    for(int i=0;i<count();i++){
    	if(rexp.match((*this)[i])){
	    rt.push((*this)[i]);
	}
    }
    return rt;
}

#if 1
SPStringList m(const char *pat, const char *str, const char *opts)
{
SPStringList l;
    l.m(pat, str, opts);
    l.shift(); // remove the first element which would be $&
    return l;
}
#endif
//************************************************************
// streams stuff
//************************************************************

istream& operator>>(istream& ifs, SPString& s)
{
char c;
#if 0
char buf[40];
#else
char buf[132];
#endif

    s= ""; // empty string
/*
    !!! DISABLED BECAUSE THIS IS CAUSING BLANK LINES TO FAIL
    !!! AND NEVER ADVANCE THE STREAM POSITION [cat 2003.02.01]
    ifs.get(buf, sizeof buf);
    // This is tricky because a line teminated by end of file that is not terminated
    // with a '\n' first is considered an OK line, but ifs.good() will fail.
    // This will correctly return the last line if it is terminated by eof with the
    // stream still in a non-fail condition, but at eof, so next call will fail as
    // expected
    if(ifs){ 		// previous operation was ok
        s += buf; 	// append buffer to string
*/
//	cout << "<" << buf << ">" << endl;
	// if its a long line continue appending to string
	while( ifs.good() && (c=ifs.get() ) != '\n')
    {
//	    cout << "eof1= " << ifs.eof() << endl;
	    ifs.putback(c);
//          cout << "eof2= " << ifs.eof() << endl;
	    if(ifs.get(buf, sizeof buf)) 
        {
            // if last character is \r (carriage return, strip it)
            // animations ended up having carriage returns [dave] 4/21/06
            s += buf; // append to line
            if (s.length()>1 && s[s.length()-1]=='\r') 
            {
                s=s.substr(0,s.length()-1);
            }
        }
    }
    return ifs;
}

istream& operator>>(istream& ifs, SPStringList& sl)
{
SPString s;

    // Should I reset sl first?
    sl.reset(); // I think so, to be consistent

    while(ifs >> s){
	sl.push(s);
//	cout << "<" << s << ">" << endl;
    };
    return ifs;
}

ostream& operator<<(ostream& os,  const SPString& arr)
{
#ifdef TEST
    os << "(" << arr.length() << ")" << "\"";
    os << (const char *)arr;
    os << "\"";
#else
    os << (const char *)arr;
#endif
    return os;
}

ostream& operator<<(ostream& os,  const SPStringList& arr)
{

    for(int i=0;i<arr.count();i++)
#ifdef TEST
	os << "[" << i << "]" << arr[i] << endl;
#else
	os << arr[i] << endl;
#endif
    return os;
}

//************************************************************
// Slice stuff
//************************************************************

// a..b is range a thru b
// a-b is also range a thru b
// a,b,c is a and b and c
Slice::Slice(const char *s)
{
SPStringList sl;
SPString sep;
int i1, i2;

    rl= new SPList<range>;
    sl.split(s, "([-,]|\\.\\.)"); // split on separators and save them
//    cout << sl << endl;

    while(sl){
	i1= atoi(sl.shift()); // +++ should check it is a valid number
        if(sl){
	    sep= sl.shift(); // get separator
            if(sep == "-" || sep == ".."){ // its a range
		if(sl.isempty()){ // check there is more
                    cerr << "\nError in Slice, bad range in string: " << s << endl;
		    return;
                }
		i2= atoi(sl.shift()); // +++ get end of range
                rl->push(range(i1, i2)); // +++ Should see if range is reversed, or contiguous
                if(sl && (sep=sl.shift()) != ","){
                    cerr << "\nError in Slice, range not terminated correctly in string: "
                         << s << " by: " << sep << endl;
                }
            }else if(sep == ","){ // its a single
		add(i1);
            }else{ // oops
            	cerr << "\nError in Slice, bad separator in string: " << s
		     << "at: " << sep << endl;
                return;
            }
        }else add(i1); // last one must be a single
    }
    cout << *this << endl;
}

void Slice::add(int i)
{
int n= rl->count()-1;
    // if and only if this index is one greater than the previous on
    if(n >= 0 && (*rl)[n].end() == i-1){ // extend end of range by 1
	((*rl)[n])++;
    }else rl->push(range(i, i));
}

// a list of at least one indices, terminated by -1
Slice::Slice(int n, ...)
{
va_list ap;
int arg;
va_start(ap, n);

    rl= new SPList<range>;
    add(n);
    while((arg=va_arg(ap, int)) >= 0){
	add(arg);
    }
    va_end(ap);
}

ostream& operator<<(ostream& os, const Slice& sl)
{
    for(int i=0;i<sl.rl->count();i++){
        os << (*sl.rl)[i] << endl;
    }
    return os;
}

#ifdef __TURBOC__
int regular_expression::groups(void) const
{
    int res= 0;
    for (int i=0; i<NSUBEXP; i++) {
	if(repat->startp[i] == NULL) break;
	res++;
    }
    return res;
}
#endif

}; // end of namespace expression
