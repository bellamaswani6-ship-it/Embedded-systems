#include<bits/stdc++.h>
using namespace std;
class A{
	public:
		int *a;
		int v;
		A(int n):v(n)
	{
		a=new int [n];
		cout<<"constructor"<<endl;
		int i;
		cout<<"enter elements:";
		for(i=0;i<n;i++)
			cin>>a[i];
	}
		void average ()
		{
			int result=0,i;
			for(i=0;i<v;i++)
				result+=a[i];
			result=result/v;
			cout<<"average temperature:"<<result<<endl;
		}
		~A()
		{
			cout<<"destructor"<<endl;
		}
};
class deleter
{
	public:
		void operator () (A*o)
		{
			delete []o->a;
                        delete o;
		}
};
int main()
{
	shared_ptr<A>o(new A(5),deleter{});
	o->average();
}

