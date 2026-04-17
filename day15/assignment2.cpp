#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
	unordered_map<int,vector<pair<int,int>>>m;
	public:
	void add(int index,int s,int time,bool directed=false)
	{
		m[index].push_back({s,time});
		if(directed)
			m[s].push_back({index,time});
	}
	void search_min(int index)
	{
		int i,j=0,d=m[index][0].second;
		for(;j<m[index].size();j++)
		{
			if(d>m[index][j].second)
				d=m[index][j].second;
		}
		cout<<"From your place "<<char('A'+index)<<"  for your destination : "<<d<<" minutes"<<endl;   
	}
	void print()
	{
		for(auto& x:m)
		{

			cout<<setw(5)<<char(x.first+'A')<<"->"<<setw(2);
			for(auto& y:x.second)
				cout<<char(y.first+'A')<<setw(5)<<y.second<<"   minutes"<<setw(5);
			cout<<endl;
		}
	}
};
int main()
{
	mygraph g;
	g.add(0,1,20);
	g.add(0,3,50);
	g.add(1,2,90);
	g.add(2,3,15);
	g.add(1,3,25);
	g.print();
	g.search_min(2);
	g.search_min(0);
	g.search_min(1);
	return 0;
}

