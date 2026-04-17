#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void _set(int*p,int size)
{
int i;
cout<<"enter the data:";
for(i=0;i<size;i++)
cin>>p[i];
}
int main()
{
int **p,n,m,i,j;
vector<int>v;
cout<<"enter how many sensors:";
cin>>n;
p=new int* [n];
for(i=0;i<n;i++)
{
cout<<"enter how many entries:";
cin>>m;
p[i]=new int[m];
v.push_back(m);
_set(p[i],m);
}
for(i=0;i<n;i++)
{
   for(j=0;j<v[i];j++)
    cout<<p[i][j]<<" ";
   cout<<endl;
}
for(i=0;i<n;i++)
delete [] p[i];
delete p;
}
