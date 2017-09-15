#ifdef	TESTASSOC

#include <iostream.h>
#include "expression.h"
#include "assoc.h"

ostream& operator<<(ostream& os, Assoc<int>& a);

main()
{
    Assoc<int> a;
    a("one")= 1; a("two")= 2; a("three")= 3;
    cout << a << endl;
    
    cout << "Keys:" << endl << a.keys() << endl;
    cout << "Values:" << endl << a.values() << endl;
    
    cout << "a.isin(\"three\")= " << a.isin("three") << endl;
    cout << "a.isin(\"four\")= " << a.isin("four") << endl;
    
    int t= a.adelete("two");
    cout << "a.adelete(\"two\") returns: " << t << ", a= " << endl << a << endl;

}
#ifdef __GNUC__
template ostream& operator<<(ostream &, SPList<int> const &);
template ostream& operator<<(ostream &, SPList<SPString> const &);
template ostream& operator<<(ostream &, Assoc<int> const &);
template ostream& operator<<(ostream &, Binar<int> const &);

template class SPList<int>;
template class SPList<SPString>;
template class SPList<Range>;
template class SPListBase<int>;
template class SPListBase<SPString>;
template class SPListBase<Range>;
template class SubList<int>;
template class SubList<SPString>;
template class SubList<Range>;

template class SubList<Binar<int> >;
template class Binar<int>;
template class SPList<Binar<int> >;
template class SPListBase<Binar<int> >;
template class Assoc<int>;
#endif

#endif

