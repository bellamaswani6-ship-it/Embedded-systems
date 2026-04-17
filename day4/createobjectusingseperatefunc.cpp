#include<bits/stdc++.h>
using namespace std;
class gpio
{
public:
gpio()
{
cout<<"default constructor"<<endl;
}
gpio(const gpio& o)
{
cout<<"copy constructor"<<endl;
}
gpio(gpio&& o)noexcept
{
cout<<"move constructor"<<endl;
} 
~gpio()
{
cout<<"destructor"<<endl;
}
};
gpio create()        ///creating an object in seperate function
{
gpio c;
cout<<"object indirctly called"<<endl;
return c;
}
int main()
{
//gpio o;
create();
}
