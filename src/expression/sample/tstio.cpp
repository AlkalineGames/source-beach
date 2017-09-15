#include	<fstream.h>
#include	<strstream.h>
#include	<stdlib.h>
#include	"expression.h"
#include	"assoc.h"

ostream& operator<<(ostream &, SPList<int> const &);
istream& operator>>(istream&, SPList<int>&);

void main()
{
ifstream fin("t.txt");
ofstream fout("t2.txt");

SPString s;
SPStringList l;

    while(fin >> s){
	cout << "read in string: " << s << endl;
	fout << s << endl;
    }
    
    fin.close();
    fout.close();
    
    fin.open("t.txt");
    
    fin >> l;
    
    cout << "List =" << endl << l << endl;

#if 1
    strstream ss, iss;
    ss << "one\n" << "two\nthree\nfour\n";
    ss >> l;
    cout << l << endl;
    SPList<int> il;
    iss << 1 << " " << 2 << " " << 3 << " " << 4 << endl;
    iss << "5 6 7 8 9" << endl;
    iss >> il;
    cout << il << endl;
#endif


    cout << "Start Typing:" << endl;
    while(cin >> s){
	cout << "read in string: " << s << endl;
    }

}

#ifdef __GNUC__
template ostream& operator<<(ostream &, SPList<int> const &);
template ostream& operator<<(ostream &, SPList<SPString> const &);
template istream& operator>>(istream&, SPList<int>&);

template class SPList<int>;
template class SPList<SPString>;
template class SPList<Range>;
template class SPListBase<int>;
template class SPListBase<SPString>;
template class SPListBase<Range>;
template class SubList<int>;
template class SubList<SPString>;
template class SubList<Range>;

#endif
