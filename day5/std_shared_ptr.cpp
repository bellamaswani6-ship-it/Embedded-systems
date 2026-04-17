#include<bits/stdc++.h>
using namespace std;//genereally in shared pointer only one resource is shared but here only one destructor
class A{
int x;
public:
A(int a=0):x(a)
{
cout<<"constructor"<<endl;
}
~A()
{
cout<<"destructor"<<endl;
}
void display()
{
cout<<"value of x:"<<x<<endl;
}
};
int main()
{
shared_ptr<A>o1=make_shared<A>(10);
cout<<"count is"<<o1.use_count()<<endl;
shared_ptr<A>o2=o1;
cout<<"count is"<<o2.use_count()<<endl;
shared_ptr<A>o3=make_shared<A>();//here another smart pointer is created not sharing previous resource it take new resourec
cout<<"count is:"<<o3.use_count()<<endl;
shared_ptr<A>o4=o3;
cout<<"count is:"<<o4.use_count()<<endl;  
}

