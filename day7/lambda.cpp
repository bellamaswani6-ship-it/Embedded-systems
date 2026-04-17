#include<bits/stdc++.h>
using namespace std;
int main()
{
int size=12;
bool state=true;
string color="yellow";
/*auto it=[&](int temp) // as we are passing by refernce we can change the actual data 
{
if(temp>25)
{
size=5;
state=false;
}
};
cout<<"before:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
it(29);
cout<<"after:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
*/
/*auto it=[=](int temp)//as passing by value if we want to change then it gives error
{
if(temp>25)
{
size=5;
state=false;
}
};
cout<<"before:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
it(29);
it(20);
cout<<"after:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
}*/
/*auto it=[=,&state](int temp) //here if we obderve we taken all differnrtlyi
{
if(temp>25)
{
state=false;
}
};
cout<<"before:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
it(29);
cout<<"after:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
}*/
/*auto it=[=](int temp)mutable noexcept//generally if we capture by value we cannot modify but still if we want go for mutable but it is temporary
{                                  //it is only within lambda function after getting out of these it shows still original previous
if(temp>25)
{
size=5;
state=false;
cout<<"in func:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
}
};
cout<<"before :"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
it(29);
cout<<"after:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
}*/

auto it=[=](int temp)mutable  //generally if we capture by value we cannot modify but still if we want go for mutable but it is temporary
{
if(temp>30)
throw ("greater than 30");//it is only within lambda function after getting out of these it shows still original previous
if(temp>25)
{
size=5;   //if noexcept is written if exception is thrown it cannot caught as mentioned as noexcept written so it is getting aborted
state=false;
cout<<"in func:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
}
};
cout<<"before :"<<endl;
cout<<size<<endl;
cout<<state<<endl;
cout<<color<<endl;
try
{
it(34);
}
catch(const char*s)
{
cout<<s<<endl;
}
cout<<"after:"<<endl;
cout<<size<<endl;
cout<<state<<endl;
}
