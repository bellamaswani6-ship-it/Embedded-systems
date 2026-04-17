#include<bits/stdc++.h>
using namespace std;
class car
{
	int fuel;
	int* vehiclenumber;
	public:
	car(int v=0,int x=0):fuel(v),vehiclenumber(new int(x)){
	cout<<"default constructor"<<endl;
	}
	car(const car&o)
	{
		cout<<"copy constructor"<<endl;
		fuel=o.fuel;
		//delete (this->vehiclenumber);
		vehiclenumber=new int(*o.vehiclenumber);
		//vehiclenumber=(o.vehiclenumber);
		//
	}
	car& operator =(const car& o)
	{
		cout<<"copy assignment operator"<<endl;
		fuel=o.fuel;
		delete(this->vehiclenumber);
		vehiclenumber=new int(*o.vehiclenumber);
		return *this;
	}
	car& operator =(const car&& o)
        {
                cout<<"move assignment operator"<<endl;
                fuel=o.fuel;
                delete(this->vehiclenumber);
                vehiclenumber=new int(*o.vehiclenumber);
		o.fuel=0;
		o.vehiclenumber=nullptr;
                return *this;
        }
	car(car&& o)
	{
		cout<<"move constructor"<<endl;
		fuel=o.fuel;
		o.fuel=0;
		vehiclenumber=o.vehiclenumber;
		o.vehiclenumber=nullptr;
	}
	void display()
	{
		cout<<"cars fuel is:"<<fuel<<endl;
		cout<<"and it's vehicle number:"<<*vehiclenumber<<endl;
	}
	~car()
	{
		cout<<"destructor"<<endl;
		delete[]vehiclenumber;
	}
};
int main()
{
	car o1(20,3467);
	car o2=o1;
	car o3(35,7689);
	car o4;
	o4=o3;
	o1.display();
	o2.display();
	o3.display();
	o4.display();
	car o5=move(o1);
          o5.display();
	  o4=move(o2);
	  o4.display();
}
