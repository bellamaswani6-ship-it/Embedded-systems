#include<bits/stdc++.h>
using namespace std;
/*struct sparse
{
int index;
int value;
};
int main()
{
/*sparse s[10];
int a[]={1,3,0,0,9,7,0,0,0,0,0,8,34,65,0,0,324},ele,i,c=0;
ele=sizeof(a)/sizeof(a[0]);
for(i=0;i<ele;i++)
{
if(a[i])
{
s[c].index=i;
s[c].data=a[i];
c++;
}
}
for(i=0;i<c;i++)
{
cout<<"index is:"<<s[i].index<<endl;
cout<<"data is:"<<s[i].data<<endl;
}*/
int main()
{
vector<pair<int,int>>v;
v.push_back({1,7});
v.push_back({2,67});
for(const auto& [index,value]:v)
{
cout<<"index is:"<<index<<endl;
cout<<"value is:"<<value<<endl;
}
}
