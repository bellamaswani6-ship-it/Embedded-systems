#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class my_shared
{
int* data;
int* count;
public:
my_shared(int x):data(new int(x))
{
cout<<"constructor "<<endl;
count=new int (1);
cout<<"value is "<<*data<<" and it's reference count "<<*count<<endl;
}
my_shared(const my_shared& other)
{
  cout<<"copy constructor "<<endl;
  data=other.data;
  count=(other.count);
++ (*count);
cout<<"value is "<<*data<<" and it's reference count "<<*count<<endl;
}
my_shared& operator =(const my_shared& other)
{
cout<<" copy assignment operator "<<endl;
relese();
data=other.data;
count=other.count;
++(*count);
cout<<"value is "<<*data<<" and it's reference count "<<*count<<endl;
return *this;
}
~my_shared()
{
cout<<"destructor "<<endl;
relese();
}
void relese()
{
   if(*count)
   {
   --(*count);
   cout << "relese count "<<*count<<endl;
    }
if(*count==0)
{
cout<<" resources are relesed "<<endl;
delete data;
delete count;
}  
}
int my_count()
{
return *count;
}
};
int main()
{
my_shared p1(10);
cout<<"refernce_count "<<p1.my_count()<<endl;
{
my_shared p2=p1;
cout<<"refernce_count "<<p1.my_count()<<endl;
my_shared p3(p1);
cout<<"refernce_count "<<p1.my_count()<<endl;
}
cout<<"refernce_count "<<p1.my_count()<<endl;
return 0;
}

