#include<bits/stdc++.h>
using namespace std;
constexpr int fact1(int n)//for faster operation we go for constexpr
{
 int fact=1;
for(int i=1;i<=n;i++)
fact=fact*i;
return fact;
}
int main()
{
//int x;                         ..erro becoz it is at runtime but const is for compiletime
//cout<<"enter number:"<<endl;
//cin>>x;
constexpr int f=fact1(6);
cout<<"factorial is:"<<f<<endl;
}
