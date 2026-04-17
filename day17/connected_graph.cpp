#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
int v;
 vector<vector<int>>adj;
vector<bool>vis;
public:
mygraph(int x):v(x)
{
adj.resize(v,vector<int>(v,0));
vis.resize(v,false);
}
void add(int u,int v)
{
adj[u].push_back(v);
}
int detect()
{
int i,c=0;
for(i=0;i<v;i++)
{
if(!vis[i])
{cout<<"components"<<c+1<<" :";
dfs(i);
cout<<endl;
c++;
}
}
return c;
}
void dfs(int node)
{
vis[node]=true;
cout<<node<<" ";
for(auto it:adj[node])
{
if(!vis[it])
dfs(it);
}
}
};
int main()
{
mygraph g(7);
g.add(0,1);
g.add(1,2);
g.add(2,0);
g.add(3,4);
g.add(4,3);
g.add(5,6);
g.add(6,5);
int c=g.detect();
cout<<"total disconnectes graphs:"<<c<<endl;
return 0;
}

