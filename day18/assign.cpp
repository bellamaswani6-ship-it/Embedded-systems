#include<iostream>
#include<bits/stdc++.h>
using namespace std;
enum ecu{engine_control=1,battery_management,dash_board,adas_camera,rear_parking_sensor,infotainment};
class myecu
{
int v;
vector<vector<pair<int,int>>>adj;
vector<int>key;
vector<int>parent;
vector<bool>vis;
public:
myecu(int x):v(x)
{
adj.resize(v);
key.resize(v,INT_MAX);
parent.resize(v,-1);
vis.resize(v,false);
}
void add(int u,int v,int w)
{
adj[u].push_back({w,v});
adj[v].push_back({w,u});
}
vector<pair<int,pair<int,int>>> algorithm(int s)
{
key[s]=0;
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
   pq.push({key[s],s});
  while(!pq.empty())
 {
     int wt=pq.top().first;
     int node=pq.top().second;
    pq.pop();
    if(vis[node])
    continue;
    vis[node]=true;
   for(auto neigh:adj[node])
  {
      int n_wt=neigh.first;
       int n_node=neigh.second;
        if(!vis[n_node] && key[n_node]>n_wt)
        {
           key[n_node]=n_wt;
           parent[n_node]=node;
          pq.push({key[n_node],n_node});
        }
     }
}
   vector<pair<int,pair<int,int>>>result;
   int i;
   for(i=1;i<adj.size();i++)
			result.push_back({parent[i],{i,key[i]}});
		return result;
}
};
int main()
{
int c=0;
myecu m(7);
m.add(1,2,3);
m.add(1,3,4);
m.add(2,3,2);
m.add(2,4,6);
m.add(3,4,5);
m.add(3,5,7);
m.add(4,6,4);
m.add(5,6,3);
auto it=m.algorithm(1);
int i=0;
string s[]={" ","engine_control","battery_management","dash_board","adas_camera","rear_parking_sensor","infotainment"};
for(auto edge:it)
{
if(edge.first!=-1)
{
cout<<s[edge.first]<<" -> "<<s[edge.second.first]<<" cost of "<<edge.second.second<<endl;
c+=edge.second.second;
}
}
cout<<"Minimum cost:"<<c<<endl;
return 0;
}

