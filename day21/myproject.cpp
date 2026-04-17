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
#include<limits>
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
    {0.35,0.35,0.3},   //it stores a,b,c values of economy car,luxury,electric,autonomous     
    {0.3,0.3,0.4},
    {0.45,0.20,0.35}
};

cable_type cabel[3] = {
    {35,50,12.5},{40,65,14.5},{10,40,13.5}           //it stores current,resistance,cost of 3 type of cabels
};

class ecu_communication {

    struct communication_link {
        string unit1, unit2;            //units are ecu's
        double delay, link_cost;        //delay is what time will take a signal to reach from one ecu to other 
    };

    double a,b,c;
	double ts_cost = 0, tp_delay = 0;  //ts_cost=total system cost ,tp_delay=total propogation delay

    vector<communication_link> link;     //edge list
    vector<communication_link> mst_link;  //store for future purpose

    unordered_map<string,string> parent;
    unordered_map<string,int> rank;
    
    unordered_set<string> activeNodes;//used to add active nodes

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
        cout<<"0)Economy 1)Luxury 2)Electric 3)Autonomous\n";   //selecting which type of car

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
        architecture_menu();  //giving menu to select to add ecu/create link/optimize
    }

    ecu_communication(const ecu_communication& old) {
        cout<<"copying communication links from model1 to model2"<<endl;
        a=old.a; b=old.b; c=old.c;
        link=old.link;
        m=old.m;
        activeNodes=old.activeNodes;          //used to copy one graph to another
        for(auto& [index,name]:m){
            parent[name]=name;
            rank[name]=0;
             
        }
        architecture_menu();
    }

