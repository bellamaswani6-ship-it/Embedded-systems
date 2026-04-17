#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class task
{
public:
string name;
int priority;
task(string s,int x):name(s),priority(x)
{
}
};
struct comparator
{
bool operator () (const task& o1,const task& o2)const
{
if(o1.priority!=o2.priority)
return o1.priority>o2.priority;
return o1.name>o2.name;
}
};
int main()
{
map<task,string,comparator>m;
m[task("task1",1)]="complete your work";
m[task("task2",3)]="fix bugs";
m[task("task3",2)]="test your code";
m[task("task4",6)]="your work is finished";
for(auto&[it,s]:m)
cout<<it.name<<" "<<it.priority<<" "<<s<<endl;
return 0;
}

