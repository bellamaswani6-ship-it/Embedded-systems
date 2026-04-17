#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct _module
{
	string dropping;
	int cost;
};
class maps
{
	_module mod;
	string s;
	unordered_map<string,vector<_module>>adj;
	unordered_map<string,int>dis;
	public:
	void add(string u,string v,int d)
	{
		adj[u].push_back(_module{v,d});
	}
        struct comparator
       {
            bool operator()(pair<string,int>&a,pair<string,int>&b)
            {
             if(a.second<b.second)
              return true;
              return false;
            }
     };
	void dijkstra(string src)
	{
		priority_queue<pair<string,int>,vector<pair<string,int>>,comparator>pq;
			dis[src]=0;
		pq.push({src,0});
		while(!pq.empty())
		{
			string s=pq.top().first;
			int price=pq.top().second;
			pq.pop();
			for(auto neigh:adj[s])
			{ 
				string n_s=neigh.dropping;
				int n_price=neigh.cost;
				if(!dis.count(n_s)) dis[n_s]=INT_MAX;
				if(dis[n_s]>price+n_price)
				{
					dis[n_s]=price+n_price;
					pq.push({n_s,dis[n_s]});
				}
			} 
		}
		cout<<"from  "<<src<<" neighbour airports are "<<endl;
		for(auto p:dis)
			cout<<p.first<<"->"<<p.second<<endl;
	}
};
int main()
{
maps m;
m.add("HYD","BNG",6000);
m.add("HYD","KDP",3500);
m.add("KDP","BNG",2000);
m.add("BNG","DELHI",4000);
m.add("KDP","DELHI",10000);
m.dijkstra("HYD");
	return 0;
}

