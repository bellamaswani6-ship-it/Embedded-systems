#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a=10,b=200;         //dangling reference also possible
    const int *p=a; 
    //*p=20;
   const int c=300;
  // p=&c;
   int * const q=b;
   cout<<*q<<endl;
    cout<<*p<<" "<<a<<endl;
}