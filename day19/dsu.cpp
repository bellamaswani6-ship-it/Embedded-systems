#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mydsu
{
int v;
vector<int>rank;
vector<int>parent;
public:
mydsu(int x):v(x)
{
rank.resize(v,0);
parent.resize(v);
int i;
for(i=0;i<v;i++)
parent[i]=i;
}
void print()
{
cout<<"parent:"<<" ";
for(auto& it:parent)
cout<<it<<" ";
cout<<endl;
cout<<"rank  :"<<" ";
for(auto& it2:rank)
cout<<it2<<" ";
cout<<endl;
//cout<<"hello"<<endl;
cout<<"___________________________________";
//cout<<"hello"<<endl;
}
int find_parent(int u)
{
 if(parent[u]==u)
 return u;
return parent[u]=find_parent(parent[u]);
}
void unionset(int u,int v)
{
 u=find_parent(u);
 v=find_parent(v);
 if(u==v)
  {
    cout<<"nodes "<<u<<" "<<v<<" are already in same set"<<endl;
    return;
  }
   if(rank[u]>rank[v])
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
  cout<<endl<<"union between "<<u<<" "<<v<<endl;
  print();
}
};
int main()
{
mydsu s(7);
cout<<"before:"<<endl;
s.print();
s.unionset(0,1);
s.unionset(1,2);
s.unionset(3,4);
s.unionset(5,6);
s.unionset(2,6);
s.unionset(0,6);
cout<<endl<<"after:"<<endl;
s.print();
return 0;
}

