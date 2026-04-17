#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class myqueue
{
	public:
		list<int>l;
		void push(int x)
		{
			l.push_back(x);
		}
		void pop()
		{
			l.pop_front();
		}
		void front()
		{
			cout<<l.front()<<endl;
		}
		void back()
		{
			cout<<l.back()<<endl;
		}
		bool empty()
		{
			if(l.empty())
				return true;
			else
				return false;
		}
		int size()
		{
			return l.size();
		}
};
int main()
{
	myqueue s;
	s.push(80);
	s.push(100);
	s.front();
	s.back();
	cout<<"size:"<<s.size()<<endl;
	s.pop();
	s.pop();
	if(s.empty())
		cout<<"queue is empty"<<endl;
	else
		cout<<"queue is not empty"<<endl;
}

