#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class linked
{
struct node
{
  int data;
  unique_ptr<node>next;
  node(int x):data(x),next(nullptr){}
};
unique_ptr<node>head=nullptr;
public:
void push_front(int x)
{
 auto newnode=make_unique<node>(x);
if(head.get()!=nullptr)
{
 newnode->next=move(head);
 head=move(newnode);
}
else
 head=move(newnode);
}
void print()
{
  node* t=head.get();
 while(t)
{
  cout<<t->data<<" ";
  t=t->next.get();
}
}
void push_back(int x)
{
  auto newnode=make_unique<node>(x);
  node *t=head.get();
if(t==nullptr)
{
head=move(newnode);
return;
}
else
{
  while(t->next)
 t=t->next.get();
t->next=move(newnode);
}
}
void pop_front()
{
 node*t=head.get();
head=move(head->next);
}
};
int main()
{
 linked l1;
l1.push_front(729);
l1.push_back(79);
l1.push_front(100);
l1.push_back(234);
l1.print();
l1.pop_front();
l1.print();
return 0;
}

