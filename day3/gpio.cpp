#include<bits/stdc++.h>
using namespace std;
class gpio
{ 
	public:
	bool pin;
	gpio(bool r)
	{
		r=pin;
		cout<<"pin is on state"<<endl;
	}
	void operator()(bool k)
	{
		pin=k;
		cout<<"release the gpio pin"<<endl;
		
	}
};
int main()
{
	gpio o(true);
	o(false);
}
