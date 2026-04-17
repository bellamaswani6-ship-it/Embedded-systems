#include<iostream>
#include<bits/stdc++.h>
using namespace std;
string s[]={"traffic_control","power_grid","water_supply","hospital_network","police_control","data_center"};
struct info
{
	int u,v,w;
};

         struct comparator
{
	  bool operator ()(const info &a,const info &b)
	{
		return a.w<b.w;
	}
};
class network
{
	int v;
	vector<info>edge_list;
	vector<int>parent;
	vector<int>rank;
	public:
	network(int x):v(x)
	{
		edge_list.resize(v);
		rank.resize(x,0);
		parent.resize(x);
		int i;
		for(i=0;i<x;i++)
			parent[i]=i;
	}
	void add(int u,int v,int w)
	{
		edge_list.push_back({u,v,w});
	}
	int find_edge(int node)
	{
		if(parent[node]==node)
			return node;
		return parent[node]=find_edge(parent[node]);
	}
	void union_set(int u,int v)
	{
		u=find_edge(u);
		v=find_edge(v);
		if(u==v)
		{
			cout<<"nodes "<<u<<" and "<<v<<" are already visited"<<endl;
			return;
		}
		if(rank[u]>rank[v])
			parent[v]=u;
		else if(rank[u]<rank[v])
			parent[u]=v;
		else
		{
			parent[u]=v;
			rank[u]++;
		}
	}
	int minimum()
	{
		sort(edge_list.begin(),edge_list.end(),comparator{});
		int min_wt=0;
		int edge_cnt=0;
		for(auto& info:edge_list)
		{
			int u=info.u;
			int v=info.v;
			int w=info.w;
			if(find_edge(u)!=find_edge(v))
			{
				union_set(u,v); 
		cout<<s[u]<<"-> "<<s[v]<<" of  cost: "<<w<<endl;
				min_wt+=w;
				edge_cnt++;  
                                if(edge_cnt==edge_list.size()-1)
                                break;
			}
		}
		return min_wt;
	}
	void print()
	{
		cout<<"parent :";
		for(auto it1:parent)
			cout<<s[it1]<<" ";
		cout<<endl;
		cout<<"rank   :";
		for(auto it2:rank)
			cout<<it2<<" ";
		cout<<endl;
		cout<<"_____________________________"<<endl;
	}
};
int main()
{
	network n(6);
	n.add(0,1,4);
	n.add(0,2,4);
	n.add(1,2,2);
	n.add(2,3,3);
	n.add(2,5,2);
	n.add(2,4,4);
	n.add(3,4,3);
	n.add(5,4,3);
	int c=n.minimum();
	cout<<"minimum cost is:"<<c<<endl;
	return 0;
}

