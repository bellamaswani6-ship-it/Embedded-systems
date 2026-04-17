#include<bits/stdc++.h>
using namespace std;
class A{
	public:
		unique_ptr<int[]>a;
		int v;
		A(unique_ptr<int[]>p,int n)
		{
			a=move(p);
			v=n;
			int i;
			//  cout<<"enter elements:";
			// for(i=0;i<v;i++)
			// cin>>a[i];
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
int main()
{
	unique_ptr<int[]>p=make_unique<int[]>(5);
	int i;
	cout<<"enter elements:";
	for(i=0;i<5;i++)
		cin>>p[i];
	shared_ptr<A>o(new A(move(p),5));
	o->average();
}

