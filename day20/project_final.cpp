#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <unordered_set>
#include <limits>

using namespace std;

/* ---------------- DATA ---------------- */

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
    {35,50,12.5},
    {40,65,14.5},
    {10,40,13.5}
};

/* ================= ECU COMMUNICATION ================= */

class ecu_communication {

    struct communication_link {
        string u,v;
        double delay,cost;
    };

    double a,b,c;
    double ts_cost = 0, tp_delay = 0;

    vector<communication_link> links;
    vector<communication_link> mst;

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
    /* -------- NORMAL CONSTRUCTOR (THAR) -------- */
    ecu_communication() {
		cout<<"process started to determine minimum link cost\n";
        cout<<"\nVehicle Types:\n";
        cout<<"0) Economy  1) Luxury  2) Electric  3) Autonomous\n";

        int i;
        while(true){
            cout<<"Select vehicle type: ";
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<"Invalid selection\n";
        }

        a = vehicle[i].a;
        b = vehicle[i].b;
        c = vehicle[i].c;

        init_dsu();
    }

    /* -------- COPY CONSTRUCTOR (BENZ FROM THAR) -------- */
    ecu_communication(const ecu_communication& old) {
        cout<<"\nCopying ECU architecture from THAR to BENZ...\n";

        a = old.a;
        b = old.b;
        c = old.c;

        links = old.links;
        ecu   = old.ecu;
        activeNodes = old.activeNodes;

        init_dsu();
    }

    /* -------- ADD AIRBAG ECU (BENZ FEATURE) -------- */
    void add_airbag_ecu() {
        int id = ecu.size();
        ecu[id] = "Airbag Control Unit";

        parent["Airbag Control Unit"] = "Airbag Control Unit";
        rankk["Airbag Control Unit"] = 0;

        cout<<"\nAdded Airbag Control Unit (Luxury Safety Feature)\n";

        // Realistic safety connections
        links.push_back({
            "Airbag Control Unit",
            "Brake Control Unit",
            3.0,
            420.0
        });

        links.push_back({
            "Airbag Control Unit",
            "ADAS Processing Unit",
            2.5,
            480.0
        });

        activeNodes.insert("Airbag Control Unit");
        activeNodes.insert("Brake Control Unit");
        activeNodes.insert("ADAS Processing Unit");
    }

    /* ---------------- HARDWARE INPUT ---------------- */

    void hardware_init() {
        cout<<"\nAvailable ECUs:\n";
        for(auto &[i,n]:ecu)
            cout<<" "<<i<<" : "<<n<<endl;

        while(true){
            cout<<"\n1) Add Link  2) Exit : ";
            int ch; cin>>ch;
            if(ch==2) break;

            int i,j;
            cout<<"Enter ECU numbers: ";
            cin>>i>>j;

            if(ecu.find(i)==ecu.end() || ecu.find(j)==ecu.end()){
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay] = cost_engine();
            links.push_back({ecu[i],ecu[j],delay,cost});
            activeNodes.insert(ecu[i]);
            activeNodes.insert(ecu[j]);
        }
    }

    /* ---------------- KRUSKAL ---------------- */

    void optimization_init() {
        mst.clear();
        ts_cost = tp_delay = 0;
        init_dsu();

        sort(links.begin(), links.end(),
            [](auto &a, auto &b){ return a.cost < b.cost; });

        for(auto &e : links){
            if(findp(e.u) != findp(e.v)){
                unite(e.u,e.v);
                mst.push_back(e);
                ts_cost += e.cost;
                tp_delay += e.delay;
            }
        }

        cout<<"\nMST Result:\n";
        cout<<left<<setw(28)<<"ECU 1"<<setw(28)<<"ECU 2"
            <<setw(10)<<"Cost"<<"Delay\n";
        cout<<string(70,'-')<<endl;

        for(auto &e:mst){
            cout<<setw(28)<<e.u<<setw(28)<<e.v
                <<setw(10)<<fixed<<setprecision(2)<<e.cost
                <<e.delay<<" ns\n";
        }

        cout<<"\nTotal Cost  : "<<ts_cost;
        cout<<"\nTotal Delay : "<<tp_delay<<" ns\n";
    }

