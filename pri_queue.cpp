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
/* bool operator()(const task& o,const task& o1)const //if we write within class there is this pointer but here out of class so need to take                                                     two operands
 {
     return o.burst_time<o1.burst_time;
 }*/

 bool operator()(const task& o,const task& o1)const
 {
    return o.priority>o1.priority;
 }
};

int main()
{
 priority_queue<task,vector<task>,deleter>pq;
pq.push({"task1",1,3});
pq.push({"task2",2,5});
pq.push({"task3",3,9});
pq.push({"task4",4,7});
while(!pq.empty())
{
auto p=pq.top();
cout<<p.name<<" "<<p.priority<<" "<<p.burst_time<<endl;
pq.pop();
}
return 0;
}

