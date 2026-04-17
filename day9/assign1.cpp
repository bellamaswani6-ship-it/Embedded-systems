#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class _forward
{
	public:
		int x;
		_forward* next=0;
		_forward* head=0;
		void push_front(int x)
		{
			if(head==nullptr)
			{
				_forward* t=new _forward{x,nullptr};
				head=t;
			}
			else
			{
				_forward* f=new _forward{x,head};
				head=f;
			}
		}
		void insert_after(_forward* f,int value)
		{
			_forward* t=head;
			while(t!=f)
				t=t->next;
			_forward* p=new _forward{value,t->next};
			t->next=p;

		}
		void print_all()
		{
			_forward* t=head;
			cout<<"printing:"<<endl;
			while(t)
			{
				cout<<t->x<<" ";
				t=t->next;
			}
			cout<<endl;
		}
		void pop_front()
		{
			_forward* t=head;
			head=head->next;
			delete t;
		}
		void front()
		{
			_forward* t=head;
			cout<<t->x<<endl;
		}
		void erase_after(_forward*f)
		{ 
			_forward* p=head;
			while(p!=f)
                        p=p->next;
			_forward* t=p->next;
			p->next=p->next->next;
			delete t;
		}
		_forward* begin()
		{ 
			return head;
		} 
                bool empty()
                {
                       if(head==nullptr)
                         return true;
                         else
                          return false;
                }
                void resize (int  x,int v=0)
                {  
                    _forward *t=head;
                       int c=0;
                       while(t->next)
                       { 
                         c++;
                         t=t->next; 
                          
                       }
                        c++;
                         cout<<"no.of elements is:"<<c<<endl;
                          if(c<x)
                          {
                             int l=x-c;
                              while(l)
                             {
                                _forward *p=new _forward{v,nullptr};
                                t->next=p;
                                t=p; 
                                l--;
                             }
                          }
                          else if(c>x)
                         {
                             int c1=1;
                             _forward* t=head;
                             while(c1!=x)
                             {
                                t=t->next;
                                 c1++;
                             }
                             _forward* f=t->next;
                               t->next=nullptr;
                               delete []f;
                         }
                    }
};
int main()
{
	_forward f;
	f.push_front(23);
	f.push_front(43);
       auto it1=f.begin();
	f.insert_after(it1,54);
         it1=it1->next;
	f.insert_after(it1,60);
	f.print_all();
	f.pop_front();
	f.print_all();
	f.front();
	auto it=f.begin();
          it=it->next;
	f.erase_after(it);
	f.print_all();
         if(!f.empty())
          cout<<"forward list is not empty"<<endl;
         else
         cout<<"forward list is empty"<<endl;
      f.resize(10,729);
         f.print_all();
        f.resize(20);
        f.print_all();
      f.resize(2);
        f.print_all();
}

