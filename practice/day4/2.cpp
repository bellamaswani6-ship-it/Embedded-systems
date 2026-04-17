#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class my_gpio
{
  int pin;
  public:
  bool state;
  my_gpio(int p):pin(p)
  {
   cout<<"constructor "<<endl;
  }
~my_gpio()
{
cout<<"destructor "<<endl;
}
void write()
{
  state=true;
 cout<<"gpio is on "<<endl; 
}
};
class my_deleter
{
public:
 void operator () (my_gpio* g)
 {
  if(g->state ==false)
 cout<<"Already in off state " <<endl;
 else
cout<<" pin is on state but now it is in off state "<<endl;
 }
};
int main()
{
unique_ptr<my_gpio,my_deleter>a(new my_gpio(23),my_deleter{});
a->write();
return 0;
}

