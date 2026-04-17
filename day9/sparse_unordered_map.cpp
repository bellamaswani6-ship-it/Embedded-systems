#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
unordered_map<int,int>m;
m[3]=5;
m[5]=3;
m[2]=65;
m[4]=77;
m[9]=34;
for(auto& [x,y]:m)//we can implement sparse array using vector,map,unorderd_map but unordered_map is very fast
cout<<"x value:"<<x<<" "<<"y value:"<<y<<endl;
cout<<m[3]<<endl;
cout<<m[2]<<endl;
cout<<m[9]<<endl;
return 0;
}

