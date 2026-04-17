#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class sparse
{
vector<pair<int,int>>v;
public:
void set(int i,int v1)
{
v.push_back({i,v1});
}
void get(int index)
{
for(auto& [i,v1]:v)
{
if(i==index)
{
cout<<"index is:"<<i<<" "<<"value is:"<<v1<<endl;
}
}
}
void print()
{
for(auto& [i,v1]:v)
cout<<"index is:"<<i<<" "<<"value is:"<<v1<<endl;
}
};
int main()
{
sparse s;
s.set(2,6);
s.set(3,9);
s.set(5,8);
s.get(5);
s.print();
return 0;
}

