#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class ecu
{
	public:
		int engine_temp[5];
		int size1=5;
		void set()
		{
			static int i=0;
			cout<<"engine temperature is:";
			cin>>engine_temp[i];
			i++;
		}
		void get()
		{
			int i;
			cout<<"engine temperatures are:";
			for(i=0;i<size1;i++)
				cout<<engine_temp[i]<<" ";
			cout<<endl;
		}
		int size()
		{
			return size1;
		}
		int& operator [](int i)
		{
			return engine_temp[i];
		}
		int& at(int i)
		{
			if(i>=size1)
				throw out_of_range("index is out of range");
			else
				return engine_temp[i];
		}
};
int main()
{
	ecu a;
	int i;
	for(i=0;i<a.size();i++)
	{
		a.set();
		sleep(10);
	}
	cout<<"engine temp after 20 seconds is:"<<a[2]<<endl;
        cout<<"engine temp after 10 seconds is:"<<a.at(1)<<endl;
	try
	{
		int r=a.at(6);
		cout<<"engine temp after 50 seconds is:"<<r<<endl;
	}
	catch(exception& e)
	{ 
		cout<<e.what()<<endl;
	}
	a.get();
}
