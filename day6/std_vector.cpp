#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={2,5,6,22,90};
cout<<v.at(2)<<endl;
cout<<v[2]<<endl;
cout<<v.front()<<endl;
cout<<v.back()<<endl;
if(v.empty())
cout<<"vector is empty"<<endl;
else
cout<<"vector is not empty"<<endl;
cout<<"size of a vector:"<<v.size()<<endl;
cout<<"max size is:"<<v.max_size()<<endl;
cout<<"capacity is:"<<v.capacity()<<endl;
auto it=v.begin()+2;
v.insert(it,1000);
cout<<"size is:"<<v.size()<<endl;
cout<<"capacity id:"<<v.capacity()<<endl;
v.push_back(290);
v.push_back(1456);
for(auto it:v)
cout<<it<<" ";
cout<<endl;
v.resize(7);
cout<<"size is:"<<v.size()<<endl;
cout<<"capacity id:"<<v.capacity()<<endl;
v.shrink_to_fit();
cout<<"size is:"<<v.size()<<endl;
 cout<<"after capacity id:"<<v.capacity()<<endl;
vector<int>v1;
v1.reserve(5);
cout<<"size is:"<<v1.size()<<endl;
 cout<<"capacity id:"<<v1.capacity()<<endl;
v1.shrink_to_fit();
cout<<"size is:"<<v1.size()<<endl;
 cout<<"after capacity id:"<<v1.capacity()<<endl;
}

