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
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define VIOLET  "\033[95m"
#define PINK    "\033[95m"
#define BOLD    "\033[1m"
#define YELLOW "\033[33m"
#define ORANGE "\033[38;5;208m"
struct vehicle_type {
    double a,b,c;  
};

struct cable_type {
    string name;
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
    {"CAN",35,50,12.5},{"FlexRay",40,65,14.5},{"Ethernet",10,40,13.5}           //it stores current,resistance,cost of 3 type of cabels
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
        cout << BOLD << MAGENTA << "\n=================================\n" << RESET;
        cout << BOLD << YELLOW << "      NEW ARCHITECTURE\n" << RESET;
        cout << BOLD << MAGENTA << "=================================\n\n" << RESET;
        cout<<"vehicle type\n"<<RESET;
        cout<<"0)Economy 1)Luxury 2)Electric 3)Autonomous\n"<<RESET;

        int i;
        while(true){
            cout<<VIOLET<<"select vehicle type: "<<RESET;
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<RED<<"invalid vehicle type\n"<<RESET;
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
        cout<<MAGENTA<<"copying communication links from model1 to model2"<<RESET<<endl;
        a=old.a; b=old.b; c=old.c;
        link=old.link;
        m=old.m;
        activeNodes=old.activeNodes;          //used to copy one graph to another
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
                  cout << VIOLET<<"select cable type (0/1/2): "<<RESET;
                  cin >> cabel_type;
                  cout<<endl;
                  if (cabel_type >= 0 && cabel_type <= 2)
                      break;
                  cout <<RED<< "invalid cable type\n"<<RESET;  //if given invalid data type
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

      void availableecus()
      {
         cout<<PINK<<"\nAvailable ECUs:\n"<<RESET;
        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;  // displays available ecu's to select
            cout<<endl;
        }
        
        void availablecables()
        {
            cout<<PINK<<"\n Available cables\n"<<RESET;
             int i=0;
            for(auto &it:cabel)
            {
             cout<<left<<setw(9)<<it.name<<" :"<<it.current<<"mA   "<<it.resistance<<"mohm  "<<it.cost<<"rs  "<<endl;
             i++;
             }
             cout<<endl;
        }
            

    
    // -------- HARDWARE INPUT --------
    void hardware_modelling() {
            availableecus();
            availablecables();
        while(true){
            int choice;
          label2:cout<<"1)Connect ECU's with cable\n2)exit\n";
             cout<<ORANGE<<"choose your choice : "<<RESET;
            cin>>choice;
            cout<<endl;
            if(choice<1||choice>2) //if choice is not between range again requesting user to enter valid choice
            {
               cout<<RED<<"invalid input"<<RESET<<endl;   
               cin.clear();  // reset fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
               goto label2;
            }
            if(choice ==2)
            {
               break;   // for exit it will execute to get out from loop
            }

            int i,j;
            cout<<GREEN<<"enter two ECU numbers (ex:ecu1 ecu2): "<<RESET;
            cin>>i>>j;   

            if(m.find(i)==m.end() || m.find(j)==m.end()){  //if selecting nodes are not present it skips present iteration and again loop executes
                cout<<RED<<"Invalid ECU index\n"<<RESET;
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

        cout << VIOLET<<"\n disconected architecture's:\n"<<RESET;
        int comp_id = 1;

        for(auto &comp : components){
            cout << " architecture  " << comp_id++ << ":\n";
            for(auto &node : comp.second){
                cout << "   - " << node << "\n";
            }
        }

        if(components.size() > 1){
            cout <<ORANGE<< "\n Suggested links to connect architecture's:\n"<<RESET;

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
            cout <<RED<< "\n Architecture  is NOT fully connected.\n"<<RESET;
            print_connected_components();
            cout<<GREEN<<"Add the suggested or desired links to form a connected structure"<<RESET<<endl;
            hardware_modelling();
            goto label3;        
        }

            print_all_links();  
            print_mst_links();
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
        
  void run_dijkstra()
    {
    int src, des;
    cout << BLUE<<"\n==============================================\n"<<RESET;
        cout <<BOLD<<PINK<< "    MINIMIZING DELAY BETWEEN SRC AND DEST    "  <<RESET<<endl;
        cout <<BLUE<< "==============================================\n"<<RESET<<endl;

    cout << "\nEnter Source ECU number      : "<<RESET;
    cin >> src;
    cout << "Enter Destination ECU number : "<<RESET;
    cin >> des;

    double user_delay;
    cout << GREEN<<"Enter Maximum Allowed Delay  : "<<RESET;
    cin >> user_delay;

    while(true)
    {
        int n = m.size();
        vector<vector<pair<int,pair<double,double>>>> adj(n);

        // Build graph from MST
        for(auto &e : mst_link)
        {
            int u = getIndex(e.unit1);
            int v = getIndex(e.unit2);
            adj[u].push_back({v,{e.link_cost,e.delay}});
            adj[v].push_back({u,{e.link_cost,e.delay}});
        }

        vector<double> dist(n,1e18), time(n,0);
        vector<int> parent(n,-1);

        priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

        dist[src] = 0;
        pq.push({0,src});

        while(!pq.empty())
        {
            auto [cd,u] = pq.top(); pq.pop();
            if(cd > dist[u]) continue;

            for(auto &[v,w] : adj[u])
            {
                if(dist[v] > cd + w.first)
                {
                    dist[v] = cd + w.first;
                    time[v] = time[u] + w.second;
                    parent[v] = u;
                    pq.push({dist[v],v});
                }
            }
        }

        if(dist[des] >= 1e18)
        {
            cout << RED<<"No path exists.\n"<<RESET;
            return;
        }

        // Build path
        vector<int> path;
        for(int v=des; v!=-1; v=parent[v])
            path.push_back(v);

        reverse(path.begin(), path.end());

        cout << MAGENTA<<"\nCurrent Path:\n"<<RESET;
        for(int i : path)
            cout << m[i] << " -> ";
        cout << "END\n";

        cout << VIOLET<<"Total Delay : " << time[des] << " ns\n"<<RESET;

        if(time[des] <= user_delay)
        {
            cout <<GREEN<< "\n   Delay constraint satisfied.\n"<<RESET;
            break;
        }

        cout << RED<<"\n⚠ Delay exceeds allowed limit.\n"<<RESET;

        // Show path links
        for(size_t i=0; i<path.size()-1; i++)
        {
            cout << i << ") "
                 << m[path[i]] << " <--> "
                 << m[path[i+1]] << endl;
        }
        cout<<path.size()-1<<")"<<"exit with out updating"<<endl;
        int choice;
        cout << GREEN<<"\nSelect link index to modify or exit: "<<RESET;
        cin >> choice;
        cin.clear();
        cin.ignore();
        
        if(choice==path.size()-1)
            return;
        if(choice < 0 || choice >= path.size())
        {
            cout << RED<<"Invalid choice.\n"<<RESET;
            continue;
        }

        string u = m[path[choice]];
        string v = m[path[choice+1]];

        // Modify only that MST edge
        for(auto &l : mst_link)
        {
            if((l.unit1==u && l.unit2==v) ||
               (l.unit1==v && l.unit2==u))
            {
                cout << VIOLET<<"Select new cable type (0/1/2): "<<RESET;
                int cable_type;
                cin >> cable_type;
                cin.clear();
                cin.ignore();

                cout << "Enter new distance: ";
                int distance;
                cin >> distance;
                cin.clear();
                cin.ignore();

                const double signal_speed = 0.2;
                double new_delay = distance / signal_speed;

                int current = cabel[cable_type].current;
                double resistance = cabel[cable_type].resistance;

                double power_loss = current * current * resistance;
                double new_cost =
                    a*new_delay + b*power_loss + c*(distance*20);

                l.delay = new_delay;
                l.link_cost = new_cost;

                cout << MAGENTA<<"\nLink updated.\n"<<RESET;
                break;
            }
        }

        cout <<BLUE<< "\nminimizing the delay between src and dest ecu...\n"<<RESET;
    }
   }
   
   
   
   // adding ECU
    void add_ecu(){
    availableecus();
    int id;
    cout <<BLUE<< "\nEnter new ECU ID: "<<RESET;
    cin >> id;

    if(m.find(id) != m.end()){
        cout << RED<<"ECU already exists.\n"<<RESET;
        return;
    }

    cout <<PINK<< "Enter ECU Name: "<<RESET;
    cin.ignore(); 
    string name;
    getline(cin, name);

    m[id] = name;

    parent[name] = name;
    rank[name] = 0;
  
    cout << GREEN<<"ECU Added Successfully.\n"<<RESET;
}


void print_mst_links()
  {
   cout<<BOLD<<MAGENTA<<"\n ECU 1                       ECU 2                      Cost         Delay\n"<<RESET;
        cout<<"------------------------------------------------------------------------------\n";

        for(auto &it: mst_link){
            cout<<left
                <<setw(26)<<it.unit1
                <<"<-->"<<setw(26)<<it.unit2
                <<setw(13)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;
        }

        cout<<GREEN<<"\n Total system cost is: "<<ts_cost<<endl;
        cout<<" Total Propagation delay is: "<<tp_delay<<" ns\n"<<RESET;
        cout<<"------------------------------------------------------------------------------\n";
   }

void print_all_links() {
       double delay1=0,cost=0;
    cout <<BOLD<<ORANGE<< "\n ALL CURRENT CONNECTED ECU'S:\n"<<RESET;
    cout << "------------------------------------------------------------\n";
    cout<<VIOLET<<"ECU 1                       ECU 2                      Cost         Delay\n"<<RESET;
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
    cout<<GREEN<<"Total System cost without any optimization: "<<cost<<endl;
    cout<<"Total Propagation delay without any optimization: "<<delay1<<" "<<"ns"<<endl<<RESET;
    cout<<"------------------------------------------------------------\n";
}


public:
    void hardware_init(){ hardware_modelling(); }
    void optimization_init(){ optimization_engine(); }
    void dijkstra(){run_dijkstra();}
    
    
    
    void architecture_menu(){
    while(true){

        cout << BOLD<<BLUE<<"\n=================================\n"<<RESET;
        cout << BOLD<<PINK<<"      ARCHITECTURE MENU\n"<<RESET;
        cout << BOLD<<BLUE<<"=================================\n"<<RESET;

        cout << "1) Add ECU\n";
        cout << "2) create links\n";
        cout <<"3) optimize the architecture\n";
        cout <<"4) optimize delay between src and dest Ecu\n";
        cout <<"5) Exit Architecture Menu\n";
        cout << GREEN<<"Select option: "<<RESET;

        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice){
        case 1: add_ecu(); break;
        case 2: hardware_init(); break;
        case 3: optimization_init(); break;
        case 4: run_dijkstra(); break;
        case 5: return;
        default:
            cout << RED<<"Invalid choice.\n"<<RESET;
        }
    }
}
  
  
    ~ecu_communication(){
        cout<<GREEN<<"successfully completed determine minimum cost communication system"<<endl<<RESET;
    }
    
    
};

int main(){
    srand(time(nullptr));

    unique_ptr<ecu_communication> current_arch = nullptr;

    while(true){

        cout << "\n=================================\n";
        cout << VIOLET<<"        MAIN SYSTEM MENU\n"<<RESET;
        cout << "=================================\n";
        cout << "1) Create New Architecture\n";
        cout << "2) Copy Existing Architecture\n";
        cout << "3) Exit\n"<<endl;
        cout << BLUE<<"Select option: "<<RESET;

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
                cout <<RED<< "No architecture exists to copy.\n"<<RESET;
                break;
            }

            ecu_communication copied(*current_arch);  //we are not copying unique_ptr copying only object point to it so no error
            break;
        }
        // EXIT
        case 3:
            return 0;

        default:
            cout <<RED<< "Invalid choice.\n"<<RESET;
        }
    }

    return 0;
}
