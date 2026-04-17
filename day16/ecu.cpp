#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct data1
{
	string name;
	bool status;
	data1(string s,bool x):name(s),status(x){}
};
struct node
{
	data1 d;
	unique_ptr<node>left;
	unique_ptr<node>right;
	node(string s,bool x):d(s,x){}
};
void bfs(node* root)
{
	if(!root)
		return;
	queue<node*>q;
	q.push(root);
	while(!q.empty())
	{
		node* current=q.front();
		q.pop();
		cout<<current->d.name<<" ";
		if(current->d.status)
			cout<<"on"<<endl;
		else
			cout<<"off"<<endl;
		if(current->left)
			q.push(current->left.get());
		if(current ->right)
			q.push(current->right.get());
	}
}
int main()
{
	unique_ptr<node>root;
	root=make_unique<node>("ecu",true);;
	root->left=make_unique<node>("infotaiment",false);
	root->right=make_unique<node>("dash board",true);
	root->left->left=make_unique<node>("media player",false);
	root->left->right=make_unique<node>("camera",false);
	root->right->left=make_unique<node>("speed",true);
	root->right->right=make_unique<node>("fuel",true);
	bfs(root.get());
	return 0;
}

