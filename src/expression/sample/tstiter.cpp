#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop

#include "expression.h"
#include "splistit.h"

typedef int INT;

void test(const SPStringList& sl)
{
SPListIter<SPString> n(sl);
   for(n.reset(); n; ++n){
	cout << *n() << endl;
   }
  
}

void main()
{
SPList<INT> l;
SPStringList sl;
    
    for(int i=0;i<10;i++) l.push(i);
    sl.push("one"); sl.push("two");
    
    i= 0;
    for(SPListIter<INT> n(l); n; ++n){
	cout << *n() << " -- " << l[i++] << endl;
    }
  
    const int *ip;
    n.reset();
    while((ip = n++) != NULL){
        cout << *ip << endl;
    }
     
    FOREACH(int, t, l) cout << t << endl;
    ENDFOREACH

    SPString s;
    for(SPListIter<SPString> sn(sl); sn; sn++){
        cout << *sn() << ":" << s << endl;
    }

    test(sl);
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

template class SPListIter<INT>;
template class SPListIter<SPString>;

#endif
