#include<bits/stdc++.h>
using namespace std;
class led
{
    int* size;
     string color;
	public:
     led():size(nullptr)
{
	     cout<<"default constructor"<<endl;
}
led(int v,string s)
{
              cout<<"parametrized constructor"<<endl;
              size=new int(v);
               color=s;
}
 led(const led& o)
 {
	 cout<<"copy constructor"<<endl;
	size=new int(*o.size);
       color=o.color;
 }
led& operator =(const led& o) 
{
	cout<<"copy assignment operator"<<endl;
	delete(this->size);
	size=new int(*o.size);
	color=o.color;
         return (*this);
}
led (led&& o)
{
	cout<<"move constructor"<<endl;
	size=new int(*o.size);
         color=o.color;
	 o.color="";
	 o.size=nullptr;
}
led& operator =(led&& o)
{
	cout<<"move assignment operator"<<endl;
	delete(this->size);
	size=new int (*o.size);
        color=o.color;
	o.color="";
        o.size=nullptr;
            return (*this);
}
void display()
{
	cout<<"size of led is:"<<*size<<endl;
	cout<<"colour of led is:"<<color<<endl;
}
~led()
{
delete  size;
}

};
int main()
{
   led l1(23,"red");
   led l2(12,"pink");
   led l3=l1;
   l1.display();
   l2.display();
   l3.display();
   led l4=move(l2);
   led l5,l6;
   l5=l1;
   l6=move(l3);
   l6.display();
   l4.display();
   l5.display();
}
