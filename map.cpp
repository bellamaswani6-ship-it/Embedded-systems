#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
map<string,int>m;
m["aswani"]=100;
m["manisha"]=87;
m["jyoti"]=67;
m.insert({"chaitu",56});
m.insert(make_pair("pooja",88));
m.emplace("harika",65);
cout<<"aswani's score:"<<m["aswani"]<<endl;
for(const auto &[name,marks]:m)
cout<<name<<" "<<marks<<endl;
if(m.find("manisha")!=m.end())
cout<<"model akka is found"<<endl;
else
cout<<"i don't know who is she"<<endl;
//m.insert("manisha",90);
for(const auto &[name,marks]:m)
cout<<name<<" "<<marks<<endl;
cout<<"jyoti's score:"<<m.at("jyoti")<<endl;
}

