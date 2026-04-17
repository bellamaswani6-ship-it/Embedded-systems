#include<bits/stdc++.h>
using namespace std;
class A
{
	int n=5;
	int a[5];
	public:
	A()
	{
		int i;
		cout<<"constructor"<<endl;
		cout<<"enter elements:";
		for(i=0;i<n;i++)
			cin>>a[i];
	}
	int size()
	{
		return n;
	}
	int& operator [] (int i)
	{
		return a[i];
	}
	int& at(int i)
	{
		if(i>=n)
			throw out_of_range("a.at");
		else
			return a[i];
	}
	int* begin()
	{
		return a;
	}
	int* end()
	{
		return a+n;
	}
	~A()
	{
		cout<<"destructor"<<endl;
	}
	void display()
	{
		int *it;
		cout<<"elements are:";
		/*for(i=0;i<n;i++)
		  cout<<a[i]<<" ";
		  cout<<endl;*/
		for (it=begin();it!=end();it++)
			cout<<*it<<" ";
		cout<<endl;
		//delete it;
	}
	int front()
	{
		return a[0];
	}
	int back()
	{
		return a[n-1];
	}
	void fil(int x)
	{
		int*p;
		for(p=this->begin();p!=this->end();p++)
			*p=x;
	}
};
int main()
{
	A o;
	cout<< o.size()<<endl;
	cout<< o[2]<<endl;
	cout<< o.at(2)<<endl;
	//cout<<o.at(5)<<endl;
	o.display();
	cout<<o.front()<<endl;
	cout<<o.back()<<endl;
	A o1;
	o1.fil(100);
	o1.display();
}

