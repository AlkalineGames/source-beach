/*
// do the ini thing properly
// Usage: setini file section item value
// +value appends value
// -value removes value
// =value or value replaces entire item
// value==nothing just leaves value blank
// +item uncomments an item
// -item comments out an item
*/

#include	<fstream.h>
#include	<stdlib.h>
#include        <stdio.h>

#include	"expression.h"

#include	"splistit.h"

SPStringList append(const SPString& v, const SPStringList& vs)
{
SPString a= v, b;
SPStringList n;

    a.tr("A-Z", "a-z"); // make lowercase
	for(SPListIter<SPString> t(vs);t;++t){ // see if already in there
	    b= *t(); b.tr("A-Z", "a-z");
	    if(a != b) n.push(*t());
	}
	n.push(v);  // add it to the end
	return n;
}

SPStringList remove(const SPString& v, const SPStringList& vs)
{
SPString a= v, b;
SPStringList n;

    a.tr("A-Z", "a-z"); // make lowercase
    FOREACH(SPString, t, vs){
	    b= t; b.tr("A-Z", "a-z");
	    if(a != b) n.push(t);
	}
	ENDFOREACH
	return n;
}

void main(int argc, char **argv)
{
SPString fn, sec, item, infn, outfn;
SPStringList values;

    if(argc < 5){
        cerr << "Usage: setini file section [+|-]item [+|-|=]value [value]..." << endl;
        cerr << "\t+value appends value to item" << endl;
        cerr << "\t-value removes value from item" << endl;
        cerr << "\t=value or value replaces entire item" << endl;
        cerr << "\tif value==nothing just leaves value blank" << endl;
        cerr << "\t+item uncomments an item" << endl;
        cerr << "\t-item comments out an item" << endl;
        exit(1);
    }

    fn= argv[1]; sec= argv[2]; item= argv[3];
    for(int j=4;j<argc;j++) values.push(argv[j]);

    infn= fn + ".ini";
    outfn= fn + ".tmp";
    
    ifstream inp(infn);
    if(!inp){
        cerr << "Can't open " << infn << " for Input" << endl;
        exit(1);
    }

    ofstream outp(outfn);
    
    if(!outp){
        cerr << "Can't open " << outfn << " for Output" << endl;
        exit(1);
    }

    int insec= 0;

    SPString w, l, i, v;
    SPStringList d, vs;
    char op;
    char itemop;
    if(item[0] == '-' || item[0] == '+'){ // add or remove an item
	    itemop= item[0];
		item= item.substr(1); // remove the first character
	}else itemop= '=';

    Regexp secre("^" + sec + "$", Regexp::nocase);
    Regexp itemre((itemop == '+' ? "^;" : "^") + item + "$", Regexp::nocase);

    if(itemop != '='){ // comment or uncomment an item
        Regexp valuere("^" + values[0] + "$", Regexp::nocase);
// cout << "add or remove" << item << "=" << values[0] << endl;
        while(inp >> w){ // find the section
            if(w.m("^\\[(.+)\\]", d)) insec= d[1].m(secre); // see if in section or not

            if(insec && w.m("^(.+)\\s*=\\s*(.*)\\s*$", d)){ // if we are in the section
                i= d[1]; v= d[2];
              	if(i.m(itemre) && v.m(valuere)){
               	    if(itemop == '+') outp << w.substr(1) << endl; // remove comment
               	    else outp << ";" << w << endl; // prepend comment
                    break;
               	}
            }
           	outp << w << endl; 
        }

        while(inp >> w) // dump the rest out to file
            outp << w << endl;
 
    }else{              // change the value in an item
        while(inp >> w){ // find the section
    // cout << w << endl;

            if(w.m("^\\[(.+)\\]", d)) insec= d[1].m(secre); // see if in section or not

            l= w; // default
            // l.chop();

            if((insec != 0) && w.m("^(.+)[\\s]*=(.*)$", d)){ // if we are in the section
                i= d[1]; v= d[2];
    // cout << "item= " << i << ", value= " << v << endl;
            	if(i.m(itemre)){   // if we match the item
            	    vs= v.split(" ");
            	    SPString value;
        	        for(int j=0;j<values.scalar();j++){ // for each value in the command list
                        value= values[j];
                		if(value[0] == '-' || value[0] == '+' || value[0] == '='){ // we have an insertion or append op
    		                op= value[0];
    		                value= value.substr(1); // remove the first character
    		            }else op= 0;
		            
                		if(value == "nothing"){ // empty
    		                l= ""; break;
    		            }else if(op == '+'){	// append
        	                vs= append(value, vs);
    		                l= vs.join(" ");
    		            }else if(op == '-'){	// remove
    		                vs= remove(value, vs);
    		                l= vs.join(" ");
    		            }else{ /* if(op == '=') */			        // replace
    		                l= value; break;
    		            }
    	            }

                    l= i + "=" + l;
//     cout << "Old: " << w << endl;
//     cout << "New: " << l << endl;
                }
           }			
           outp <<  l << endl;
        }
    }

    inp.close();
    if(outp.fail()){
        cerr << "Something bad happened to the output file" << endl;
        perror(outfn); exit(1);
    }
    outp.close();

    SPString fnbak;
    fnbak= fn + ".bak";
    unlink(fnbak);
    if(rename(infn, fnbak)){
        SPString errmsg; errmsg= "rename failed for " + infn + " to " + fnbak;
        perror(errmsg); exit(1);
    }
    if(rename(outfn, infn)){
        SPString errmsg; errmsg= "rename failed for " + outfn + " to " + infn;
        perror(errmsg); exit(1);
    }
}

#ifdef __GNUC__
template ostream& operator<<(ostream &, SPList<int> const &);
template ostream& operator<<(ostream &, SPList<SPString> const &);

template class SPList<int>;
template class SPList<SPString>;
template class SPList<Range>;
template class SPListBase<int>;
template class SPListBase<SPString>;
template class SPListBase<Range>;
template class SubList<int>;
template class SubList<SPString>;
template class SubList<Range>;

template class SPListIter<SPString>;

#endif

