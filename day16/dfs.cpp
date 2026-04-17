#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class dfs
{
  int v;
 vector<vector<int>>adj;
 vector<bool>vis;
public:
 dfs(int x):v(x){
  adj.resize(v);
  vis.resize(v,"false");
}
 void add(int u,int v)
{
  adj[u].push_back(v);
  adj[v].push_back(u);
}
void dfs1(int node)
{
   vis[node]=true;
   cout<<node<<" ";
   for(auto it:adj[node])
   {
     if(!vis[it])
     dfs1(node);
   }
}
};
int main()
{
dfs g(5);
g.add(0,1);
g.add(0,2);
	g.add(1,2);
        g.add(2,4);
        g.add(1,3);
	g.add(3,4);
g.dfs1(0);
return 0;
}

