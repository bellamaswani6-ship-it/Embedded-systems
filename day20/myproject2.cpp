#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

struct vehicle_type {
    double a,b,c;
};

struct cable_type {
    int current;
    double resistance;
};

vehicle_type vehicle[4] = {
    {0.3,0.45,0.25},
    {0.35,0.35,0.3},
    {0.3,0.3,0.4},
    {0.45,0.20,0.35}
};

cable_type cabel[3] = {
    {35,50},{40,65},{10,40}
};

class ecu_communication {

    struct communication_link {
        string u, v;
        double delay, cost;
    };

    double a,b,c;
    double total_cost = 0, total_delay = 0;

    vector<communication_link> links;
    vector<communication_link> mst;

    unordered_map<string,string> parent;
    unordered_map<string,int> rankk;
    unordered_set<string> active;

    unordered_map<int,string> ecu = {
        {0,"Engine Control Unit"},
        {1,"Brake Control Unit"},
        {2,"Steering Control Unit"},
        {3,"ADAS Processing Unit"},
        {4,"Battery Management System"},
        {5,"Infotainment Control Unit"}
    };

public:
    ecu_communication() {
        cout<<"Select vehicle type:\n0)Economy 1)Luxury 2)Electric 3)Autonomous\n";
        int i; cin>>i;
        a=vehicle[i].a; b=vehicle[i].b; c=vehicle[i].c;

        for(auto &[i,n]:ecu){
            parent[n]=n;
            rankk[n]=0;
        }
    }

    // ---------- UTIL ----------
    int getIndex(const string &s){
        for(auto &[i,n]:ecu)
            if(n==s) return i;
        return -1;
    }

    // ---------- COST ----------
    pair<double,double> cost_engine(){
        int distance = 1 + rand()%5;
        double delay = distance / 0.2;

        int t;
        cout<<"Select cable (0/1/2): ";
        cin>>t;

        double power_loss = cabel[t].current * cabel[t].current * cabel[t].resistance;
        double cost = a*delay + b*power_loss + c*(distance*20);

        return {cost,delay};
    }

    // ---------- HARDWARE ----------
    void hardware_init(){
        cout<<"\nAvailable ECUs:\n";
        for(auto &[i,n]:ecu) cout<<i<<" : "<<n<<endl;

        while(true){
            int ch;
            cout<<"1)Add link 2)Exit: ";
            cin>>ch;
            if(ch==2) break;

            int i,j;
            cout<<"Enter ECU numbers: ";
            cin>>i>>j;

            auto [cst,dly]=cost_engine();
            links.push_back({ecu[i],ecu[j],dly,cst});
            active.insert(ecu[i]);
            active.insert(ecu[j]);
        }
    }

    // ---------- DSU ----------
    string findp(string x){
        if(parent[x]==x) return x;
        return parent[x]=findp(parent[x]);
    }

    void unite(string a,string b){
        a=findp(a); b=findp(b);
        if(rankk[a]<rankk[b]) parent[a]=b;
        else if(rankk[b]<rankk[a]) parent[b]=a;
        else { parent[b]=a; rankk[a]++; }
    }

    // ---------- KRUSKAL ----------
    void build_mst(){
        sort(links.begin(),links.end(),
             [](auto &x,auto &y){return x.cost<y.cost;});

        for(auto &[i,n]:ecu){
            parent[n]=n; rankk[n]=0;
        }

        for(auto &e:links){
            if(findp(e.u)!=findp(e.v)){
                unite(e.u,e.v);
                mst.push_back(e);
                total_cost+=e.cost;
                total_delay+=e.delay;
            }
        }

        cout<<"\nMST Links:\n";
        for(auto &e:mst)
            cout<<e.u<<" <--> "<<e.v<<" | Cost: "<<e.cost<<" Delay: "<<e.delay<<endl;

        cout<<"\nTotal MST Cost: "<<total_cost;
        cout<<"\nTotal MST Delay: "<<total_delay<<" ns\n";
    }

    // ---------- DIJKSTRA ON MST ----------
    void dijkstra(string src,string des){
        int n = ecu.size();
        vector<vector<pair<int,pair<double,double>>>> adj(n);

        for(auto &e:mst){
            int u=getIndex(e.u);
            int v=getIndex(e.v);
            adj[u].push_back({v,{e.cost,e.delay}});
            adj[v].push_back({u,{e.cost,e.delay}});
        }

        vector<double> dist(n,1e18), time(n,0);
        vector<int> parent(n,-1);

        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        int s=getIndex(src), d=getIndex(des);
        dist[s]=0;
        pq.push({0,s});

        while(!pq.empty()){
            auto [cd,u]=pq.top(); pq.pop();
            if(cd>dist[u]) continue;

            for(auto &[v,w]:adj[u]){
                if(dist[v]>cd+w.first){
                    dist[v]=cd+w.first;
                    time[v]=time[u]+w.second;
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        cout<<"\nShortest path in MST:\n";
        vector<int> path;
        for(int v=d;v!=-1;v=parent[v]) path.push_back(v);
        reverse(path.begin(),path.end());

        for(int i:path) cout<<ecu[i]<<" -> ";
        cout<<"END\n";

        cout<<"Path Cost: "<<dist[d];
        cout<<"\nPath Delay: "<<time[d]<<" ns\n";
    }
};

int main(){
    srand(time(nullptr));
    ecu_communication ev;

    ev.hardware_init();
    ev.build_mst();
    ev.dijkstra("Engine Control Unit","Infotainment Control Unit");

    return 0;
}
