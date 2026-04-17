#include<bits/stdc++.h>
using namespace std;
class gpio
{
	bool pin;
	public:
	gpio(bool r)
	{
		pin=r;
	}
class custom
{
	public:
	void operator()(gpio *p)
	{
		if(p->pin==true)
		{
			p->pin=false;
			cout<<"gpio pin is relesed"<<endl;
		}
		else
			cout<<"gpio pin already released"<<endl;
	}
};
};
int main()
{
	unique_ptr<gpio,gpio::custom>o1(new gpio(true));
}
