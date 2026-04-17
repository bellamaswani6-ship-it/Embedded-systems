#include<bits/stdc++.h>
using namespace std;
int main()
{
array<int,10>a;
cout<<"enter elements:";
int i;
for(i=0;i<10;i++)
cin>>a[i];
cout<<a[4]<<endl;
//cout<<a[13]<<endl;//throw exception because .at() has bound checking
//cout<<a[5]<<endl;//it gives error [] doesn't have bound checking
cout<<"size of an array:"<<a.size()<<endl;
sort(a.begin(),a.end());
for(auto it:a)//range based value
cout<<it<<" ";
cout<<endl;
reverse(a.begin(),a.end());
for(auto it:a)
cout<<it<<" ";
cout<<endl;
cout<<a.front()<<endl;///prints a[0] data
cout<<a.back()<<endl;//prints a[4] data
for(auto it=a.begin();it!=a.end();it++)
cout<<*it<<" ";
cout<<endl;
for(auto it=a.rbegin();it!=a.rend();it++)
cout<<*it<<" ";
cout<<endl;
//cout<<a.capacity()<<endl;//no capacity() in array
if(a.empty())
cout<<"array is empty"<<endl;
else
cout<<"array is not empty"<<endl;
cout<<"max size is:"<<a.max_size()<<endl;
cout<<"size is:"<<a.size()<<endl;
array<int,10>b;
fill(b.begin(),b.end(),100);
for(auto it:b)
cout<<it<<" ";
}
