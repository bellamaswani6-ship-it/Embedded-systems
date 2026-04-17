#include<bits/stdc++.h>
using namespace std;
class gpio
{
public:
int pin;
gpio(int x=2):pin(x)
{
cout<<"constructor"<<endl;
}
~gpio()
{
cout<<"destructor"<<endl;
}
void modulea(shared_ptr<gpio>g)//if here we use new/make_shared it is like creating new memory but is pointing to same memory
{
cout<<"pin is using by module A"<<endl;
cout<<"no.of owners is:"<<g.use_count()<<endl;
}
void moduleb(shared_ptr<gpio>g)
{
cout<<"pin is using by module B"<<endl;
cout<<"no.of owners is:"<<g.use_count()<<endl;
}
};
class deleter
{
public:
void operator()(gpio*p)
{
  cout<<p->pin<<"pin is relised"<<endl;
}
};
int main()
{
deleter d;
shared_ptr<gpio,deleter>o(new gpio(13),d);
modulea(o);
{
moduleb(o);
}
cout<<"in main refrence count:"<<o.use_count()<<endl;
}
