#include<bits/stdc++.h>
using namespace std;
class A{
	public:
		int *a;
		int v;
		A(int *p,int n)
	{
               a=p;
              v=n;
	}
		void average ()
		{
			float result=0;
                        int i;
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
	int *p=new int[5],i;
	for( i=0;i<5;i++){
		cin>>p[i];
	}
	shared_ptr<A>o(new A(p,5),deleter{});
	o->average();
}

