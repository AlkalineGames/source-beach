#if !defined(BEACH_EXPRESSION_REGULAR_EXPRESSION)
#define      BEACH_EXPRESSION_REGULAR_EXPRESSION
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       regular_expression.hpp
 *  @note       platform independent, Standard C++
 *  @author     David Ferguson
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <expression/range.h>

//--------------------------------------

/// Beach Expression Framework
namespace expression
{
	#define NSUBEXP  10
	typedef struct regexp {
		char *startp[NSUBEXP];
		char *endp[NSUBEXP];
		char regstart;		/* Internal use only. */
		char reganch;		/* Internal use only. */
		char *regmust;		/* Internal use only. */
		int regmlen;		/* Internal use only. */
		char program[1];	/* Unwarranted chumminess with compiler. */
	} regexp;


/* definition	number	opnd?	meaning */
#define	END	0	/* no	End of program. */
#define	BOL	1	/* no	Match "" at beginning of line. */
#define	EOL	2	/* no	Match "" at end of line. */
#define	ANY	3	/* no	Match any one character. */
#define	ANYOF	4	/* str	Match any character in this string. */
#define	ANYBUT	5	/* str	Match any character not in this string. */
#define	BRANCH	6	/* node	Match this alternative, or the next... */
#define	BACK	7	/* no	Match "", "next" ptr points backward. */
#define	EXACTLY	8	/* str	Match this string. */
#define	NOTHING	9	/* no	Match empty string. */
#define	STAR	10	/* node	Match this (simple) thing 0 or more times. */
#define	PLUS	11	/* node	Match this (simple) thing 1 or more times. */
#define	OPEN	20	/* no	Mark this point in input as start of #n. */
			/*	OPEN+1 is number 1, etc. */
#define	CLOSE	30	/* no	Analogous to OPEN. */

#define	OP(p)	(*(p))
#define	NEXT(p)	(((*((p)+1)&0377)<<8) + (*((p)+2)&0377))
#define	OPERAND(p)	((p) + 3)

/*
 * See regmagic.h for one further detail of program structure.
 */


/*
 * Utility definitions.
 */
#ifndef CHARBITS
#define	UCHARAT(p)	((int)*(unsigned char *)(p))
#else
#define	UCHARAT(p)	((int)*(p)&CHARBITS)
#endif

#define	FAIL(m)	{ regerror(m); return(NULL); }
#define	ISMULT(c)	((c) == '*' || (c) == '+' || (c) == '?')
#define	META	"^$.[()|?+*\\"

/*
 * Flags to be passed up and down.
 */
#define	HASWIDTH	01	/* Known never to match null string. */
#define	SIMPLE		02	/* Simple enough to be STAR/PLUS operand. */
#define	SPSTART		04	/* Starts with * or +. */
#define	WORST		0	/* Worst case. */


//--------------------------------------

/// regular expression wrapper
/**
 *  Our wrapper around another regular expression implementation
 */
class regular_expression
{
public:

    enum options {def=0, nocase=1};

    regular_expression(const char *rege, int ifl= 0);

    ~regular_expression();

    int match(const char *targ);

    int groups(void) const
    {
	int res= 0;
	for (int i=0; i<NSUBEXP; i++) {
	    if(repat->startp[i] == NULL) break;
	    res++;
	}
	return res;
    }

    range getgroup(int n) const
    {
	assert(n < NSUBEXP);
        if(repat->endp[n] == repat->startp[n]) // pointing to end of string
	        return range((int)(repat->startp[n] - (char *)target),
		             (int)(repat->endp[n] - (char *)target));
        else
                return range((int)(repat->startp[n] - (char *)target),
		             (int)(repat->endp[n] - (char *)target) - 1);
    }

private:
    regexp 		*repat;
    const char  *target; // only used as a base address to get an offset
    int res;
    int iflg;

	char *regparse;		/* Input-scan pointer. */
	int regnpar;		/* () count. */
	char regdummy;
	char *regcode;		/* Code-emit pointer; &regdummy = don't. */
	long regsize;		/* Code size. */

    char *reginput;		/* String-input pointer. */
    char *regbol;		/* Beginning of input, for ^ check. */
    char **regstartp;	/* Pointer to startp array. */
    char **regendp;		/* Ditto for endp. */

    void strlwr(char *s)
    {
	  while(*s){
	    *s= tolower(*s);
	    s++;
  	  }
    }
	int regexec(register regexp *prog, register char *string);
	void regc(char b);
	void regtail(char *p, char *val);
    char * regnext(register char *p);
	int regrepeat(char *p);
	int regtry(regexp *prog, char *string);
	int	regmatch(char *prog);
	regexp * regcomp(char *exp);
	char * reg(int paren, int *flagp);
	void reginsert(char op, char *opnd);
	void regoptail(char *p, char *val);
	char * regnode(char op);
	char * regbranch(int *flagp);
	char * regpiece(int *flagp);
	char * regatom(int *flagp);

	void regerror(char *s);

}; // end of class regular_expression

//--------------------------------------

}; // end of namespace atoms

//----------------------------------------------------------
#endif // BEACH_EXPRESSION_REGULAR_EXPRESSION
