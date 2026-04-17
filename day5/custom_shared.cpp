#include<bits/stdc++.h>
using namespace std;
class shared
{
	int* data;
	int*ref_count;
	public:
	explicit shared(int v=0)
	{
		cout<<"constructor"<<endl;
		data=new int(23);
		ref_count=new int(1);
	}
	shared(const shared& o)
	{
		cout<<"copy constructor"<<endl;
		data=o.data;
		ref_count=o.ref_count;
		++(*ref_count);
	}
	shared& operator = (const shared& o)
	{
		cout<<"copy assignment operator"<<endl;
		relese();
		data=o.data;
		ref_count=o.ref_count;
		++(*ref_count);
		return *this;
	}
	void relese()
	{
		if(ref_count)
		{
			--(*ref_count);
                         cout<<"count is:"<<*ref_count<<endl;
			if(*ref_count==0)
			{
				cout<<"all owners are relesed"<<endl;
				delete data;
				delete ref_count;
			}
		}
	}
	~shared()
	{
                   relese();
                  cout<<"destructor"<<endl;
	}
	shared(shared&& o) noexcept
	{
		cout<<"move constructor"<<endl;
		data=o.data;
		ref_count=o.ref_count;
		o.data=nullptr;
		o.ref_count=nullptr;
	}
	shared& operator =(shared&& o)noexcept
	{
		cout<<"move assignment operator"<<endl;
		relese();
		data=o.data;
		ref_count=o.ref_count;
		o.data=nullptr;
		o.ref_count=nullptr;
		return *this;
	}
	void get()
	{
		cout<< *ref_count<<endl;
	}
};
int main()
{
	shared s1(12);
	s1.get();
	shared s2=s1;
	s2.get();
	shared s3=s1;
	s3.get();
	s3=s1;
	s3.get();
	shared s4=move(s1);
	s4.get();
	s2=move(s3);
	s2.get();
	//s2.relese();
}
