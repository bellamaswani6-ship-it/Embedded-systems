#include<bits/stdc++.h>
using namespace std;
void fun(int&n)
{
    n=n*6;
}
int& fun2(int &n)
{
    n=n*10;
    static int l=2;
    int &r=l;
    return r;
}
void display(const int &a,const double &d)
{
    cout<<a<<endl;
    cout<<d<<endl;
}
int add(int a,int b)
{
    return a+b;
}
int main()
{
    int a=10;
    int &rf=a;
    double d=12.54;   //indirectly reference is constant pointer,go for constant
    cout<<&a<<endl;
    cout<<&rf<<endl;
    cout<<&d<<endl;
    int &rv=rf;
    cout<<&rv<<endl;
    const int &c=a;
    cout<<&c<<endl;
    const int *p;
    p=&c;
    cout<<p<<endl;
    //int &r=c;
    //cout<<&r<<endl;
    fun(a);
    cout<<a<<" "<<rf<<" "<<endl;
    int &l_ref=fun2(a);
    cout<<&l_ref<<endl;
    cout<<a<<" "<<l_ref<<endl;
    display(a,d);
    int sum=add(a,l_ref);
    cout<<"sum is:"<<sum<<endl;
    vector<string>v={"ASD","345","sdsdg","6987"}; //for each loop
    for(auto &it:v)
    cout<<it<<endl;
}
