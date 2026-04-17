#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={21,34,56,98,123,5,62};
auto temp=v|views::filter([](int& x)
{
return (x>15 && x<50);
});
for(auto& it:temp)
cout<<it<<" "<<endl;
}
