#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class B;
class A
{
public:
shared_ptr<B>aptr;
A()
{
cout<<"A's constructor "<<endl;
}
~A()
{
cout<<"A's destructor "<<endl;
}
};
class B
{
public:
weak_ptr<A>bptr;
B()
{
cout<<"B 's constructor "<<endl;
}
~B()
{
cout<<"B 's destructor "<<endl;
}
};
int main()
{
shared_ptr<A>a=make_shared<A>();
shared_ptr<B>b=make_shared<B>();
a->aptr=b;
b->bptr=a;
return 0;
}

