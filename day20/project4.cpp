#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <queue>
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

    ecu_communication(ecu_communication& old) {
        cout<<"copying communication links from model1 to model2"<<endl;
        a=old.a; b=old.b; c=old.c;
        link=old.link;

        for(auto& [index,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
    }
private:

    pair<double,double> cost_computation_engine() {
        int distance = 1 + rand()%5;
        const double signal_speed = 0.2;
        double delay = distance / signal_speed;

        int cabel_type;
        cout<<"select cable type (0/1/2): ";
        cin>>cabel_type;

        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;

        double power_loss = current * current * resistance;
        double link_cost = a*delay + b*power_loss + c*(distance*20);

        return {link_cost, delay};
    }

    void hardware_modelling() {
        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;

        while(true){
            int choice;
            cout<<"1)enter  2)exit: ";
            cin>>choice;
            if(choice!=1) return;

            int i,j;
            cout<<"enter two ECU numbers: ";
            cin>>i>>j;

            if(m.find(i)==m.end() || m.find(j)==m.end()){
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay] = cost_computation_engine();
            link.push_back({m[i],m[j],delay,cost});
        }
    }

    // ---------- KRUSKAL ----------
    void optimization_engine() {
        ts_cost = 0;
        tp_delay = 0;
        mst_link.clear();

        sort(link.begin(), link.end(),
             [](auto &a, auto &b){ return a.link_cost < b.link_cost; });

        int cnt = 0;
        for(auto &it: link){
            if(find_parent(it.unit1) != find_parent(it.unit2)){
                union_set(it.unit1, it.unit2);
                mst_link.push_back(it);
                ts_cost += it.link_cost;
                tp_delay += it.delay;
                if(++cnt == m.size()-1) break;
            }
        }

        if(cnt != m.size()-1){
            cout << "\nWarning: Graph is not fully connected. MST not possible.\n";
        }

        cout<<"\n[KRUSKAL] ECU 1                     ECU 2                     Cost        Delay\n";
        cout<<"------------------------------------------------------------\n";

        for(auto &it: mst_link){
            cout<<left
                <<setw(25)<<it.unit1
                <<setw(25)<<it.unit2
                <<setw(12)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;
        }

        cout<<"\n[KRUSKAL] Total system cost is: "<<ts_cost<<endl;
        cout<<"[KRUSKAL] Total Propagation delay is: "<<tp_delay<<" ns\n";
        cout<<"------------------------------------------------------------\n";
    }

    // ---------- PRIM ----------
    void prim_engine() {
        if(link.empty()){
            cout << "\nNo communication links available.\n";
            return;
        }

        ts_cost = 0;
        tp_delay = 0;
        mst_link.clear();

        unordered_map<string, vector<communication_link>> adj;

        for(auto &e : link){
            adj[e.unit1].push_back(e);
            adj[e.unit2].push_back({e.unit2, e.unit1, e.delay, e.link_cost});
        }

        unordered_map<string,bool> visited;
        for(auto &[i,name]: m) visited[name] = false;

        auto cmp = [](communication_link &a, communication_link &b){
            return a.link_cost > b.link_cost;
        };

        priority_queue<
            communication_link,
            vector<communication_link>,
            decltype(cmp)
        > pq(cmp);

        string start = m.begin()->second;
        visited[start] = true;

        for(auto &e : adj[start]) pq.push(e);

        int cnt = 0;

        while(!pq.empty() && cnt < m.size()-1){
            auto cur = pq.top(); pq.pop();

            if(visited[cur.unit2]) continue;

            visited[cur.unit2] = true;
            mst_link.push_back(cur);
            ts_cost += cur.link_cost;
            tp_delay += cur.delay;
            cnt++;

            for(auto &next : adj[cur.unit2]){
                if(!visited[next.unit2])
                    pq.push(next);
            }
        }

        if(cnt != m.size()-1){
            cout << "\nWarning: Graph is not fully connected. MST not possible.\n";
        }

        cout<<"\n[PRIM] ECU 1                     ECU 2                     Cost        Delay\n";
        cout<<"------------------------------------------------------------\n";

        for(auto &it: mst_link){
            cout<<left
                <<setw(25)<<it.unit1
                <<setw(25)<<it.unit2
                <<setw(12)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;
        }

        cout<<"\n[PRIM] Total system cost is: "<<ts_cost<<endl;
        cout<<"[PRIM] Total Propagation delay is: "<<tp_delay<<" ns\n";
        cout<<"------------------------------------------------------------\n";
    }

    // ---------- DSU ----------
    string find_parent(string x){
        if(parent[x]==x) return x;
        return parent[x] = find_parent(parent[x]);
    }

    void union_set(string a,string b){
        a=find_parent(a);
        b=find_parent(b);
        if(rank[a]<rank[b]) parent[a]=b;
        else if(rank[b]<rank[a]) parent[b]=a;
        else { parent[b]=a; rank[a]++; }
    }

public:
    void hardware_init(){ hardware_modelling(); }
    void optimization_init(){ optimization_engine(); }
    void prim_init(){ prim_engine(); }

    ~ecu_communication(){
        cout<<"successfully completed determine minimum cost communication system"<<endl;
    }
};

int main(){
    srand(time(nullptr));

    ecu_communication ev;
    ev.hardware_init();

    cout << "\nRunning Kruskal...\n";
    ev.optimization_init();

    cout << "\nRunning Prim...\n";
    ev.prim_init();

    return 0;
}
