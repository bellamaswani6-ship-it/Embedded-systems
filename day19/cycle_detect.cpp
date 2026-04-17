#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class cycle
{
	int v;
	vector<vector<int>>adj;
	vector<bool>vis;
	public:
	cycle(int x):v(x)
	{
		adj.resize(v);
		vis.resize(v,false);
	}
	void add(int u,int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bool dfs(int node,int parent)
	{
		vis[node]=true;
		for(auto neigh:adj[node])
		{
			if(!vis[neigh])
			{
				if(dfs(neigh,node))
					return true;
			}
			else if(neigh!=parent)
				return true;
		}
		return false;
	}
	void detect()
	{
		int i;
		bool is_cycle=false;
		for(i=0;i<v;i++)
		{
			if(dfs(i,-1)&& (!vis[i]))
			{
				is_cycle=true;
				break;
			}   
		}
		if(is_cycle)
			cout<<"cycle found"<<endl;
		else
			cout<<"not a cycle"<<endl;
	}
};
int main()
{
	cycle c(5);
	c.add(0,1);
	c.add(1,2);
	//c.add(2,1);
	c.add(3,4);
	//c.add(4,3);
	c.detect();
	return 0;
}

