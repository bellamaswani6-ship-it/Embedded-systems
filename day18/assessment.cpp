#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class router
{
	int v;
	vector<vector<pair<int,int>>>adj;
	vector<int>dis;
	public:
	router(int x):v(x)
	{
		adj.resize(x);
		dis.resize(x,INT_MAX);
	}
	void add(int u,int v,int w)
	{
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	void dijik(int s)
	{
		dis[s]=0;
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
		pq.push({s,0});
		while(!pq.empty())
		{
			int node=pq.top().first;
			int wt=pq.top().second;
			pq.pop();
			for(auto neigh:adj[node])
			{
				int n_node=neigh.first;
				int n_wt=neigh.second;
				if(dis[n_node]>wt+n_wt)
				{
					dis[n_node]=wt+n_wt;
					pq.push({n_node,dis[n_node]});
				}
			}
		}
		cout<<"shortest distance from src router "<<endl;
		for(int i=0;i<dis.size();i++)
			cout<<s<<" -> "<< " to destination router "<<i<<" takes transmission delay of "<<dis[i]<<"ms"<<endl;
	}
};
int main()
{
	router r(6);
	r.add(0,1,4);
	r.add(0,2,2);
	r.add(1,2,1);
	r.add(1,3,5);
	r.add(2,3,8);
	r.add(2,4,10);
	r.add(3,5,6);
	r.add(4,5,2);
	r.dijik(0);
	return 0;
}

