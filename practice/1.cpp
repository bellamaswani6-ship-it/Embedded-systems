#include<bits/stdc++.h>
using namespace std;
void print(span<int>s)
{
int i;
for(auto it:s)
cout<<it<<" ";
cout<<endl;
}
int main()
{
int *p,i;
p=new int [10];
cout<<"enter elements:";
for(i=0;i<10;i++)
cin>>p[i];
print(span<int>(p,10));
}
