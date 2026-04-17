#include<bits/stdc++.h>
using namespace std;
class sensor
{
	int value;
	mutable int c=0;
	public:
	sensor(int v):value(v){}
	void modify()const
	{
		cout<<"value :"<<value<<endl;
		c++;
	}
	int count1 ()const
	{
		return c;
	}
};
int main()
{
	int c;
	sensor o1(23);
	o1.modify();
	o1.modify();
	c=o1.count1();
	cout<<"count is:"<<c<<endl;
	const sensor o2(43);
	o2.modify();
	//o2.count1();//compile time error because o2 is constant object and tring to access non constant member func
}
