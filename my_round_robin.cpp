#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct process
{
int pid,burst_time,remaining_time;
};
int main()
{
queue<process>v{{1,3,3},{2,6,6},{3,7,7}};
queue<int>q;
int i,time_qauntum=2;
for(int i=0;i<q.size();i++)
q.push(i);
int current_time=0;
while(!q.empty())
{
int index=q.front();
auto& p=process[index];
cout<<"exectung p"<<p.pid<<"from"<<current_time<<" to ";
if(p.remaining_time>time_quantum)
{
 current_time+=time_quantum;
 p.remaining_time-=time_quantum;
cout<< 
return 0;
}

