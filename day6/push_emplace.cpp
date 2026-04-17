#include<bits/stdc++.h>
using namespace std;
class A
{
public:
int x;
A(int a=0):x(a)
{
cout<<"constructor"<<endl;
}
A(A&&)noexcept
{
cout<<"move constructor"<<endl;
}
A(const A& )
{
cout<<"copy constructor"<<endl;
}
};
int main()
{
vector<A>v;
cout<<"1)push_back"<<endl;
v.push_back(A(10));
cout<<"1)emplace"<<endl;
v.emplace_back(A(20));
}
