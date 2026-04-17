#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
int v;
 unordered_map<int,vector<int>>adj;
 vector<int>vis;
public:
mygraph(int x):v(x)
{
adj.resize(v);
vis.resize(v,INT_MAX);
}
void add(int u,int v)
{
adj[u].push_back(v);
adj[v].push_back(u);
}
void count_conn()
{
int i,count=0;
for(i=0;i<v;i++)
{
if(!vis[i])
{
cout<<count+1<<endl;
dfs(i);
}
}
}
void dfs(int node)
{
vis[node]=true;
for(auto it:adj[node])
{
 

}
int main()
{


return 0;
}

