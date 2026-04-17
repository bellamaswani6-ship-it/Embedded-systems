#include<iostream>
using namespace std;
int c;
int main()
{
    int a;             //remember c++ is for concurrency which is not in c
    static int b=0;
    static int d;
    cout<<"auto:"<<&a<<endl;
    cout<<"static local:"<<&b<<endl;
    cout<<"static global:"<<&c<<endl;
    int *p=new int(10);
    cout<<"heap:"<<p<<endl;
    cout<<"bss:"<<&d<<endl;
}