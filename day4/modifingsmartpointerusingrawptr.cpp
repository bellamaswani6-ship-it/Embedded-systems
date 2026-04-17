#include<bits/stdc++.h>
using namespace std;
void modify(int* p)
{
*p=134;
cout<<"in resource function:"<<*p<<endl;
cout<<"address in function:"<<p<<endl;
}
int main()
{
unique_ptr<int>o=make_unique<int>(20);
cout<<"before value:"<<*o<<endl;
cout<<"address in main:"<<&o<<endl;
modify(o.get());
cout<<"after value:"<<*o<<endl;
cout<<"address in main:"<<&o<<endl;
}
