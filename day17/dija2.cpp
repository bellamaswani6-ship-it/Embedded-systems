#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct location
{
int distance;
string name;
};
class myalg
{
  unordered_map<string,vector<location>>adj;
  unordered_map<string,int>dis;
  public:
  void add(string u,string v,int weight)
  {
     adj[u].push_back(location{weight,v});
     adj[v].push_back(location{weight,u});
  }
  void dijk(string src)
 {
   priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>>pq;
   dis[src]=0;
   pq.push({0,src});
   while(!pq.empty())
  {
       int w=pq.top().first;
       string n=pq.top().second;
       pq.pop();
     // if (w > dis[n]) continue;
        for(auto neigh:adj[n])
           {
             int n_w=neigh.first;
             string n_n=neigh.second;
             if(dis[n_n]>w+n_w)
              {
                dis[n_n]=w+n_w;
                pq.push({dis[n_n],n_n});
              }
            }
  }
   int i;
 cout<<"shortest distance from  "<<src;
  for(i=0;i<adj[src].size();i++)
  cout<<i<<"->"<<dis[i]<<endl;
}
};
int main()
{
myalg g;
g.add("A","C",5);
g.add("A","F",3);
g.add("A","G",4);
g.add("B","C",2);
g.add("B","F",2);
g.add("F","G",1);
g.add("G","E",3);
g.add("E","C",2);
//g.add(5,2,3);
g.dijk(0);
return 0;
}

