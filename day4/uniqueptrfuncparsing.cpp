#include<bits/stdc++.h>
using namespace std;
void modify(const unique_ptr<int>*p)
{
**p=100; //*p=make_unique<int<(100) it gives different address but **p gives same memory location
cout<<"after changing: "<<**p<<endl;
cout<<"address is heap: "<<(*p).get()<<endl;
cout<<"address in stack:"<<p<<endl;
}
int main()
{
unique_ptr<int>o1=make_unique<int>(10);
cout<<"before changing:"<<*o1<<endl;
cout<<"address is stack:"<<&o1<<endl;
cout<<"address in heap:"<<o1.get()<<endl;
modify(&o1);
if(!o1)
cout<<"it is empty"<<endl;
}
