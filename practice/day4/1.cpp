#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class A
{
int* data;
public:
A(int n=0):data(new int(n))
{
cout<<"constructor "<<endl;
}
A(const A& o)
{
cout<<"copy constructor "<<endl;
data=new int (*(o.data));
}
A& operator = (const A& o)
{
cout<<"copy assignment opertor "<<endl;
delete data;
data=new int(*(o.data));
return *this;
}
/*A (A&& o)noexcept
{
cout<<"move constructor "<<endl;
data=new int(*(o.data));
o.data=nullptr;
}
A& operator = (A&& o)noexcept
{
cout<<" move assignment operator " <<endl;
delete data;
data=new int (*(o.data));
o.data=nullptr;
return *this;
}*/
~A()
{
cout<<" destructor "<<endl;
}
void display()
{
cout<<"data is : "<<*data<<endl;
}
};
int main()
{
A o1(10);
o1.display();
A o2=o1;
o2.display();
A o3;
o3=o2;
o3.display();
A o4=move(o1);
o4.display();
A o5;
o5=move(o2);
o5.display();
return 0;
}

