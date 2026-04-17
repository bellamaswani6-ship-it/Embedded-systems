#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct process
{
  int id;
  int burst_time;
};
int main()
{
 queue<process>q;
q.push({1,3});
q.push({2,7});
q.push({3,9});
q.push({4,5}); 
int current_time=0;
while(!q.empty())
{
process p=q.front();
cout<<"executing p"<<p.id<<" from "<<current_time;
current_time+=p.burst_time;
cout<<" to "<<current_time<<endl;
q.pop();
}
return 0;
}

