#ifdef	TEST

#include <iostream.h>

#include "splash.h"

typedef int INT;

template <class T>
ostream& operator<<(ostream& os, const SubList<T>& sl)
{
    os << SPList<T>(sl) << endl;
    return os;
}

ostream& operator<<(ostream& os, const SubList<int>& sl);

int main()
{
#if	1
    Slice sl1;

    sl1.add(1); sl1.add(2);
    cout << "1,2 " << sl1 << endl;

    Slice sl2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1);
    cout << "1,2,3,4,5,6,7,8,9,10 " << sl2 << endl;

    sl1.add(5); sl1.add(10);
    cout << "1,2,5,10 " << sl1 << endl;

    Slice sl3(39, 1, 38, 2, 4, 5, 37, 7, 8, 9, 20, 22, -1);
    cout << "39,1,38,2,4,5,37,7,8,9,20,22 " << sl3 << endl;

    SPList<INT> ix1, ix2;
    ix1.push(1); ix1.push(2); ix1.push(3); ix1.push(4);
    ix2.push(22); ix2.push(33);
    cout << "ix1= " << ix1 << endl << "ix2= " << ix2 << endl;

    ix1(1, 2)= ix2;
    
    cout << "ix1(1, 2)= ix2: ix1= " << ix1 << endl;
    
    SPList<INT> tl(ix1(2, 2));
    
    cout << "tl ctor(ix1(2, 2)): tl= " << tl << endl;
    
    SPList<INT> tl2;
    
    tl2.push(0); tl2.push(1); tl2.push(2); tl2.push(3); tl2.push(4);
    cout << "tl2= " << tl2 << endl;
    
    cout << "tl2(2, 3)= " << tl2(2, 3) << endl;
    cout << "tl2(Slice(1, 2, 4, -1))= " << tl2(Slice(1, 2, 4, -1)) << endl;
    
    tl= tl2(Range(2, 4));
    cout << "tl= tl2(Range(2, 4)): tl= " << tl << endl;
    
    tl2(Slice(1, 2, -1))= ix2;
    
    cout << "tl2(Slice(1, 2, -1))= ix2: tl2 = " << tl2 << endl;

    SPList<INT> tl3;
    
    tl3= tl2(1, 4);
    
    cout << "tl3= tl2(1, 4): tl3 = " << tl3 << endl;
    
    tl3.push(tl2(1, 2));
    
    cout << "tl3.push(tl2(1, 2)): tl3= " << tl3 << endl;
    
    cout << "tl3(Slice(4, 1, -1))= " << tl3(Slice(4, 1, -1)) << endl;
    
    cout << "tl3(Slice(2, 1, -1))= " << tl3(Slice(2, 1, -1)) << endl;
#endif
    SPList<int> tl4;
    for(int i=0;i<40;i++) tl4.push(i);

    cout << "tl4(\"1..3,6,10-22,30,31,35,37\") = ";
    cout << tl4("1..3,6,10-22,30,31,35,37") << endl;


    
}

#ifdef __GNUC__
template ostream& operator<<(ostream &, SPList<int> const &);
template ostream& operator<<(ostream &, SubList<int> const &);

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
#endif
