#include<iostream>
#include<bits/stdc++.h>
using namespace std;
struct deleter
{
void operator ()(int* p)
{
 free(p);
 cout<<"memory is freed "<<endl;
}
};
int main()
{
unique_ptr<int,deleter>p{(int*)malloc(sizeof(int)),deleter{}};
cout<<"memory allocated "<<endl;
*p=34;
cout<<"value is  "<<*p<<endl;
}


