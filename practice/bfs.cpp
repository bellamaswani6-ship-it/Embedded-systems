#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class my_graph
{
int v;
vector<vector<pair<int,int>>>adj;
vector<bool>vis;
public:
my_graph(int n):v(n)
{
adj.resize(n);
vis.resize(n,false);
}
void add(int u,int v,int w)
{
adj[u].push_back({v,w});
adj[v].push_back({u,w});
}
void bfs(int src)
{
   vis[src]=true;
   queue<int>q;
   q.push(src);
   while(!q.empty())
   {
      int node=q.front();
         q.pop();
        cout<<node<<" ";
        for(auto it :adj[node])
           {
                  if(!vis[it.first])
                    {
                         vis[it.first]=true;
                           q.push(it.first);
                    }
           }
    }
}
};
int main()
{
my_graph g(6);
g.add(0,1,4);
g.add(1,2,6);
g.add(3,2,7);
g.add(4,5,1);
g.add(3,4,2);
g.bfs(0);
return 0;
}

