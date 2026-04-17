#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct car
{
	car* left=nullptr;
	string name;
	string manufacturer;
	double rating;
	car* right=nullptr;
};
car* insert1(car*root,string name,string manf,double rate)
{
	if(root==nullptr)
		return new car{nullptr,name,manf,rate};
	if(rate>root->rating)
		root->right=insert1(root->right,name,manf,rate);
	else if(rate < root->rating)
		root->left=insert1(root->left,name,manf,rate);
	return root;
}
void inorder(car* root)
{
	if(root==nullptr)
		return;
	inorder(root->left); 
	cout<<"car name :"<<root->name<<" manufactured by :"<<root->manufacturer<<" having rating "<<root->rating<<endl;
	inorder(root->right);
}
int main()
{
	car* root=nullptr;
	root=insert1(root,"Benz","Karl Benz",4.5);
	root=insert1(root,"Thar","Mahindra",4);
	root=insert1(root, "Ford","Henry Ford",4.3);
	root=insert1(root,"Toyata", "Toyada",4.2);
	inorder(root);
	return 0;
}

