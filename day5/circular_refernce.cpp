#include<bits/stdc++.h>
using namespace std;
class car;//it is must before person class if not error (i.e) forward declaration
class person
{
public:
shared_ptr<car>c_m;
static int c;
person()
{
++c;
cout<<"person construcor"<<endl;
}
~person()
{
--c;
cout<<"person destructor"<<endl;
}
};
class car
{
public:
//shared_ptr<person>p_m;  to avoid circular reference take it as weak_ptr
weak_ptr<person>p_m;
static int c1;
car()
{
++c1;
cout<<"car constructor"<<endl;
}
~car()
{
--c1;
cout<<"car destructor"<<endl;
}
};
int person::c=0;
int car::c1=0;
int main()
{
shared_ptr<person>p1=make_shared<person>();
shared_ptr<car>c2=make_shared<car>();
cout<<"before:"<<endl;
cout<<"count is:"<<person::c<<endl;
cout<<"count is:"<<car::c1<<endl;
p1->c_m=c2;
c2->p_m=p1;
cout<<"after:"<<endl;
cout<<"count is:"<<person::c<<endl;
cout<<"count is:"<<car::c1<<endl;
}
