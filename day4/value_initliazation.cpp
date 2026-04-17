#include<bits/stdc++.h>
using namespace std;
class A{
int x;
public:
A()
{
cout<<"default constructor"<<endl;
}
A(int v):x(v)
{
cout<<" parametrized constructor"<<endl;
}
~A()
{
cout<<"destructor"<<endl;
}
void display()
{
cout<<"value of x:"<<x<<endl;
}
};
int main()
{
A o1;//default cobstructor while it is calling there is chance of 0 or garbage
o1.display();
A o2{};//default constructor it is initialised to 0 in value initalisation default value is depends on default constructor w
//what user has to initalise it it is not necessary only 0 
o2.display();
A o3(3);//parametrized constructor
o3.display();
}
