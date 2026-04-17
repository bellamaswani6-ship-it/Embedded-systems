#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct process
{
int pid;
int burst_time;
};
int main()
{
int current=0;
queue<process>o1;
o1.push({1,3});
o1.push({2,4});
o1.push({3,3});
while(!o1.empty())
{
process p=o1.front();
cout<<"process is:"<<p.pid<<"executing time is"<<current<<" to ";
current=current+p.burst_time;
cout<<current<<endl;
o1.pop();
}
return 0;
}

