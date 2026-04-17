#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class task
{ 
   public:
  string name;
  int priority,burst_time;
};
/* bool operator<(const task& o)const
 {
    return o.priority<priority;
 }*/
struct deleter
{
 bool operator()(const task& o,const task& o1)const //if we write within class there is this pointer but here out of class so need to take                                                     two operands
  {    cout<<"comparision called"<<endl; 
     if(o.priority==o1.priority)       
     return o.burst_time>o1.burst_time;

     return o.burst_time>o1.burst_time;
 }

/* bool operator()(const task& o,const task& o1)const
 {
    return o.priority>o1.priority;
 }*/
};

int main()
{
 set<task,deleter>s;
s.insert({"task1",1,3});
s.insert({"task2",1,4});
s.insert({"task3",3,9});
s.insert({"task4",4,7});
for(auto p:s)
cout<<p.name<<" "<<p.priority<<" "<<p.burst_time<<endl;
cout<<"delete is calling"<<endl;
s.erase(task({"task2",1,4}));
for(auto p:s)
cout<<p.name<<" "<<p.priority<<" "<<p.burst_time<<endl;
s.insert({"task5",2,88});
for(auto p:s)
cout<<p.name<<" "<<p.priority<<" "<<p.burst_time<<endl;
}


