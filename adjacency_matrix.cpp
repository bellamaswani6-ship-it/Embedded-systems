#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mygraph
{
   int v;
   vector<vector<int>>matrix;
   public:
   mygraph(int x):v(x){
   matrix.resize(v,vector<int>(v,0));
}
   void add(int x,int y)
   {
     matrix[x][y]=1;
     matrix[y][x]=1;
  }
   void print()
  {
    int i,j;
    for(i=0;i<v;i++)
    {
      for(j=0;j<v;j++)
      cout<<matrix[i][j]<<" ";
      cout<<endl;
    }
}
};
int main()
{
mygraph g(4);
g.add(0,2);
g.add(0,3);
g.add(1,2);
g.add(2,3);
g.add(3,1);
g.print();
return 0;
}

