template<class T>
class SPListIter
{
private:
    int i;
    const T *p;
    const SPList<T>& r;
public:
    SPListIter(const SPList<T>& x) : r(x){ i= 0; reset(); }
    void reset(void){ i= 0; p= (i < r.count()) ? &r[0] : 0;};
   
    const T* operator()(void) const{ return p; }
    const T* operator++() { p= (++i < r.count()) ? &r[i] : 0; return p; } // prefix
    const T* operator++(int)  {const T *o= p; p= (++i < r.count()) ? &r[i] : 0; return o; } //postfix
    operator const void* () const { return p; }
};

#define FOREACH(type, var, list) {SPListIter<type> iter(list); while(iter){type var= *iter++;
#define ENDFOREACH }}


