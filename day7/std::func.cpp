#include<bits/stdc++.h>
using namespace std;

void fun(auto v)
{
cout<<"inside:"<<v<<endl;
}
int main()
{
 function<int(int,int)>f=[](int a,int b)//standard function with lambdas
{
return a+b;
};
cout<<"sum is:"<<f(3,7)<<endl;
function<int(int,int)>f1=[](auto a,auto b)//we cannot use auto for standard function
{
  return (a-b);
};
cout<<"difference is:"<<f1(43.34,12.32)<<endl;
auto f2=[](auto a,auto b)//we can use auto for generic lambda if we observe here nothing in capture block becoz we are extenally passing 
{                             //arguments so no need
return a-b;
};
cout<<"diffe:"<<f2(32.45,6.1)<<endl;
auto f4=[](auto a,auto b)
{
return (a*b);
};
/*void fun(auto v)
{
cout<<"inside:"<<v<<endl;
}*/
fun(f4(2.5,7.5));
fun(f4(2,-6));
fun(f4(4.7,9));
//cout<<"mul is:"<<f4(43,6)<<" "<<(2.5,7.5)<<endl;
}
