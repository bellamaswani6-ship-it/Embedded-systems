#include<iostream>
#include<bits/stdc++.h>
using namespace std;
constexpr int square(int x)
{
return x*x;
}
int main()
{
 constexpr int a=square(5);
 cout<<"a="<<a<<endl;
constexpr int b=10;
int c=square(b);
cout<<"c="<<c<<endl;
return 0;
}

