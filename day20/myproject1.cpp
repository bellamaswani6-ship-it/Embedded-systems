#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <unordered_set>
#include <tuple>
#include <climits>

using namespace std;

struct vehicle_type {
    double a,b,c;
};

struct cable_type {
    int current;
    double resistance;
    double cost;
};

vehicle_type vehicle[4] = {
    {0.3,0.45,0.25},
    {0.35,0.35,0.3},
    {0.3,0.3,0.4},
    {0.45,0.20,0.35}
};

cable_type cabel[3] = {
    {35,50,12.5},{40,65,14.5},{10,40,13.5}
};

class ecu_communication {

    struct communication_link {
        string unit1, unit2;
        double delay, link_cost;
    };

    double a,b,c;
    double ts_cost = 0, tp_delay = 0;

    vector<communication_link> link;
    vector<communication_link> mst_link;

    unordered_map<string,string> parent;
    unordered_map<string,int> rank;
    unordered_set<string> activeNodes;

    unordered_map<int,string> m = {
        {0,"Engine Control Unit"},
        {1,"Brake Control Unit"},
        {2,"Steering Control Unit"},
        {3,"ADAS Processing Unit"},
        {4,"Battery Management System"},
        {5,"Infotainment Control Unit"}
    };

public:
    ecu_communication() {
        cout<<"process started to determine minimum link cost\n";
        cout<<"0)Economy 1)Luxury 2)Electric 3)Autonomous\n";

        int i;
        while(true){
            cout<<"select vehicle type: ";
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<"invalid vehicle type\n";
        }

        a=vehicle[i].a;
        b=vehicle[i].b;
        c=vehicle[i].c;

        for(auto& [idx,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
    }

private:
    // ---------- UTILS ----------
    int getindex(const string& s){
        for(auto& [i,name]:m)
            if(name==s) return i;
        return -1;
    }

    // ---------- COST ENGINE ----------
    pair<double,double> cost_computation_engine() {
        int distance = 1 + rand()%5;
        const double signal_speed = 0.2;
        double delay = distance / signal_speed;

        int cabel_type;
        while(true){
            cout<<"select cable type (0/1/2): ";
            cin>>cabel_type;
            if(cabel_type>=0 && cabel_type<=2) break;
            cout<<"invalid cable type\n";
        }

        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;

        double power_loss = current * current * resistance;
        double link_cost = a*delay + b*power_loss + c*(distance*20);

        return {link_cost, delay};
    }

    // ---------- HARDWARE ----------
    void hardware_modelling() {
        cout<<"\nAvailable ECUs:\n";
        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;

        while(true){
            int choice;
            cout<<"1)Add Link  2)exit: ";
            cin>>choice;
            if(choice==2) break;
            if(choice!=1) continue;

            int i,j;
            cout<<"enter two ECU numbers: ";
            cin>>i>>j;

            if(m.find(i)==m.end() || m.find(j)==m.end()){
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay] = cost_computation_engine();
            link.push_back({m[i],m[j],delay,cost});
            activeNodes.insert(m[i]);
            activeNodes.insert(m[j]);
        }
    }

    // ---------- DSU ----------
    string find_parent(string x){
        if(parent[x]==x) return x;
        return parent[x]=find_parent(parent[x]);
    }

    void union_set(string a,string b){
        a=find_parent(a);
        b=find_parent(b);
        if(rank[a]<rank[b]) parent[a]=b;
        else if(rank[b]<rank[a]) parent[b]=a;
        else{ parent[b]=a; rank[a]++; }
    }

    void reset_mst(){
        mst_link.clear();
        for(auto& [i,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
    }

    // ---------- KRUSKAL ----------
    void optimization_engine() {
        if(activeNodes.size()<2){
            cout<<"Not enough ECUs connected\n";
            return;
        }

        reset_mst();
        ts_cost=tp_delay=0;

        sort(link.begin(),link.end(),
             [](auto&a,auto&b){return a.link_cost<b.link_cost;});

        int cnt=0;
        for(auto&e:link){
            if(find_parent(e.unit1)!=find_parent(e.unit2)){
                union_set(e.unit1,e.unit2);
                mst_link.push_back(e);
                ts_cost+=e.link_cost;
                tp_delay+=e.delay;
                if(++cnt==activeNodes.size()-1) break;
            }
        }

        cout<<"\nECU 1                     ECU 2                     Cost     Delay\n";
        cout<<"--------------------------------------------------------------\n";
        for(auto&e:mst_link){
            cout<<left<<setw(25)<<e.unit1<<"<-->"<<setw(25)<<e.unit2
                <<setw(10)<<fixed<<setprecision(2)<<e.link_cost
                <<setw(8)<<e.delay<<endl;
        }

        cout<<"\nTotal cost: "<<ts_cost<<"\nTotal delay: "<<tp_delay<<" ns\n";
    }

    // ---------- DIJKSTRA ----------
    void dijkstra_imp(string src,string des){
        int n=m.size();
        vector<vector<pair<int,pair<double,double>>>> adj(n);

        for(auto&e:link){
            int u=getindex(e.unit1);
            int v=getindex(e.unit2);
            adj[u].push_back({v,{e.link_cost,e.delay}});
            adj[v].push_back({u,{e.link_cost,e.delay}});
        }

        vector<double> dist(n,1e18), time(n,0);
        vector<int> parent(n,-1);
        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        int s=getindex(src), d=getindex(des);
        dist[s]=0;
        pq.push({0,s});

        while(!pq.empty()){
            auto [cd,u]=pq.top(); pq.pop();
            if(cd>dist[u]) continue;
            for(auto&[v,w]:adj[u]){
                if(dist[v]>cd+w.first){
                    dist[v]=cd+w.first;
                    time[v]=time[u]+w.second;
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        cout<<"\nShortest path cost: "<<dist[d];
        cout<<"\nTotal delay: "<<time[d]<<" ns\n";
    }

public:
    void hardware_init(){ hardware_modelling(); }
    void optimization_init(){ optimization_engine(); }
    void dijkstra_init(){
        dijkstra_imp("Engine Control Unit","Infotainment Control Unit");
    }
};

int main(){
    srand(time(nullptr));
    ecu_communication ev;
    ev.hardware_init();
    ev.optimization_init();
    ev.dijkstra_init();
    return 0;
}
