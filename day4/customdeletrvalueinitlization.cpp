#include<bits/stdc++.h>
using namespace std;
class gpio
{
public:
bool* state;
gpio()
{
state=new bool(true);
//state=true;
cout<<"gpio pin is on"<<endl;
}
};
class custom
{
public:
void operator ()(gpio *p)
{
*(p->state)=false;
cout<<"gpio pin is release"<<endl;
delete p;//it is a raw pointer i should deallocate to avoid memory leak
}
};
int main()
{
custom c{};
unique_ptr<gpio,custom>o(new gpio(),c);
}
