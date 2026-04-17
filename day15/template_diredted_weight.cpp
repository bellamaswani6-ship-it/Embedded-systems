#include<iostream>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
class mygraph
{
int v;
T inf;
vector<vector<T>>matrix;
public:
mygraph(int x):v(x),inf(numeric_limits<T>::max())
{
matrix.resize(v,vector<T>(v,inf));
}
void add(int i,int j,int wt)
{
 if((i>=0 && i<v)&&(j>=0 && j<v))
  matrix[i][j]=wt;
}
void print()
{
int i,j;
for(auto& row:matrix)
{
for(auto& col:row)
if(col==inf)
cout<<setw(5)<<'~';
else
cout<<setw(5)<<col;
cout<<endl;
}
}
};
int main()
{
mygraph<int>g(4);
g.add(0,1,6);
g.add(1,3,4);
g.add(2,2,1);
g.add(3,0,5);
g.print();
return 0;
}

