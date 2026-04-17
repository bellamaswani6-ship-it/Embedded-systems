#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct logger
{
int sensor_id;
double temperature;
unique_ptr<logger>left;
unique_ptr<logger>right;
logger(int id,double t):sensor_id(id),temperature(t){}
};
class bst
{
unique_ptr<logger>root;
public:
void insert1(int id,double temp)
{
    insert_imp(root,id,temp);
}
bool search1(int id)
{
return search_imp(root.get(),id);
}
void inorder()
{
  inorder_imp(root.get());
}
optional<double>min_temp()
{
return find_min(root.get());
}
optional<double>max_temp()
{
return find_max(root.get());
}
private:
void insert_imp(unique_ptr<logger>&root,int id,double temp)
{
if(!root)
{
root= make_unique<logger>(id,temp);
 return;
}
if(temp> root->temperature)
insert_imp(root->right,id,temp);
else if(temp< root->temperature)
insert_imp(root->left,id,temp);
}
bool search_imp(logger* root,int id)
{
  if(!root)
   return false;
  if(id==root->sensor_id)
  return true;
  return(search_imp(root->left.get(),id)||search_imp(root->right.get(),id));
}
void inorder_imp(logger* root)
{
  if(!root)
  return;
 inorder_imp(root->left.get());
 cout<<root->sensor_id<<" "<<root->temperature<<endl;
 inorder_imp(root->right.get());
}
optional<double> find_max(logger* root)
{
   if(!root)
   return nullopt;
   while(root->right)
   root=root->right.get();
   return root->temperature;
}
optional<double> find_min(logger* root)
{
  if(!root)
  return nullopt;
  while(root->left)
 root=root->left.get();
 return root->temperature;
}
};
int main()
{
bst root;
root.insert1(10,23.5);
 root.insert1(5,33.7);
 root.insert1(20,29.3);
 root.insert1(15,37.8);
 root. insert1(30,45.2);
 root. inorder();
 if(root.search1(20))
 cout<<"found"<<endl;
 else
cout<<"not found"<<endl;
auto x=root.min_temp();
cout<<"minimum temperature is:"<<*x<<endl;
auto y=root.max_temp();
cout<<"maximum temperature is:"<<*y<<endl;
return 0;
}

