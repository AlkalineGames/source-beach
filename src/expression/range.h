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

#ifndef	_RANGE_H
#define	_RANGE_H

#include <cassert>
#include <iostream>

namespace expression
{

/*
 * Note this is an inclusive range where it goes
 * from start() to, and including, end()
 */
class range
{
private:
    int st, en, len;

public:
    range()
    {
	st=0; en= -1; len= 0;
    }

    range(int s, int e)
    {
	st= s; en= e; len= (en - st) + 1;
 	assert(st <= en && st >= 0);
    }

    // test validity of the range
    operator void *() { return (st <= en && st >= 0)? this : 0;}
    int start(void) const { return st;}
    int end(void) const { return en;}
    int length(void) const { return len;}

    void set(int a, int b)
    {
	st= a; en= b; len= (en - st) + 1;
 	assert(st <= en && st >= 0);
    }

    int operator<(const range& r) const // for sorting
    {
    	return ((st == r.st) ? (en < r.en) : (st < r.st));
    }

    // x++ operator extends end of range by one
    void operator++(int){ en++; len++; }

    // ++x operator extends start of range by one
    void operator++(void){ st++; len--; }

#if 0
    // Don't need these yet
    range operator&(const range& r) const // returns intersection of two ranges
    {
        range ret;
	if(en >= 0 && r.en >= 0 && (st <= r.en) && (en >= r.st)){  // if any overlap
            ret.st= (st > r.st) ? st : r.st;
            ret.en= (en < r.en) ? en : r.en;
        }
        return ret;
    }

    range operator|(const range& r) const // returns union of two ranges if consecutive
    {
        range ret;
        if(en >= 0 && r.en >= 0 && (st <= r.en+1) && (en >= r.st-1)){  // if any overlap or contiguous
            ret.st= (st < r.st) ? st : r.st;
            ret.en= (en > r.en) ? en : r.en;
        }
        return ret;
    }
#endif

    friend std::ostream& operator<<(std::ostream& os, const range& r)
    {
	os << r.st << " - " << r.en << " (" << ((r.en - r.st)+1) << ")";
        return os;
    }
};


//--------------------------------------

}; // end of namespace expression

#endif // _RANGE_H