private:

    // -------- COST ENGINE --------
    pair<double,double> cost_computation_engine() {
        int distance = 1 + rand()%5;   //distance  from (1 -5)meters
        const double signal_speed = 0.2; //converting signal speed into ns
        double delay = distance / signal_speed;

        int cabel_type;
         while (true) {
                  cout << "select cable type (0/1/2): ";
                  cin >> cabel_type;
                  if (cabel_type >= 0 && cabel_type <= 2)
                      break;
                  cout << "invalid cable type\n";  //if given invalid data type
                  cin.clear();  // reset fail state
                  cin.ignore(numeric_limits<streamsize>::max(), '\n'); //take up to infinite and delete everything until \n found
                  }
        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;
             
        double power_loss = current * current * resistance;
        double cabel_cost=cabel[cabel_type].cost;
        double link_cost = a*delay + b*power_loss + c*(distance*cabel_cost);//formula to calculate link codt

        return {link_cost, delay};
             }

    // -------- HARDWARE INPUT --------
    void hardware_modelling() {
          cout<<"\nAvailable ECUs:\n";
        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;  // displays available ecu's to select

        while(true){
            int choice;
          label2:cout<<"1)Add Link  2)exit: ";
            cin>>choice;
            if(choice<1||choice>2) //if choice is not between range again requesting user to enter valid choice
            {
               cout<<"invalid input"<<endl;   
               cin.clear();  // reset fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
               goto label2;
            }
            if(choice ==2)
            {
               break;   // for exit it will execute to get out from loop
            }

            int i,j;
            cout<<"enter two ECU numbers: ";
            cin>>i>>j;   

            if(m.find(i)==m.end() || m.find(j)==m.end()){  //if selecting nodes are not present it skips present iteration and again loop executes
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay] = cost_computation_engine();  //structure binding
            link.push_back({m[i],m[j],delay,cost});
            activeNodes.insert(m[i]);  
            activeNodes.insert(m[j]);
        }
    }

    // -------- PRINT COMPONENTS --------
    void print_connected_components() {
        unordered_map<string, vector<string>> components;

        for(auto &name : activeNodes){
            string root = find_parent(name);
            components[root].push_back(name);
        }

        cout << "\n Connected ecu's:\n";
        int comp_id = 1;

        for(auto &comp : components){
            cout << "ecu's  " << comp_id++ << ":\n";
            for(auto &node : comp.second){
                cout << "   - " << node << "\n";
            }
        }

        if(components.size() > 1){
            cout << "\n Suggested links to connect ecu's:\n";

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

        if(cnt !=activeNodes.size()-1 && activeNodes.size()>0){
            cout << "\n Architecture  is NOT fully connected.\n";
            print_connected_components();
            cout<<"Add the suggested or desired links to form a connected structure"<<endl;
            hardware_modelling();
            goto label3;        
        }

            print_all_links();  

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
    int getIndex(const string &s){
        for(auto &[i,n]:m)
            if(n==s) return i;
        return -1;
    }
    void run_dijkstra(){
        int src, des;
        cout << "\n==============================================\n";
        cout << "        COST-EFFICIENT ECU COMMUNICATION  PATH  "  <<endl;
        cout << "==============================================\n";

        cout << "Enter Source ECU number      : ";
        cin >> src;
        cout << "Enter Destination ECU number : ";
        cin >> des;

        int n = m.size();
        vector<vector<pair<int,pair<double,double>>>> adj(n);

        for(auto &e:mst_link){
            int u=getIndex(e.unit1);
            int v=getIndex(e.unit2);
            adj[u].push_back({v,{e.link_cost,e.delay}});
            adj[v].push_back({u,{e.link_cost,e.delay}});
        }

        vector<double> dist(n,1e18), time(n,0);
        vector<int> parent(n,-1);

        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        dist[src]=0;
        pq.push({0,src});

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

        if(dist[des]>=1e18){
            cout << "\n❌ No path exists between selected ECUs in MST\n";
            return;
        }
           
if(activeNodes.find(m[src]) == activeNodes.end() ||
   activeNodes.find(m[des]) == activeNodes.end()){
    cout << "\n❌ One or both ECUs are not connected in architecture.\n";
    return;
}
        cout << "\nPath:\n";
        vector<int> path;
        for(int v=des;v!=-1;v=parent[v]) path.push_back(v);
        reverse(path.begin(),path.end());

        for(int i:path)
            cout << m[i] << " -> ";
        cout << "END\n";

        cout << "\nTotal Path Cost  : " << dist[des];
        cout << "\nTotal Path Delay : " << time[des] << " ns\n";
    }
    void add_ecu(){
    int id;
    cout << "\nEnter new ECU ID: ";
    cin >> id;

    if(m.find(id) != m.end()){
        cout << "ECU already exists.\n";
        return;
    }

    cout << "Enter ECU Name: ";
    cin.ignore(); 
    string name;
    getline(cin, name);

    m[id] = name;

    parent[name] = name;
    rank[name] = 0;
  
    cout << "ECU Added Successfully.\n";
}
void print_all_links() {
       double delay1=0,cost=0;
    cout << "\n ALL CURRENT CONNECTED ECU'S:\n";
    cout << "------------------------------------------------------------\n";
    cout<<"ECU 1                       ECU 2                      Cost         Delay\n";
    cout<<"------------------------------------------------------------\n";

    for(auto &it: link){
        cout<<left
            <<setw(26)<<it.unit1
            <<"<-->"<<setw(26)<<it.unit2
            <<setw(13)<<fixed<<setprecision(2)<<it.link_cost
            <<setw(8)<<it.delay
            <<endl;
        delay1+=it.delay;
       cost+=it.link_cost;
    }
    cout<<endl;
    cout<<"Total System cost without any optimization: "<<cost<<endl;
    cout<<"Total Propagation delay without any optimization: "<<delay1<<" "<<"ns"<<endl;
    cout<<"------------------------------------------------------------\n";
}
public:
    void hardware_init(){ hardware_modelling(); }
    void optimization_init(){ optimization_engine(); }
    void dijkstra(){run_dijkstra();}
    
    void architecture_menu(){

    while(true){

        cout << "\n=================================\n";
        cout << "      ARCHITECTURE MENU\n";
        cout << "=================================\n";
        cout << "1) Add ECU\n";
        cout << "2) create links\n";
        cout << "3) optimize,run_dijkstra and Exit Architecture Menu\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
           
        case 1:
            add_ecu();
            break;

        case 2:
            hardware_modelling();
            break;

        case 3:
             optimization_engine();
             run_dijkstra();
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
    ~ecu_communication(){
        cout<<"successfully completed determine minimum cost communication system"<<endl;
    }
};

int main(){
    srand(time(nullptr));

    unique_ptr<ecu_communication> current_arch = nullptr;

    while(true){

        cout << "\n=================================\n";
        cout << "        MAIN SYSTEM MENU\n";
        cout << "=================================\n";
        cout << "1) Create New Architecture\n";
        cout << "2) Copy Existing Architecture\n";
        cout << "3) Exit\n";
        cout << "Select option: ";

        int ch;
        cin >> ch;

        switch(ch){

        // CREATE NEW
        case 1:
        {
            current_arch = make_unique<ecu_communication>();
            break;
        }
        // COPY EXISTING
        case 2:
        {
            if(!current_arch){                                       
                cout << "❌ No architecture exists to copy.\n";
                break;
            }

            ecu_communication copied(*current_arch);  //we are not copying unique_ptr copying only object point to it so no error
            break;
        }
        // EXIT
        case 3:
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
