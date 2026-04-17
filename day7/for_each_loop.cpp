#include<bits/stdc++.h>
using namespace std;
int main()
{
vector<int>v={54,21,6,8,23};
for_each(v.begin(),v.end(),[](auto val)
{
cout<<val<<" ";
});
}