    /* --------- SUGGEST MISSING LINKS --------- */

    bool suggest_missing_links() {
        unordered_map<string, vector<string>> comps;

        for(auto &n:activeNodes)
            comps[findp(n)].push_back(n);

        if(comps.size() <= 1)
            return false;

        cout<<"\n⚠ Architecture is NOT fully connected\n";
        cout<<"Suggested ECU connections:\n";

        vector<string> reps;
        for(auto &c:comps)
            reps.push_back(c.second[0]);

        for(size_t i=0;i+1<reps.size();i++)
            cout<<"  "<<reps[i]<<" <--> "<<reps[i+1]<<endl;

        cout<<"\n1) Add Links  2) Continue to Dijkstra : ";
        int ch; cin>>ch;
        return (ch == 1);
    }

    /* ---------------- DIJKSTRA ---------------- */

    void dijkstra() {
        int src,dst;
        cout<<"\nEnter Source ECU number      : ";
        cin>>src;
        cout<<"Enter Destination ECU number : ";
        cin>>dst;

        int n = ecu.size();
        vector<vector<pair<int,pair<double,double>>>> adj(n);

        for(auto &e:mst){
            int u = index(e.u);
            int v = index(e.v);
            adj[u].push_back({v,{e.cost,e.delay}});
            adj[v].push_back({u,{e.cost,e.delay}});
        }

        vector<double> dist(n,1e18), time(n,0);
        vector<int> par(n,-1);

        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        dist[src]=0;
        pq.push({0,src});

        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>dist[u]) continue;

            for(auto &[v,w]:adj[u]){
                if(dist[v] > d + w.first){
                    dist[v] = d + w.first;
                    time[v] = time[u] + w.second;
                    par[v] = u;
                    pq.push({dist[v],v});
                }
            }
        }

        if(dist[dst] >= 1e18){
            cout<<"\n❌ No path exists between selected ECUs\n";
            return;
        }

        cout<<"\nShortest Path:\n";
        vector<int> path;
        for(int v=dst;v!=-1;v=par[v])
            path.push_back(v);
        reverse(path.begin(),path.end());

        for(int i:path)
            cout<<ecu[i]<<" -> ";
        cout<<"END\n";

        cout<<"\nPath Cost  : "<<dist[dst];
        cout<<"\nPath Delay : "<<time[dst]<<" ns\n";
    }

	~ecu_communication()
	{
		cout<<"successfully completed determine minimum  cost communication system"<<endl;
	}

private:
    pair<double,double> cost_engine() {
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

    void init_dsu() {
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
        a=findp(a);
        b=findp(b);
        if(rankk[a]<rankk[b]) 
          parent[a]=b;
        else if(rankk[b]<rankk[a]) 
           parent[b]=a;
        else
       { parent[b]=a; rankk[a]++; }
    }

    int index(const string& s){
        for(auto &[i,n]:ecu)
            if(n==s) return i;
        return -1;
    }
};

/* ================= MAIN ================= */

int main(){
    srand(time(nullptr));

    cout<<"\n===== DESIGNING THAR =====\n";
    ecu_communication thar;
    thar.hardware_init();
    thar.optimization_init();

    if(thar.suggest_missing_links()){
        thar.hardware_init();
        thar.optimization_init();
    }
    thar.dijkstra();

    cout<<"\n===== DESIGNING BENZ =====\n";
    ecu_communication benz = thar;   // COPY CONSTRUCTOR
    benz.add_airbag_ecu();            // EXTRA FEATURE
    benz.optimization_init();

    if(benz.suggest_missing_links()){
        benz.hardware_init();
        benz.optimization_init();
    }
    benz.dijkstra();

    return 0;
} 
