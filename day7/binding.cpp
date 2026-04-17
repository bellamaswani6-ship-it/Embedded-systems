#include<bits/stdc++.h>
using namespace std;
int sum(int x,int y,int z)
{
return (x+y+z);
}
int main()
{
auto boundsum=bind(sum,10,placeholders::_1,placeholders::_2);
cout<<"sum:"<<boundsum(32,45)<<endl;
}

