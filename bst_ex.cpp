#include<iostream>
#include<bits/stdc++.h>
using namespace std;
/*enum error
{
engine_error=100,
fuel_error,
temp_error=50,
infotainment error
};*/
struct node
{
unique_ptr<node>left;
int id;
unique_ptr<node>right;
node (int x):id(x){}
};
void insert1(unique_ptr<node>&root,int id)
{
  if(!root)
   {
    root=make_unique<node>(id);
    return;
    }
   if(id > root->id)
   insert1(root->right,id);
   else if(id <root->id)
   insert1(root->left,id);
}
void error_solved(int v)
{


}
/*
void inorder(node* root)
{
if(!root)
return;
inorder(root->left.get());
cout<<root->id<<" ";
inorder(root->right.get());
}*/
void inorder(node* root)
{
  if(!root)
   return;
  stack<node*>st;
  node* current=root;
  while(current!=nullptr || !st.empty())
  {
       while(current!=nullptr)
      {
           st.push(current);
           current=current->left.get();
      }
     current=st.top();
      st.pop();
   cout<<current->id<<" ";
   current=current->right.get();
  }
}
void delete1(unique_ptr<node>&root,int id)
{
  if(!root)
  return;
  if(id > root->id)
  delete1(root->right,id);
  else if(id < root->id)
 delete1(root->left,id);
else
{
 if(!root->left && !root->right)
  root.reset();
 else if(!root->left)
 root=move(root->right);
 else if(!root->right)
 root=move(root->left);
else
{
    node* min=root->right.get();
    while(min->right)
    min=min->left.get();
    root->id=min->id;
    delete1(root->right,id);
}
}
}
int main()
{
unique_ptr<node>root;
insert1(root,100);
insert1(root,50);
insert1(root,300);
insert1(root,250);
insert1(root,400);
inorder(root.get());
delete1(root,50);
cout<<endl<<"after deleting:"<<endl;
inorder(root.get());
return 0;
}

