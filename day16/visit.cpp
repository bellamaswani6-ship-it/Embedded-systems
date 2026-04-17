#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
	int x;
	unordered_map<int,vector<int>>adj;
	public:
	mygraph(int v):x(v){
	}
	void add(int u,int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void bfs(int start,int target)
	{
		vector<bool>vis(x,false);
                vector<int>parent(x,-1);
                 vis[start]=true;
		queue<int>q;
		q.push(start);
		while(!q.empty())
		{
			int node=q.front();
			q.pop();
			//cout<<node<<" ";
                            if(node==target)
                             break;
			for(int it:adj[node])
			{
				if(!vis[it])
				{
					vis[it]=true;
                                        parent[it]=node;
					q.push(it);
				}
			}
		}
                vector<int>path;
                for(int v=target;v!=-1;v=parent[v])
                { 
                  cout<<endl<<v<<" ";
                  path.push_back(v);
                 }
                  reverse(path.begin(),path.end());
                   cout<<endl<<"shortest route is:"<<endl;
                  for(auto it1:path)
                  cout<<it1<<" "; 
                  cout<<endl;
              cout<<"shortest path :"<<path.size()-1<<endl;
	}
};
int main()
{
	mygraph g(5);
	g.add(0,1);
	g.add(0,2);
	g.add(1,2);
        g.add(2,4);
        g.add(1,3);
	g.add(3,4);
	g.bfs(0,4);
}


