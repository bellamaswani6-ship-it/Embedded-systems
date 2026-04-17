#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct node
{
	unique_ptr<node> left;
	int data;
	unique_ptr<node>right;
	node(int x):data(x){}
};
void bfs_travaseral(unique_ptr<node>&root)
{
	if(!root)
		return;
	queue<node*>q;
	q.push(root.get());
	while(!q.empty())
	{
		node* current=q.front();
		q.pop();
		cout<<current->data<<" ";
		if(current->left)
			q.push(current->left.get());
		if(current->right)
			q.push(current->right.get());
	}
}
int main()
{
	unique_ptr<node>root;
	root=make_unique<node>(20);
	root->left=make_unique<node>(10);
	root->right=make_unique<node>(30);
	root->left->left=make_unique<node>(5);
	root->left->right=make_unique<node>(15);
	root->right->left=make_unique<node>(25);
	root->right->right=make_unique<node>(50);
	bfs_travaseral(root);
	return 0;
}

