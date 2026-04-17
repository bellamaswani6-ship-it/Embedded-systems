#include<bits/stdc++.h>
using namespace std;
void led(int pin)
{
cout<<"led is on"<<endl;
}
void motoron(int pin)
{
cout<<"motor is on"<<endl;
}
void (*fp)(int x);
int main()
{
int temp;
cout<<"enter temperature:"<<endl;
cin>>temp;
if(temp<20)
{
fp=led;
fp(13);
}
else
{
fp=motoron;
fp(13);
}
}
