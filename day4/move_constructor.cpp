#include<bits/stdc++.h>
using namespace std;
class led
{
public:
int pin;
 led()
{
cout<<"default constructor"<<endl;
}
led(int x)
{
pin=x;
cout<<"parametrized"<<endl;
}
led(const led &o)
{
cout<<"copy constructor"<<endl;
pin=o.pin;
}
led(led&& o) //noexcept is mandatory for move constructor
{
cout<<"move constructor"<<endl;
}
~led()
{
cout<<"destructor"<<endl;
}
};
led create()
{
  led l;
cout<<"object created indirectly"<<endl;
return l;
}
int main()
{
vector<led>v;
v.push_back(led(1));//here internally it will move and parametrized constructor
v.push_back(led(2));
led l1=create();
}
