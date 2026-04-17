#include<bits/stdc++.h>
using namespace std;
class car
{
	int fuel;
	int *vnum;
	public:
	car(int v=0,int n=0):fuel(v),vnum(new int(n)){}
	car(const car &o)
	{
		fuel=o.fuel;
		vnum=new int(*o.vnum);
	}
        car& operator =(const car& o)
	{
		fuel=o.fuel;
		delete(this->vnum);
		vnum=new int(*o.vnum);
		return *this;
	}
        car( car&& o)
	{ 
	 fuel=o.fuel;
	 vnum=new int(*o.vnum);
	 o.fuel=0;
	 o.vnum=nullptr;
	}
         car& operator = (car&& o)
	 {
		 fuel=o.fuel;
		 delete(this->vnum);
		 vnum=new int(*o.vnum);
		o.fuel=0;
                o.vnum=nullptr;
	 }
	void display()
	{
		cout<<"fuel is:"<<endl<<"vehicle number:"<<*vnum<<endl;
	}
	~car()
	{
		delete[] vnum;
	}
};
int main()
{
	car o1(21,668);
	car o2(73,234);
	car o3=o1;
	car o4;
	o4=o1;
        o1.display();
	o2.display();
	o3.display();
	o4.display();
	car o5=move(o1);
	o5.display();
}

