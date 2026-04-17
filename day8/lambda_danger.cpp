#include<bits/stdc++.h>
using namespace std;
int main()
{
function<int()>f;
{
int x=10;
f=[&x]()
{
return x;
};
cout<<f()<<endl;//actually it is error becoz it's scope is ended but it doesnt show in this terminal
}
}
