#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class myalg
{
  int v;
  vector<vector<pair<int,int>>>adj;
  vector<int>dis;
  public:
  myalg(int x):v(x)
  {
     dis.resize(v,INT_MAX);
     adj.resize(v);
  }
  void add(int u,int v,int weight)
  {
     adj[u].push_back({weight,v});
     adj[v].push_back({weight,u});
  }
  void dijk(int src)
 {
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
   dis[src]=0;
   pq.push({0,src});
   while(!pq.empty())
  {
       int w=pq.top().first;
       int n=pq.top().second;
       pq.pop();
      if (w > dis[n]) continue;
        for(auto neigh:adj[n])
           {
             int n_w=neigh.first;
             int n_n=neigh.second;
             if(dis[n_n]>w+n_w)
              {
                dis[n_n]=w+n_w;
                pq.push({dis[n_n],n_n});
              }
            }
  }
   int i;
 cout<<"shortest distance from  "<<src;
  for(i=0;i<v;i++)
  cout<<i<<"->"<<dis[i]<<endl;
}
};
int main()
{
myalg g(6);
g.add(0,1,2);
g.add(0,3,5);
g.add(1,4,6);
g.add(1,3,5);
g.add(3,5,2);
g.add(3,4,6);
g.add(5,4,1);
g.add(4,2,1);
g.add(5,2,3);
g.dijk(0);
return 0;
}

