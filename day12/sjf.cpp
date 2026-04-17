#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class process
{
public:
int pid;
string name;
int burst_time;
friend ostream& operator <<(ostream& COUT,process& p);
};
ostream& operator <<(ostream& COUT,process &p)
{
COUT<<"process name is: "<<p.name<<" having burst_time :"<<p.burst_time<<" and it's process id "<<p.pid<<endl;
}
struct comparator
{
bool operator () (const process &p1,const process &p2)const
{
 if(p1.burst_time!=p2.burst_time)
 return p1.burst_time<p2.burst_time;
 return p1.pid<p2.pid;
}
};
int main()
{
set<process,comparator>s;
s.insert({1,"Task1",4});
s.insert({2,"Task2",6});
s.insert({3,"Task3",7});
s.insert({4,"Task4",8});
s.insert({5,"Task5",5});
int i;
for(auto it:s)
{
cout<<it<<" ";
s.erase(it);
}
cout<<endl;
return 0;
}

