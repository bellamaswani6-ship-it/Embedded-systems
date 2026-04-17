#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool original_state=false;
class my_graph
{
int pin;
public:
my_graph(int p):pin(p)
{
cout<<"gpio pin "<<pin<<" is initialised "<<endl;
}
void status ()
{
original_state=true;
cout<<"gpio pin is on state "<<endl;
}
};
class my_deleter
{
public:
void operator () (my_graph* g)
{
 if(original_state==true)
{
cout<<"upto now gpio pin is on" <<endl;
original_state=false;
cout<<"it is now in off state "<<endl;
}
else
cout<<"pin is already in off state "<<endl;
}
};
int main()
{
unique_ptr<my_graph,my_deleter>p(new my_graph(12));
p->status();
}



