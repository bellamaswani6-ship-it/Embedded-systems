#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

/* ---------- DATA STRUCTURES ---------- */
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

/* ---------- ECU COMMUNICATION ---------- */
class ecu_communication {

    struct link {
        string u,v;
        double delay,cost;
    };

    double a,b,c;
    double total_cost=0,total_delay=0;

    vector<link> edges;
    vector<link> mst;

    unordered_map<string,string> parent;
    unordered_map<string,int> rankk;
    unordered_set<string> activeNodes;

    unordered_map<int,string> ecu = {
        {0,"Engine Control Unit"},
        {1,"Brake Control Unit"},
        {2,"Steering Control Unit"},
        {3,"ADAS Processing Unit"},
        {4,"Battery Management System"},
        {5,"Infotainment Control Unit"}
    };

public:
    ecu_communication(){
        cout<<"\nVehicle Types:\n";
        cout<<"0)Economy  1)Luxury  2)Electric  3)Autonomous\n";

        int i;
        while(true){
            cout<<"Select vehicle type: ";
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<"Invalid choice\n";
        }

        a=vehicle[i].a;
        b=vehicle[i].b;
        c=vehicle[i].c;

        init_dsu();
    }

    /* ---------- HARDWARE INPUT ---------- */
    void hardware_init(){
        cout<<"\nAvailable ECUs:\n";
        for(auto &[i,n]:ecu)
            cout<<i<<" : "<<n<<endl;

        while(true){
            int ch;
            cout<<"\n1) Add Link  2) Exit : ";
            cin>>ch;
            if(ch==2) break;
            if(ch!=1){
                cout<<"Invalid input\n";
                continue;
            }

            int i,j;
            cout<<"Enter ECU numbers: ";
            cin>>i>>j;

            if(ecu.find(i)==ecu.end() || ecu.find(j)==ecu.end()){
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay] = cost_engine();
            edges.push_back({ecu[i],ecu[j],delay,cost});
            activeNodes.insert(ecu[i]);
            activeNodes.insert(ecu[j]);
        }
    }

    /* ---------- KRUSKAL MST ---------- */
    void build_mst(){
        mst.clear();
        total_cost=0;
        total_delay=0;
        init_dsu();

        sort(edges.begin(),edges.end(),
             [](auto &x, auto &y){ return x.cost < y.cost; });

        for(auto &e:edges){
            if(findp(e.u)!=findp(e.v)){
                unite(e.u,e.v);
                mst.push_back(e);
                total_cost+=e.cost;
                total_delay+=e.delay;
            }
        }

        cout<<"\n=================================\n";
        if(is_mst_possible()){
            cout<<"✅ MST POSSIBLE (Graph Connected)\n";
        }else{
            cout<<"❌ MST NOT POSSIBLE (Graph Disconnected)\n";
            cout<<"   Minimum Spanning Forest created\n";
        }
        cout<<"=================================\n";
    }

    /* ---------- DIJKSTRA ---------- */
    void run_dijkstra(){
        if(!is_mst_possible()){
            cout<<"\n❌ Cannot run Dijkstra: MST not fully connected\n";
            return;
        }

        int src,dst;
        cout<<"\nSelect Source ECU number: ";
        cin>>src;
        cout<<"Select Destination ECU number: ";
        cin>>dst;

        if(ecu.find(src)==ecu.end() || ecu.find(dst)==ecu.end()){
            cout<<"Invalid ECU selection\n";
            return;
        }

        int n = ecu.size();
        vector<vector<pair<int,double>>> adj(n);

        for(auto &e:mst){
            int u=index(e.u);
            int v=index(e.v);
            adj[u].push_back({v,e.cost});
            adj[v].push_back({u,e.cost});
        }

        vector<double> dist(n,1e18);
        vector<int> parent_node(n,-1);

        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        dist[src]=0;
        pq.push({0,src});

        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>dist[u]) continue;

            for(auto &[v,w]:adj[u]){
                if(dist[v]>d+w){
                    dist[v]=d+w;
                    parent_node[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        if(dist[dst]>=1e18){
            cout<<"\n❌ No path exists between selected ECUs\n";
            return;
        }

        cout<<"\nShortest Path:\n";
        vector<int> path;
        for(int v=dst;v!=-1;v=parent_node[v])
            path.push_back(v);
        reverse(path.begin(),path.end());

        for(int i:path)
            cout<<ecu[i]<<" -> ";
        cout<<"END\n";

        cout<<"Path Cost: "<<dist[dst]<<endl;
    }

private:
    pair<double,double> cost_engine(){
        int dist = 1 + rand()%5;
        double delay = dist / 0.2;

        int t;
        while(true){
            cout<<"Select cable type (0/1/2): ";
            cin>>t;
            if(t>=0 && t<=2) break;
            cout<<"Invalid cable type\n";
        }

        double power_loss =
            cabel[t].current * cabel[t].current * cabel[t].resistance;

        double cost = a*delay + b*power_loss + c*(dist*20);
        return {cost,delay};
    }

    void init_dsu(){
        parent.clear();
        rankk.clear();
        for(auto &[i,n]:ecu){
            parent[n]=n;
            rankk[n]=0;
        }
    }

    string findp(string x){
        if(parent[x]==x) return x;
        return parent[x]=findp(parent[x]);
    }

    void unite(string a,string b){
        a=findp(a); b=findp(b);
        if(rankk[a]<rankk[b]) parent[a]=b;
        else if(rankk[b]<rankk[a]) parent[b]=a;
        else{ parent[b]=a; rankk[a]++; }
    }

    bool is_mst_possible(){
        if(activeNodes.empty()) return false;
        return mst.size() == activeNodes.size()-1;
    }

    int index(const string& s){
        for(auto &[i,n]:ecu)
            if(n==s) return i;
        return -1;
    }
};

/* ---------- MAIN ---------- */
int main(){
    srand(time(nullptr));

    ecu_communication ev;
    ev.hardware_init();
    ev.build_mst();
    ev.run_dijkstra();

    return 0;
}

