#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class A
{
int x;
mutable int y;
public:
A(int u,int v):x(u),y(v)
{
cout<<"constructor executed "<<endl;
}
~A()
{
cout<<"destructor "<<endl;
}
void add( )const
{
y=x+y;
}
void sub()const
{
y=y-x;
}
void display()const
{
cout<<"x is "<<x<<"y is "<<y<<endl;
}
};
int main()
{
const A o(2,5);
o.display();
o.add();
o.display();
o.sub();
o.display();
return 0;
}

