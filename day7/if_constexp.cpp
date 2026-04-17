#include<bits/stdc++.h>
using namespace std;
template<typename T>
void process(T x)
{
if constexpr(sizeof(T)==4)
{
cout<<"it is 32 bit"<<endl;
}
else
{
cout<<"it is not 32 bit"<<endl;
}
}
int main()
{
process(2);
process('A');
process(2.4);
process(4.56f);
process(true);
}
