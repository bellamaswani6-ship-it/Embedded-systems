#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
//template<typename t>
struct freedeleter        //using a functor
{
    void operator () (int *p)const
    {
        free(p);
        cout<<"memory is freed"<<endl;
    }
};
int main()
{
    //unique_ptr<int,freedeleter>p1{(int*)malloc(4)};
   // unique_ptr<int,freedeleter>p1{(int*)malloc(4)};
    unique_ptr<int,void(*)(int*)>p1{(int*)malloc(4),freedeleter};
    *p1=10;
    cout<<*p1<<endl;
}