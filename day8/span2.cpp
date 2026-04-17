#include<bits/stdc++.h>
using namespace std;
void print(span<int>s)
{
for(auto it:s)
cout<<it<<" ";
cout<<endl;
}
int main()
{
vector<int>v={5,10,15,20,25,30,35,40};
span<int>s(v);
auto first=s.first(4);
cout<<"from first:"<<endl;
print(first);
auto last=s.last(3);
cout<<"from last:"<<endl;
print(last);
auto middle=s.subspan(2,6);
cout<<"from middle:"<<endl;
print(middle);
//cout<<s.at(4)<<endl;//it is giving error
cout<<v.at(4)<<endl;//it is not  giving error
cout<<s[4]<<endl;
}
