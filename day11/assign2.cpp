#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class myqueue
{
	struct node
	{
		node* prev=nullptr;
		int x;
		node* next=nullptr;
	};
	public:
	node* head=nullptr;
	void push(int x)
	{ 
		if(head!=nullptr)
		{
			node* t=head;
			while(t->next)
				t=t->next;
			node* newnode=new node{t,x,nullptr}; 
			t->next=newnode;
		}
		else
		{
			node* t=new node{nullptr,x,nullptr};
			head=t;
		}
	}
	void pop()
	{
		if(!head) 
			return;
		node* t=head;
		head=head->next;
		if(head)
			head->prev=nullptr;
		delete t;
	}
	int front()
	{  
		if(head)
			return (head->x);
		else
		{
			cout<<"queue is empty"<<endl;
			return 0;  
		}
	}
	int back()
	{
		if(head)
		{
			node* t=head;
			while(t->next)
				t=t->next;
			return(t->x);
		}
		else
		{
			cout<<"queue is empty"<<endl;
			return 0; 
		}
	}
	bool empty()
	{
		if(head==nullptr)
			return true;
		else
			return false;
	}
	int size()
	{
		node *t=head;
		int c=0;
		while(t)
		{ 
			c++;
			t=t->next; 
		}
		return c;
	}
};
int main()
{
	myqueue s;
	s.push(80);
	s.push(435);
	s.push(245);
	s.push(1);
	s.push(100);
	s.push(729);
	cout<<"front element:"<< s.front()<<endl;
	cout<<"back element:"<<s.back()<<endl;
	cout<<"size:"<<s.size()<<endl;
	s.pop();
	s.pop();
	if(s.empty())
		cout<<"queue is empty"<<endl;
	else
		cout<<"queue is not empty"<<endl;
	cout<<"elements are:"<<endl;
	while(!s.empty())
	{
		cout<<s.front()<<" ";
		s.pop();
	}    
	if(s.empty())
		cout<<"queue is empty"<<endl;
	else
		cout<<"queue is not empty"<<endl;
}

