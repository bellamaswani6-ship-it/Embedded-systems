#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class _list
{
	  struct node
             {
                node* prev=nullptr;
		int x;
		node* next=nullptr;
             };
		node* head=nullptr;
public:
		void push_front(int x)
		{
			if(head==nullptr)
			{
				node* t=new node{nullptr,x,nullptr};
				head=t;
			}
			else
			{
				node* f=new node{nullptr,x,head};
                                 head->prev=f;
				head=f;
			}
		}
		void insert(node* f,int value)
		{ 
			node* t=head;
			while(t!=f)
			t=t->next;
			node* p=new node{t,value,t->next};  
                          if(t->next)
                          {
                         t->next->prev=p;    
                          }
			t->next=p;

		}
		void print_all()
		{
			node* t=head;
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
			node* t=head;
			head=head->next;
                         head->prev=nullptr;
			delete t;
		}

		void front()
		{
			node* t=head;
			cout<<t->x<<endl;
		}
		 /*void erase(node*f)
		{ 
			node* p=head;
			while(p!=f)
                        p=p->next;  
                        if(p==head)
                          {
                          head=p->next;
                              if(head)
                              head->prev=nullptr;
                           }
                         if(p->prev)
                         p->prev->next=p->next;
                          if(p->next)
                          p->next->prev=p->prev;
			delete p;
		}*/
		node* begin()
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
                void  resize (int  x,int v=0)
                {  
                       int c=0;
                         c=this->size();
                          cout<<"size is:"<<c<<endl;
                          if(c<x)
                          {
                             int l=x-c;
                             node* t=head;
                             while(t->next)
                              t=t->next;
                              while(l)
                             {
                                node *p=new node{t->next,v,nullptr};
                                t->next=p;
                                t=p; 
                                l--;
                             }
                          }
                          else if(c>x)
                         {
                             int c1=1;
                             node* t=head;
                             while(c1!=x)
                             {
                                t=t->next;
                                 c1++;
                             }
                             node* f=t->next;
                               t->next=nullptr;
                               delete []f;
                         }
                    }
                   void push_back(int x)
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
                  void pop_back()
                   { 
                         
                          if(head->next==nullptr)
                          {
                                delete head;
                                   head=nullptr;
                              return;
                            }
                        node* t=head;
                           while(t->next)
                              t=t->next;
                               t->prev->next=nullptr;       
                                  delete t;
                    }
};
int main()
{
	_list f;
	f.push_front(23);
	f.push_front(43);
         f.push_back(88);
         f.print_all();
         f.pop_back();
        f.print_all();
        f.pop_front();
        f.print_all();
        f.front();
        auto it=f.begin();
          f.insert(it,729);
          f.print_all();
          f.push_front(21);
          f.push_back(999);
          f.push_back(2112);
          /*auto it1=f.begin();
           it1++;
          f.erase(it1);*/
          f.print_all();
          if(f.empty())
             cout<<"list is empty"<<endl;
           else
            cout<<"list is not empty"<<endl;
            f.resize(20,707);
             f.print_all();    
             f.resize(5);
             f.print_all();
}

