#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class A
{
	int fuel;
	int* vnum;
	public:
	A(int f=0,int n=0):fuel(f),vnum(new int(n))
	{
		cout<<"constructor "<<endl;
	}
	A(const A& o)
	{
		cout<<"copy constructor "<<endl;
		fuel=o.fuel;
		vnum=new int(*(o.vnum));
	}
	A& operator = (const A& o)
	{
		cout<<"copy assignment operator "<<endl;
		fuel=o.fuel;
		delete vnum;
		vnum=new int (*(o.vnum));
		return *this;
	}
	void display()
	{
		cout<<"fuel is "<<fuel<<" and it's vehicle number is : "<<*vnum<<endl;
	}
	A (A&& o)noexcept
	{
		cout<<" move constructor "<<endl;
		fuel=o.fuel;
		vnum=o.vnum;
		o.fuel=0;
		o.vnum=nullptr;
	}
	A& operator = (A&& o)noexcept
	{
		cout<<"move assignment operator "<<endl;
		fuel=o.fuel;
		delete vnum;
		vnum=o.vnum;
		o.fuel=0;
		o.vnum=nullptr;
		return *this;
	}
	~A()
	{
		if(vnum)
		{
			cout<<"destructor "<<endl;
			delete vnum;
		}
	}
};
int main()
{
	A o1(25,1234);
	o1.display();
	A o2=o1;
	o2.display();
	A o3;
	o3=o1;
	o3.display();
	A o4=move (o1);
	o4.display();
	//o1.display();
	A o5;
	o5=move(o2);
	o5.display();
	return 0;
}

