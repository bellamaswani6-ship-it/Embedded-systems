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
#include <limits>

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
    {35,50,12.5},
    {40,65,14.5},
    {10,40,13.5}
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
        cout<<"0)Economy 1)Luxury 2)Electric 3)Autonomous\n";
        int i;
        while(true){
            cout<<"Select vehicle type: ";
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<"Invalid vehicle type\n";
        }

        a=vehicle[i].a;
        b=vehicle[i].b;
        c=vehicle[i].c;

        for(auto& [idx,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
        architecture_menu();
    }

    ecu_communication(const ecu_communication& old) {
        a=old.a; b=old.b; c=old.c;
        link=old.link;
        m=old.m;
        activeNodes=old.activeNodes;

        for(auto& [idx,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
        architecture_menu();
    }

private:

    // PRINT ALL LINKS BEFORE MST
    void print_all_links() {

        if(link.empty()){
            cout << "\nNo links available.\n";
            return;
        }

        cout << "\n================ BEFORE OPTIMIZATION ================\n";
        cout<<"ECU 1                     ECU 2                     Cost       Delay\n";
        cout<<"--------------------------------------------------------------\n";

        double total_cost=0, total_delay=0;

        for(auto &it : link){
            cout<<left
                <<setw(25)<<it.unit1
                <<"<-->"<<setw(25)<<it.unit2
                <<setw(10)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;

            total_cost+=it.link_cost;
            total_delay+=it.delay;
        }

        cout<<"--------------------------------------------------------------\n";
        cout<<"Total Raw Cost  : "<<total_cost<<endl;
        cout<<"Total Raw Delay : "<<total_delay<<" ns\n";
    }

    pair<double,double> cost_computation_engine() {

        int distance = 1 + rand()%5;
        const double signal_speed = 0.2;
        double delay = distance / signal_speed;

        int cabel_type;
        while(true){
            cout<<"Select cable type (0/1/2): ";
            cin>>cabel_type;
            if(cabel_type>=0 && cabel_type<=2) break;
            cout<<"Invalid cable type\n";
        }

        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;
        double power_loss = current * current * resistance;
        double cabel_cost=cabel[cabel_type].cost;

        double link_cost = a*delay + b*power_loss + c*(distance*cabel_cost);

        return {link_cost,delay};
    }

    void hardware_modelling() {

        for(auto& [i,name]:m)
            cout<<i<<" : "<<name<<endl;

        while(true){
            int choice;
            cout<<"1)Add Link 2)Exit: ";
            cin>>choice;
            if(choice==2) break;

            int i,j;
            cout<<"Enter two ECU numbers: ";
            cin>>i>>j;

            if(m.find(i)==m.end() || m.find(j)==m.end()){
                cout<<"Invalid ECU index\n";
                continue;
            }

            auto [cost,delay]=cost_computation_engine();
            link.push_back({m[i],m[j],delay,cost});
            activeNodes.insert(m[i]);
            activeNodes.insert(m[j]);
        }
    }

    void reset_mst(){
        mst_link.clear();
        for(auto& [idx,name]:m){
            parent[name]=name;
            rank[name]=0;
        }
    }

    string find_parent(string x){
        if(parent[x]==x) return x;
        return parent[x]=find_parent(parent[x]);
    }

    void union_set(string a,string b){
        a=find_parent(a);
        b=find_parent(b);
        if(rank[a]<rank[b]) parent[a]=b;
        else if(rank[b]<rank[a]) parent[b]=a;
        else { parent[b]=a; rank[a]++; }
    }

    void optimization_engine(){

        if(link.empty()){
            cout<<"No links to optimize.\n";
            return;
        }

        ts_cost=0;
        tp_delay=0;
        reset_mst();

        print_all_links();

        sort(link.begin(),link.end(),
             [](auto &a,auto &b){return a.link_cost<b.link_cost;});

        vector<communication_link> rejected;

        for(auto &it:link){
            if(find_parent(it.unit1)!=find_parent(it.unit2)){
                union_set(it.unit1,it.unit2);
                mst_link.push_back(it);
                ts_cost+=it.link_cost;
                tp_delay+=it.delay;
            }else{
                rejected.push_back(it);
            }
        }

        cout<<"\n================ AFTER OPTIMIZATION (MST) ================\n";
        cout<<"ECU 1                     ECU 2                     Cost       Delay\n";
        cout<<"--------------------------------------------------------------\n";

        for(auto &it:mst_link){
            cout<<left
                <<setw(25)<<it.unit1
                <<"<-->"<<setw(25)<<it.unit2
                <<setw(10)<<fixed<<setprecision(2)<<it.link_cost
                <<setw(8)<<it.delay
                <<endl;
        }

        cout<<"--------------------------------------------------------------\n";
        cout<<"Optimized Cost  : "<<ts_cost<<endl;
        cout<<"Optimized Delay : "<<tp_delay<<" ns\n";

        if(!rejected.empty()){
            cout<<"\nRejected Links (Cycle Removal):\n";
            for(auto &it:rejected)
                cout<<it.unit1<<" <--> "<<it.unit2<<"  Cost:"<<it.link_cost<<endl;
        }

        double raw=0;
        for(auto &it:link) raw+=it.link_cost;

        cout<<"\nCost Saved: "<<raw-ts_cost<<endl;
    }

public:

    void architecture_menu(){
        while(true){
            cout<<"\n1)Create Links\n2)Optimize\n3)Exit\n";
            int choice;
            cin>>choice;
            if(choice==1) hardware_modelling();
            else if(choice==2) optimization_engine();
            else return;
        }
    }

    ~ecu_communication(){
        cout<<"Architecture session ended.\n";
    }
};

int main(){

    srand(time(nullptr));

    unique_ptr<ecu_communication> current_arch=nullptr;

    while(true){

        cout<<"\n1)Create New Architecture\n2)Copy Architecture\n3)Exit\n";
        int ch;
        cin>>ch;

        if(ch==1){
            current_arch=make_unique<ecu_communication>();
        }
        else if(ch==2){
            if(!current_arch){
                cout<<"No architecture to copy.\n";
            }else{
                ecu_communication copied(*current_arch);
            }
        }
        else{
            return 0;
        }
    }
}
