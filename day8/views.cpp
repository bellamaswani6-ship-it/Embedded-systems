#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={32,41,67,89,345,665,22,1,99,1,34,54,6745,889,34};
auto even=v|views::filter([](int &x)
{
return x%2==0;
});
for(auto& it:even)
cout<<it<<" ";
cout<<endl;
auto square=v|views::transform([](int& x)
{
return x*x;
});
for(auto it:square)//generally it is saying that it is a range based for loop where i dont know how many elemnts are there
cout<<it<<" ";
cout<<endl;
cout<<"after:"<<endl;//"|" it is pipe symbol which says o/p of one procexx lead to i/p of another processes
for(auto it:v) //if we observe we are using vector data but not modifiyng that is we are viewing into that and creating our own
cout<<it<<" ";
cout<<"first 5"<<endl;
auto first=v|views::take(5);//it take first 5 elements
for(auto& it:first)
cout<<it<<" ";
cout<<endl<<"last 5"<<endl;
auto skip =v|views::drop(5);//it skips first 5 elements and remaining are included
for(auto& it:skip)
cout<<it<<" ";
cout<<"reverse:"<<endl;
auto r=v|views::reverse;//it reverse the vector but not original one
for(auto& it:r)
cout<<it<<" ";
cout<<endl;
cout<<"after:"<<endl;
for(auto& it:v)
cout<<it<<" ";
cout<<endl;
map<string,int>m={{"SD",45},{"sads",656},{"sdsf",89}};
cout<<"keys:"<<endl;
for(auto it:m|views::keys)
cout<<it<<endl;
cout<<"values:"<<endl;
for(auto it1:m|views::values)
cout<<it1<<endl;
}

