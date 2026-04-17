#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class family
{
public:
string name;
int age;
};
struct comparator
{
bool operator()(const family&a,const family &b)const
{
if(a.name!=b.name)
return a.age<b.age;
}
};
int main()
{
set<family,comparator>s;
s.insert({"ABC",23});
s.insert({"DEF",21});
s.insert({"GHI",12});
s.insert({"JKL",67});
s.insert({"ABC",34});
for(auto it:s)
cout<<it.name<<" "<<it.age<<endl;
return 0;
}

