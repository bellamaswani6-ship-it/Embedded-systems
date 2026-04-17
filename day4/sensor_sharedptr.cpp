#include<bits/stdc++.h>
using namespace std;
class sensor
{
int temperature=25;
public:
sensor()
{
cout<<"sensor is activated"<<endl;
}
~sensor()
{
cout<<"sensor is off"<<endl;
}
int read()
{
  return temperature;
}
void logger(shared_ptr<int>s)
{
cout<<"logger temp:"<<s->read()<<endl;
}
void display(shared_ptr<int>s)
{
cout<<"display"<<s->read()<<endl;
}
void control(shared_ptr<int>s)
{
cout<<"control temp:"<<s->read()<<endl;
}
};
int main()
{
shared_ptr<int>s=make_shared <sensor>();
logger(s.get());
display(s.get());
control(s.get());
}
