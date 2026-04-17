#include<bits/stdc++.h>
using namespace std;
void fun(span<int>s)
{
for(auto& it:s)
{
it=it*2;
cout<<it<<" ";
}
cout<<endl;
}
int main()
{
vector<int>v={1,3,5,7};
fun(v);
int a[]={34,68,31,90,54};//it is available from c++20 so when compiling take seperate
fun(a);
int size=5;
int *p=new int[size]{12,34,65,78,90};
//span<int>s(p,size);//if we dont declare here size it give error as constructor excepting size becoz of some dma
fun(span<int>(p,size));//it is another method but it avoids taking size on anotherside of function
//for(auto it:s)
//cout<<it<<" ";
}
