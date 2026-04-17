#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct data1
{
	string name;
	bool status;
         int v;
	data1(string s,bool x,int y):name(s),status(x),v(y){}
};
struct node
{
	data1 d;
	unique_ptr<node>left;
	unique_ptr<node>right;
	node(string s,bool x,int v):d(s,x,v){}
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
void insert1(unique_ptr<node>&root,string s,bool x,int v)
{
   if(!root)
   {
     root=make_unique<node>(s,x,v);
     return;
   }
   if(v >root->d.v)
  insert1(root->right,s,x,v);
 else if(v < root->d.v)
 insert1(root->left,s,x,v);
}
int main()
{
	unique_ptr<node>root;
        insert1(root,"ecu",true,20); 
        insert1(root,"safety",true,10);
        insert1(root,"dash board",false,30);
        insert1(root,"Air bags",true,5);
        insert1(root,"ABS",true,15);
        insert1(root,"speed",false,25);
        insert1(root,"fuel",false,50);
	bfs(root.get());
	return 0;
}

