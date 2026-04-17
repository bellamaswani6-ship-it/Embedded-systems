#include<bits/stdc++.h>
using namespace std;
class vec
{
int *p,size,capacity;
public:
vec():p(nullptr),size(0),capacity(0){}
~vec()
{
delete []p;
}
int size1()
{
return size;
}
int capacity1()
{
return capacity;
}
int& operator [](int i)
{
return p[i];
}
void push1(int d)
{
if(size==capacity)
grow();
p[size++]=d;
}

int* begin()
{
return p;
}
int* end()
{
return p+size;
void grow()
{
(capacity!=0)?(capacity=capacity*2):(capacity=1);
int *d;
d=new int [capacity];
int i;
for(i=0;i<size1();i++)
d[i]=p[i];
delete []p;
p=d;
}
void pop1()
{
 p[size-1]=0;
size--;
}
void shrink()
{
 int *a=new int [size];
int i;
for(i=0;i<size;i++)
a[i]=p[i];
capacity=size;
delete[]p;
p=a;
}
int front()
{
 return p[0];
}
int back()
{
return p[size-1];
}
/*void fill(int x)
{
  int*p;
   for(p=this->begin();p!=this->end();p++)
    *p=x;
}*/
};
int main()
{
vec v;
v.push1(10);
cout<<v.size1()<<endl;
cout<<v.capacity1()<<endl;
v.push1(34);
v.push1(23);
v.push1(2343);
v.push1(342);
//v.pop1();
cout<<v.size1()<<endl;
cout<<v.capacity1()<<endl;
v.shrink();
cout<<v.capacity1()<<endl;
cout<<v.front()<<endl;
cout<<v.back()<<endl;
//v.fill(19);
for(auto it:v)
cout<<it<<endl;
}
