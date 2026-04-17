#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct mydata
{
int u,v,wt;
};
class mygraph
{
int v;
vector<mydata>adj;
vector<int>rank;
vector<int>parent;
public:
mygraph(int x):v(x)
{
adj.resize(v);
rank.resize(x,0);
parent.resize(v);
int i;
for(i=0;i<v;i++)
parent[i]=i;
}
void add(int u,int v,int w)
{
 adj.push_back({u,v,w});
}
int find_parent(int node)
{
if(parent[node]==node)
return node;
return parent[node]=find_parent(parent[node]);
}
void union_set(int u,int v)
{
u=find_parent(u);
v=find_parent(v);
if(u==v)
{
cout<<u<<" "<<v<<" alreay visted";
return;
}
if(rank[v]<rank[u])
{
parent[v]=u;
}
else if(rank[v]>rank[u])
{
parent[u]=v;
}
else
{
parent[v]=u;
rank[u]++;
}
cout<<"union between node "<<u<<" "<<v<<endl;
print();
}
void print()
{
cout<<"parent :";
for(auto it:parent)
cout<<it<<" ";
cout<<endl;
cout<<"rank   :";
for(auto it2:rank)
cout<<it2<<" ";
cout<<endl;
cout<<"----------------------------------------------";
cout<<endl;
}
static bool comparator (const mydata& a,const mydata& b)
{
  return a.wt<b.wt;
}
int minimum()
{
int i,min_wt=0,edge_count=0;
sort(adj.begin(),adj.end(),comparator);
for(auto edges:adj)
{
int u=edges.u;
int v=edges.v;
int wt=edges.wt;
if(find_parent(u)!=find_parent(v))
{
union_set(u,v);
min_wt+=wt;
edge_count++;
}
}
return min_wt;
}
};
int main()
{
mygraph m(6);
m.add(0,1,4);
m.add(0,2,4);
m.add(1,2,2);
m.add(2,3,3);
m.add(2,5,2);
m.add(2,4,4);
m.add(3,4,3);
m.add(5,4,3);
int c=m.minimum();
cout<<"minimum weight is:"<<c<<endl;
return 0;
}

