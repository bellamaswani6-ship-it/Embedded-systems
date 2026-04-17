#include<bits/stdc++.h>
using namespace std;
class car
{
	vector<int>v;
	public:
	car(int count);v(count);
         void set(int n,int vn)
         {
		v[n]=vn;
	 }
        void get()
	{
            int i;
            cout<<"total no.of cars:"<<v.size()<<endl;
             for(i=0;i<v.size();i++)
	     cout<<(i+1)<<" "<<v[i];
	}
};
int main()
{
	car o1(1);
	o1.set(2,677);
	o1.get();
	car o2(5);
	o2.set(1,67);
	o2.set(2,87);
	o2.set(3,45);
	o2.se(4,89);
	o2.set(5,98);
}

