#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
	int v;
	unordered_map<int,vector<pair<int,int>>>adj;
	vector<int>dis;
	public:
	mygraph(int x):v(x)
	{
		dis.resize(v,INT_MAX);
	//	adj.size(v);
	}
	void add(int u,int v,int weight)
	{
		adj[u].push_back({weight,v});
		adj[v].push_back({weight,u});
	}
	void dijiks(int src)
	{
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
		pq.push({0,src});
                dis[src]=0;
                while(!pq.empty())
              {
		int wt=pq.top().first;
		int node=pq.top().second;
		pq.pop();
		for(auto neigh:adj[node])
		{
			int n_wt=neigh.first;
			int n_node=neigh.second;
			if(dis[n_node]>wt+n_wt)
			{
				dis[n_node]=wt+n_wt;
				pq.push({dis[n_node],n_node});
			}
		}
               }
		int i;
		for(i=0;i<v;i++)
			cout<<i<<"->"<<dis[i]<<endl;
	}
};
int main()
{
	mygraph g(6);
	g.add(0,1,2);
	g.add(0,3,8);
	g.add(1,3,5);
	g.add(1,4,6);
	g.add(3,4,3);
	g.add(3,5,2);
	g.add(4,5,1);
	g.add(4,2,9);
	g.add(5,2,3);
	g.dijiks(0);
	return 0;
}

