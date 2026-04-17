#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class cycle
{
	int v;
	unordered_map<int,vector<int>>adj;
	vector<bool>vis;
	vector<bool>restack;
	public:
	cycle(int x):v(x)
	{
		vis.resize(v,false);
		restack.resize(v,false);
	}
	void add(int u,int v)
	{
		adj[u].push_back(v);
                adj[v].push_back(u);
	}
	bool dfs(int n)
	{
		vis[n]=true;
		restack[n]=true;
		for(auto it:adj[n])
		{
			if(!vis[it])
                          {
				if(dfs(it))
                                     return true;
                          }
			else if(restack[it])
				return true;
		}
		restack[n]=false;
		return false;
	}
	bool detect()
	{
		int i;
		for(i=0;i<v;i++)
		{
			if(!vis[i])
			{
				if(dfs(i))
					return true;
			}
		}
		return false;
	}
};
int main()
{
	cycle d(3);
	d.add(0,1);
	d.add(1,2);
	d.add(2,0);
	if(d.detect())
		cout<<"yeah! it is a cycle"<<endl;
	else
		cout<<"oh! no it is not a cycle"<<endl;
	return 0;
}

