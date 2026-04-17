#include<bits/stdc++.h>
using namespace std;
class A{
	vector<int>v;
	public:
	A(int count=0):v(count,0){}
	void set(int n,int n2)
	{
		v[n]=n2;
	}
	void print()const
	{
		int i;
		for(i=0;i<v.size();i++)
			cout<<(i+1)<<" "<<v[i]<<endl;
	}
};
int main()
{
	A o(2);
	o.set(0,2323);
	o.set(1,7772);
	o.print();
}
