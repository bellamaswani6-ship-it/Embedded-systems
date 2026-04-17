#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
map<string,int>m={{"aswani",100},{"chaitu",98},{"jyoti",87}};
//for(auto it:m)  //old style
//cout<<it.first<<" "<<it.second<<endl;
for(auto& [name,v]:m) //from c++17 it is known as structure binding defined as decomposing unpacking of grouped data
cout<<name<<" "<<v<<endl;
return 0;
}

