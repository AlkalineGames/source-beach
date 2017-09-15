/*
 * Simple program to read STDIN and justify the text to the
 * specified number of columns and output to STDOUT.
 * The padding is alternated from line to line so as to look even.
 * Blank lines in the input stream are preserved.
 * This was designed to be used as a filter.
 * As with fmt(1) indents are preserved, this can be disabled
 * with an option.
 * Also a change in indent level will be treated as the end of a 
 * stream, so no words on the following line will be wrapped up to
 * the current line.
 */

#include    <iostream.h>
#include    <stdlib.h>
#include    <ctype.h>

#include    "expression.h"
#include    "tracer.h"

// Some useful synonyms
typedef SPString Str;
typedef SPStringList StrList;

int tog= 0;

static int nextnonspace(const Str& s, int n)
{
    while(n < s.length() && s[n] == ' ') n++;    
    return n;
}

static int prevnonspace(const Str& s, int n)
{
    while(n >= 0 && s[n] == ' ') n--;    
    return n;
}

void justify(Str& ln, int width)
{
TRACER("justify(Str ln, int width)")
    LTRACE(2, ln)
    int p, o= tog?0:ln.length();
    while(ln.length() < width){
	if(tog){ // left to right pad
	    p= ln.index(" ", o); // find a space
	    if(p > 0){
		ln.substr(p, 0)= " "; // insert a space
		o= nextnonspace(ln, p); // start from next non-space
	    }else if(o) o= 0; // reset
	    else ln += " "; // put at end of line
	}else{ // right to left pad
	    p= ln.rindex(" ", o); // find a space
	    if(p > 0){
		ln.substr(p, 0)= " "; // insert a space
		o= prevnonspace(ln, p); // start from previous non-space
	    }else if(o != ln.length()) o= ln.length(); // reset
	    else ln += " "; // put at end of line
	}	
    }
    tog ^= 1;
}

void Usage()
{
    cout << "Usage: justify [-i] [width]" << endl;
    cout << "\t-i ignores leading whitespace" << endl;
    cout << "\twidth is the line width, default is 79" << endl;
    exit(1);
}

int main(int argc,  char **argv)
{
FTRACER("main()", 0, cout)
Str inl, curln, curword;
StrList words;
int width= 79, wwidth, ignorews= 0, lastindent= 0;
Str lws;	// leading whitespace
StrList ARGS;

    for(int i=1;i<argc;i++){ // load args
	ARGS.push(argv[i]);
    }
    
    while(ARGS){ // process them
	Str arg= ARGS.shift();
	if(arg == "-i") ignorews= 1;
	else if(arg == "-x") TRACE_ON
	else if(isdigit(arg[0])) width= atoi(arg);
	else Usage();
    }
	
    while(cin >> inl){
	LTRACE(2, inl)

	if(inl.length() == 0){ // honour existing blank lines
	    if(curln.length()){
		if(lws.length()) cout << lws; // leading space
		cout << curln << endl; // flush previous line
	    }
	    cout << endl; // output blank line
	    curln= "";
	    continue;
	}

	if(!ignorews){ // don't ignore leading whitespace
	    StrList t= m("^([ \t]+)", inl); // get leading whitespace
	    LTRACE(4, "Length = " << t[0].length());
    	    if(t){
		int l= 0;
		for(int i=0;i<t[0].length();i++){ // expand tabs
		    if(t[0][i] == '\t') l= l + (8 - l%8);
		    else l++;
		}
		wwidth= width - l;
	    }else wwidth= width;
	    if(wwidth != lastindent && curln.length()){ // indent changed, flush line
		if(lws.length()) cout << lws; // leading space
		cout << curln << endl; // flush previous line
		curln= "";
	    }
	    lastindent= wwidth;
	    lws= t[0];
	}else wwidth= width;
	
    	words.push(inl.split("' '")); // put at end of word FIFO
	LTRACE(2, words)
	while(words){
	    if(curln.length() == 0){
		curln= words.shift(); // get first word
	    }
	    while(curln.length() < wwidth){
		if(!words) break; // need to refill FIFO
		curword= words.shift(); // next word
		if(curln.length() + curword.length() + 1 > wwidth){
		    words.unshift(curword); // put it back
		    justify(curln, wwidth); // pads with spaces to width
		}else curln += (" " + curword); // add word to line
	    }
	    if(curln.length() >= wwidth){ // done with this line
		if(lws.length()) cout << lws; // leading space
		cout << curln << endl;
		curln= "";
	    }
	}
    }
    if(curln.length()){
	if(lws.length()) cout << lws; // leading space
	cout << curln << endl;
    }
}
