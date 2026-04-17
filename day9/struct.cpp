#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct st
{
mutable int x:4;
voltaile double y;
};
st f()
{
return st(2,3.14);
}
int main()
{
const auto[x,y]=f();
x=90;//no error because of mutable
//y=4.56;  error because we mentioned it is const
cout<<"x value :"<<x<<"y value"<<y<<endl;
auto[x1,y1]=f();
x1=43;
y1=2.445;
cout<<"x1 value :"<<x1<<"y1 value"<<y1<<endl;
return 0;
}

