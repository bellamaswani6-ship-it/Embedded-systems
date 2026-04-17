#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mystack
{
public:
   int pid;
   string process_name;
    bool status;
void finish()
{
cout<<"process ended"<<endl;
}
friend ostream& operator <<(ostream&,mystack&);
};
ostream& operator << (ostream&COUT,mystack& s)
{
COUT<<s.pid<<" "<<s.process_name<<" "<<s.status<<endl;
return COUT;
}
int main()
{
stack<mystack>s;
s.push({324,"hello",false});
s.push({879,"c++",true});
s.push({671,"DS",true});
stack<mystack>p(s);
cout<<"size is:"<<s.size()<<endl;
while(!p.empty())
{ 
cout<<p.top();
p.top().finish(); //remeber p.finish() is not all possible always go with p.top().finish() to call member function
p.pop();
}
return 0;
}

