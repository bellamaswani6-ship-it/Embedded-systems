#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
set<int>s={32,2,5,8,1,9};
s.insert(43);
s.insert(90);
s.insert(465);
for(auto it:s)
cout<<it<<" ";
cout<<endl;
if(s.find(11)!=s.end())
cout<<"yes 11 is found"<<endl;
else
cout<<"oh! NO 11 is found"<<endl;
s.erase(90);
cout<<"after deleting:"<<endl;
for(auto it1:s)
cout<<it1<<" ";
if(s.contains(32))
cout<<"found"<<endl;
else
cout<<"not found"<<endl;
return 0;
}

