#include<bits/stdc++.h>
using namespace std;
class car
{
	public:
		int fuel;
		int* vnum;
		car(int f=0,int v=0):fuel(f),vnum(new int(v))
	{
		cout<<"constructor"<<endl;
	}
	//	car(const car&) = delete;
	//	car& operator=(const car&) = delete;
		~car()
		{
			delete vnum;
			cout<<"destructor"<<endl;
		}
		void transfer(car&& o)
		{
			fuel=o.fuel;
			vnum=o.vnum;
			o.fuel=0;
			o. vnum=nullptr;
		}

};
void passbyvalue(car o)
{
	cout<<"fuel is:"<<o.fuel<<endl;
	cout<<"vehicle number:"<<(*o.vnum)<<endl;
}
void passbyreference (car& o)
{
	o.fuel=27;
	*(o.vnum)=1234;
}
void constref(const car &o)
{
cout<<"fuel is:"<<o.fuel<<endl;
cout<<"vehicle number:"<<*(o.vnum)<<endl;
}
int main()
{
car c1(24,5678);
car c2;
passbyvalue(c1);
passbyreference(c2);
constref(c2);
car c3;
c3.transfer(move(c2));
}

