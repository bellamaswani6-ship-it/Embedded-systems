#include<bits/stdc++.h>
using namespace std;
int add(int a,int b)
{
    return a+b;
}
int main()
{
    int x,y;
    cin>>x>>y;
    int (*fp)(int x,int y);
    fp=add;
    cout<<add(x,y)<<endl;
}