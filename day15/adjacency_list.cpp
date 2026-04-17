#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mylist
{
 unordered_map<int,list<int>>adj;
  public:
  void add(int u,int v,bool directed=true)
  {
     adj[u].push_back(v);
     if(directed)
     adj[v].push_back(u);
  }
   void print()
   {
     for(auto& x:adj)
     {
       cout<<x.first<<"->";
      for(auto& y:x.second)
      cout<<y<<" ";
      cout<<endl;
      }
}
};
int main()
{
mylist l;
l.add(0,2);
l.add(2,3);
l.add(1,4);
l.print();
return 0;
}

