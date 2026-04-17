#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={34,1,3,576,3,45,90,22,45,77};
ranges::sort(v);
for(auto it:v)
cout<<it<<" ";
auto it=ranges::find(v,45);
if(it!=v.end())
cout<<"found"<<distance(v.begin(),it)<<endl;
else
cout<<"not found"<<endl;
vector<int>v2(v.size());
ranges::copy(v,v2.begin());
ranges::for_each(v2,[](int& x)
{
cout<<x<<" ";
});
int c=ranges::count(v,3);
cout<<"count is:"<<c<<endl;
bool x=ranges::all_of(v,[](int x)
{
return x>0;
});
cout<<(boolalpha)<<x<<endl;
}
