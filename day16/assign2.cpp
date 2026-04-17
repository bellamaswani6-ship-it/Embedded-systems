#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class logger
{
	unordered_map<string,vector<string>>adj;
	unordered_map<string,bool>vis;
	public:
	void add(string src,string des)
	{
		adj[src].push_back(des);
	}
	void dfs(string s)
	{
		vis[s]=true;
		cout<<"Activated "<<s<<endl;
		for(auto it:adj[s])
		{
			if(!vis[it])
				dfs(it);
		}
	}
};
int main()
{
	logger g;
	g.add("engine_contol","fuel_systems");
	g.add("engine_control","ignition");
	g.add("fuel_system","sensor_module");
	g.add("ignition","sensor_module");
	g.add("sensor_module","logging_system");
	g.dfs("engine_control");
	return 0;
}

