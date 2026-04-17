#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct node
{
	node* left=nullptr;
	int data;
	node* right=nullptr;
};
node* insert1(node*root,int x)
{
	if (root == nullptr)
		return new node{nullptr, x, nullptr};
	if(x>root->data)
		root->right=insert1(root->right,x);
	else if(x<root->data)
		root->left=insert1(root->left,x);
	return root;
}
void preorder(node*root)
{
	if(root==nullptr)
		return;
	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);
}
void postorder(node*root)
{
	if(root==nullptr)
		return;
	postorder(root->left);
    
  // cout<<"hello"<<endl;
	postorder(root->right);
  
    //  cout<<"hello"<<endl;
	cout<<root->data<<" ";
}
void inorder(node*root)
{
	if(root==nullptr)
		return;
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}
void delete1(node* root)
{
if(root==nullptr)
return;
cout<<"bye"<<endl;
delete1(root->left);
cout<<"hai"<<endl;
delete1(root->right);
cout<<"hii"<<endl;
delete root;
}
int main()
{
	node* root=nullptr;
	root=insert1(root,10);
	root=insert1(root,5);
	root=insert1(root,35);
	root=insert1(root,15);
	root=insert1(root,15);
	root=insert1(root,20);
	root=insert1(root,81);
	root=insert1(root,100);
        cout<<"Inorder"<<endl;
	inorder(root);
	cout<<endl<<"preorder"<<endl;
	preorder(root);
	cout<<endl<<"postorder"<<endl;
	postorder(root);
        delete1(root);
        inorder(root);
	return 0;
}

