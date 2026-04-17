#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class prims
{
	int v;
	vector<vector<pair<int,int>>>adj;
	vector<int>key;
	vector<int>parent;
	vector<bool>vis;
	public:
	prims(int x):v(x)
	{
		adj.resize(v);
		key.resize(v,INT_MAX);
		parent.resize(v,-1);
		vis.resize(v,false);
	}
	void add(int u,int w,int v)
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
			int node=pq.top().second;
			int wt=pq.top().first;
			pq.pop();
			if(vis[node])
				continue;
			vis[node]=true;
			for(auto neigh:adj[node])
			{
				int n_node=neigh.second;
				int n_wt=neigh.first;
				if(!vis[n_node] && key[n_node] > n_wt)
				{
					key[n_node]=n_wt;
					parent[n_node]=node;
					pq.push({key[n_node],n_node});
				}
			}
		}
		vector<pair<int,pair<int,int>>>result;
		int i;
		for(i=1;i<v;i++)
			result.push_back({parent[i],{i,key[i]}});
		return result;
	}
};
int main()
{
         int c=0;
	prims p(6);
	p.add(0,12,1);
	p.add(0,8,2);
	p.add(1,9,2);
	p.add(1,22,3);
	p.add(2,14,5);
	p.add(2,16,3);
	p.add(3,18,5);
	p.add(4,3,5);
        p.add(4,15,3);
	auto it=p.algorithm(0);
	cout<<"edges are:"<<endl;
	for(auto edge:it)
          {
		cout<<edge.first<<" - "<<edge.second.first<<" weight: "<<edge.second.second<<endl;
               c+=edge.second.second;
          }
         cout<<"minimum cost is: "<<c<<endl;
	return 0;
}

