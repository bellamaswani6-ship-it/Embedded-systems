#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct node
{
	unique_ptr<node>left;
	int data;
	unique_ptr<node>right;
        node(int x):data(x){}
};
void insert1(unique_ptr<node>&root,int x)
{
	if (!root)
        {
            root=make_unique<node>(x);
            return;
        } 
	 if(x>root->data)
	insert1(root->right,x);
	else if(x<root->data)
         insert1(root->left,x);
}
void preorder(node*root)
{
	if(root==nullptr)
		return;
	cout<<root->data<<" ";
	preorder(root->left.get());
	preorder(root->right.get());
}
void postorder(node*root)
{
	if(root==nullptr)
		return;
	postorder(root->left.get());
    
  // cout<<"hello"<<endl;
	postorder(root->right.get());
  
    //  cout<<"hello"<<endl;
	cout<<root->data<<" ";
}
void inorder(node*root)
{
	if(root==nullptr)
		return;
	inorder(root->left.get());
	cout<<root->data<<" ";
	inorder(root->right.get());
}
/*void delete1(node* root)
{
if(root==nullptr)
return;
cout<<"bye"<<endl;
delete1(root->left.get());
cout<<"hai"<<endl;
delete1(root->right.get());
cout<<"hii"<<endl;
delete root;
}*/
void delete1(unique_ptr<node>&root,int x)
{
   if(!root)
   return;
  else if(x >root->data)
  delete1(root->right,x);
  else if(x < root->data)
  delete1(root->left,x);
  else
  {
    if(!root->left && !root->right)
    {
      root.reset();
    }
    else if(!root->left)
  {
   root=move(root->right);
  }
    else if(!root->right)
   {
    root=move(root->left);
   }
  else
  {
    node* min=root->right.get();
    while(min->left)
    min=min->left.get();
    root->data=min->data;
    delete1(root->right,min->data);//here i am passing as root->right not as min node becoz my parameter as unique_ptr so i am going with                                      //root->right
   }
  }
}
optional<int> large(node* root)
{
  if(!root)
  return nullopt;
  while(root->right)
  root=root->right.get();
 return root->data;
}
optional<int>small(node*root)
{
  if(!root)
  return nullopt;
   while(root->left)
  root=root->left.get();
  return root->data;
}
bool search(node*root,int x)
{
  if(!root)
  return false;
  if(root->data==x)
   return true;
  else if(x>root->data)
  return search(root->right.get(),x);
  else
   return search(root->left.get(),x);
}
int main()
{
	unique_ptr<node>root;
        //node* root=nullptr;
	insert1(root,20);
	insert1(root,15);
	insert1(root,30);
	insert1(root,10);
	insert1(root,17);
	insert1(root,25);
	insert1(root,40);         
	insert1(root,35);
	insert1(root,50);
	//insert1(root,30);
        cout<<"Inorder"<<endl;
	inorder(root.get());
	cout<<endl<<"preorder"<<endl;
	preorder(root.get());
	cout<<endl<<"postorder"<<endl;
	postorder(root.get());
        delete1(root,30);
      cout<<endl<<"after deleting 30:"<<endl;
        preorder(root.get());
        bool r= search(root.get(),15);
(r==1)?(cout<<"Found"<<endl):(cout<<"Not found"<<endl);
    optional<int> r1=large(root.get());
       cout<<"largest node is: "<<*r1<<endl;
     optional< int> s=small(root.get());
      cout<<"smallest node is: "<<*s<<endl;
	return 0;
}

