#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<unordered_set>
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

    // -------- COST ENGINE --------
    pair<double,double> cost_computation_engine() {
        int distance = 1 + rand()%5;
        const double signal_speed = 0.2;
        double delay = distance / signal_speed;

        int cabel_type;
        label1:cout<<"select cable type (0/1/2): ";
        cin>>cabel_type;
        if(cabel_type<0||cabel_type>2)
        {
           cout<<"invalid cable type"<<endl;
           goto label1;
         }
        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;

        double power_loss = current * current * resistance;
        double link_cost = a*delay + b*power_loss + c*(distance*20);

        return {link_cost, delay};
    }

    // -------- HARDWARE INPUT --------
    void hardware_modelling() {
          cout<<"\nAvailable ECUs:\n";
        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;

        while(true){
            int choice;
           label2:cout<<"1)Add Link  2)exit: ";
            cin>>choice;
            if(choice<1||choice>2) 
            {
               cout<<"invalid input"<<endl;
               goto label2;
               }
            if(choice ==2)
            {
               break;
            }

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

    // -------- PRINT COMPONENTS --------
    void print_connected_components() {
        unordered_map<string, vector<string>> components;

        for(auto &[idx,name] : m){
            string root = find_parent(name);
            components[root].push_back(name);
        }

        cout << "\n Connected Components:\n";
        int comp_id = 1;

        for(auto &comp : components){
            cout << "Component " << comp_id++ << ":\n";
            for(auto &node : comp.second){
                cout << "   - " << node << "\n";
            }
        }

        if(components.size() > 1){
            cout << "\n Suggested edges to connect components:\n";

            vector<string> reps;
            for(auto &comp : components)
                reps.push_back(comp.second[0]);

            for(size_t i = 0; i < reps.size(); i++){
                for(size_t j = i+1; j < reps.size(); j++){
                    cout << "   Connect: "
                         << reps[i] << "  <-->  " << reps[j] << "\n";
                }
            }
        }
    }
    void reset_mst()
    {
      mst_link.clear();
      for(auto& [index,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
    }
    // -------- KRUSKAL --------
    void optimization_engine() {
       label3:ts_cost = 0;
        tp_delay = 0;
        reset_mst();

        sort(link.begin(), link.end(),
             [](auto &a, auto &b){ return a.link_cost < b.link_cost; });

        int cnt = 0;
        for(auto &it: link){
            if(find_parent(it.unit1) != find_parent(it.unit2)){
                union_set(it.unit1, it.unit2);
                mst_link.push_back(it);
                ts_cost += it.link_cost;
                tp_delay += it.delay;
                if(++cnt == activeNodes.size()-1) break;
            }
        }

        if(cnt !=activeNodes.size()-1){
            cout << "\n Architecture  is NOT fully connected.\n";
            cout << "Minimum Spanning Forest generated.\n";
            print_connected_components();
            cout<<"Add the suggested or desired links to form a connected structure"<<endl;
            hardware_modelling();
            goto label3;        
        }

        cout<<"\n ECU 1                       ECU 2                      Cost         Delay\n";
        cout<<"------------------------------------------------------------\n";

        for(auto &it: mst_link){
            cout<<left
                <<setw(26)<<it.unit1
                <<"<-->"<<setw(26)<<it.unit2
                <<setw(13)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;
        }

        cout<<"\n Total system cost is: "<<ts_cost<<endl;
        cout<<" Total Propagation delay is: "<<tp_delay<<" ns\n";
        cout<<"------------------------------------------------------------\n";
    }

    // -------- PRIM --------
   /* void prim_engine() {
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
            cout << "\n[PRIM] Graph is NOT connected. Full MST cannot be formed.\n";
            cout << "[PRIM] Only partial spanning tree was possible.\n";
            return;
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
    }*/

    // -------- DSU --------
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
    
void DIjikistras(string src,string des,
                     vector<vector<tuple<int,int,double>>>& Result,
                     vector<double>& time){

        int c=getindex(src);
        int d=getindex(des);

        //  Validate input
        if(c==-1 || d==-1){
            cout<<"Invalid Airport Entered!\n";
            return;
        }

        int n=Result.size();
        vector<long long> dist(n,LLONG_MAX);
        vector<int> parent(n,-1);
        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       greater<pair<long long,int>>> pq;

        dist[c]=0;
        time.assign(n,0);  // reset time properly

        pq.push({0,c});

        while(!pq.empty()){
            auto [distance,node]=pq.top();
            pq.pop();

            if(distance>dist[node]) continue;

            for(auto neighbour:Result[node]){
                int nn=get<0>(neighbour);
                int cost=get<1>(neighbour);
                double t=get<2>(neighbour);

                if(dist[nn]>distance+cost){
                    dist[nn]=distance+cost;
                    time[nn]=time[node]+t;
                    parent[nn]=node;
                    pq.push({dist[nn],nn});
                }
            }
        }
public:
    void hardware_init(){ hardware_modelling(); }
    void optimization_init(){ optimization_engine(); }
   // void prim_init(){ prim_engine(); }
      void dijkstra_init()
     {
        dijksta_imp();
     } 
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

   /* cout << "\nRunning Prim...\n";
    ev.prim_init();*/

    return 0;
}
