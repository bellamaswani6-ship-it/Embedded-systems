#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct process
{
int pid,burst_time,remaining_time;
};
int main()
{
int i;
queue<process>q;
q.push({1,4,4});
q.push({2,7,7});
q.push({3,8,8});
q.push({4,9,9});
queue<int>q1;
for(i=0;i<q.size();i++)
q1.push(i);
int current_time=0;
int time_slice=2;
for(i=0;i<q.size();i++)
{
  process p=q.front();
   q.pop();
  cout<<"executing p "<<p.pid<<" from "<<current_time<<" to ";
   if(p.remaining_time > current_time)
     {
       p.remaining_time-=current_time;
       current_time+=time_slice;
       cout<<current_time<<endl;
    q.push(p);
     }
     else
     {
         current_time+=p.remaining_time;
         cout<<" to "<<p.remaining_time<<"finished"<<endl;
         p.remaining_time=0;
     }
}
}
