#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mystack 
{
	int a[5],index=-1;
    int  ele=sizeof(a)/sizeof(a[0]);
	public:
	void push(int x)
	{
		if(index+1 >=ele)
		{
			cout<<"overflow"<<endl;
		}
		else
		{
			a[++index]=x;
		}
	}
	void pop()
	{
		if(index<0)
		{
			cout<<"underflow"<<endl;
		}
		else
		{
			index--;
		}
	}
	int size()
	{
		return index+1;
	}
	int top()
	{
              if(index<0)
               { 
               cout<<"underflow"<<endl;
                 return 0;
               } 
              else
		return a[index];
	}
	bool empty()
	{
		if(index==-1)
               	return true;
		else
			return false;
	}
};
int main()
{
	mystack s;
	s.push(21);
	s.push(90);
        s.push(23);
        s.push(546);
       s.push(5864);
       s.push(12);
	cout<<"size is:"<<s.size()<<endl;
//	s.pop();
	while(!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}
	if(s.empty())
		cout<<"stack is empty"<<endl;
	else
		cout<<"stack is not empty"<<endl;
}

