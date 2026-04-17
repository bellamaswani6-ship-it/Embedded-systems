#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={54,76,2,7,89,325,7889,1938};
ranges::sort(v);
for(auto it:v)
cout<<it<<" ";
cout<<endl;
auto it1=ranges::find(v,325);
if(it1!=v.end())
//cout<<"element is found at:"<<distance(v.begin(),it1)<<endl;
cout<<"element is found at:"<<it1-v.begin()<<endl;
else
cout<<"element is not found"<<endl;
vector<int>v1(v.size());
ranges::copy(v,v1.begin());
for(auto it2:v1)
cout<<it2<<" ";
cout<<endl;
ranges::for_each((v),[](auto& it2)
{
it2=it2*10;
});
for(auto& it2:v)
cout<<it2<<" ";
cout<<endl;
}
