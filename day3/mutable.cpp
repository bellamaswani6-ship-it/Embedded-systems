#include<bits/stdc++.h>  //application of mutable is debugging
using namespace std;
class sensor
{
	int v;
	mutable int c;//as mentioning mutable we can change data members even functio                       n /object is constant mutable is only for data members not for                        local data
	public:
	sensor(int x)
	{
		v=x;
	}
	void read ()const  //as mentioning const we cannot change datamembers unless                                     it is mutable
	{
		c++;
		cout<<"count is:"<<c<<endl;
	}
	void write()
	{
		v=234;
		cout<<"sensor data is:"<<v<<endl;//constant object can call only cons                                   tant functions
	}
};
int main()
{
	 const sensor s(10);
         s.read();
          s.read();
	   sensor s1(120);
	  s1.write();
}	  
