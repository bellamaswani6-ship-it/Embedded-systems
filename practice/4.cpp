#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={23,34,56,76,12,90,6,44,33,22};
auto result=v|views::filter([](int& x){ return x%2==0;})|views::transform([](int &x){return x*x;});
for(auto it:result)
cout<<it<<" "<<endl;
for(auto it2:v)
cout<<it2<<" ";
}
