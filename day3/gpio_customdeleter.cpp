#include<bits/stdc++.h>
using namespace std;
class gpio
{
	public:
	  bool pin;
	  gpio(bool r)
	  {
		  pin=r;
		  cout<<"pin is in on state"<<endl;
	  }
};
class custom
{
	public:
    void operator ()(gpio *p)
    {	    
   p-> pin=false;
    cout<<"release gpio pin"<<endl;
   // delete []p;
    }
};
int main()
{
	//unique_ptr<gpio,custom>o1(new gpio(true));//if we want write customdeletr only in case of new
	unique_ptr<gpio,custom>o1=make_unique<true>;//if make is present no use of custom deleter

 }
