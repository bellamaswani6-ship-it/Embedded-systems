#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct node
{
unique_ptr<node>left=nullptr;
int data;
unique_ptr<node>right=nullptr;
node(int x):data(x){}
};
void inorder(node* root)
{
if(!root)
return;
inorder(root->left.get());
cout<<root->data<<" ";
inorder(root->right.get());
}
int main()
{
auto root=make_unique<node>(10);
root->left=make_unique<node>(5);
root->right=make_unique<node>(20);
root->left->left=make_unique<node>(2);
root->left->right=make_unique<node>(7);
root->right->left=make_unique<node>(15);
root->right->right=make_unique<node>(30);
inorder(root.get());
return 0;
}

