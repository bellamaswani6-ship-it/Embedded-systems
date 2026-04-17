#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class mylogger
{
unordered_map<string,vector<string>>adj;
unordered_map<string,bool>vis;
public:
void add(string s,string r)
{
 adj[s].push_back(r);
}
void dfs()
{
    stack<string>st;
    st.push(adj[0]->first);
     while(!st.empty())
     {
       string r=st.top();
       st.pop();
       if(!vis[r])
       { 
          vis[r]=true;
           cout<<"activating is "<<r<<endl;
            int i;
            for(i=adj[r].size()-1;i>=0;i--)
              {    
                if(!vis[adj[r][i]])
                {
                    st.push(adj[r][i]);
                }
                 }
        }
     
}
}
};   
int main()
{
mylogger g;
g.add("engine_contol","fuel_systems");
g.add("engine_control","ignition");
g.add("fuel_system","sensor_module");
g.add("ignition","sensor_module");
g.add("sensor_module","logging_system");
g.dfs();
return 0;
}

