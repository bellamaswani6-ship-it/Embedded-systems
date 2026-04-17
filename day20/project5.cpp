#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;

// ---------- COLORS ----------
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// ---------- STRUCTURES ----------
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

// =============================================================

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
        cout<<BLUE<<BOLD<<"\n=============================================\n";
        cout<<" ECU COMMUNICATION OPTIMIZATION SYSTEM\n";
        cout<<"=============================================\n"<<RESET;

        cout<<YELLOW<<"0) Economy  1) Luxury  2) Electric  3) Autonomous\n"<<RESET;

        int i;
        while(true){
            cout<<CYAN<<"Select vehicle type: "<<RESET;
            cin>>i;
            if(i>=0 && i<=3) break;
            cout<<RED<<"Invalid vehicle type!\n"<<RESET;
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
        cout<<YELLOW<<"\nCopying communication links to second model...\n"<<RESET;
        a=old.a; b=old.b; c=old.c;
        link=old.link;

        for(auto& [idx,name]:m){
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
        cout<<CYAN<<"Select cable type (0/1/2): "<<RESET;
        cin>>cabel_type;

        int current = cabel[cabel_type].current;
        double resistance = cabel[cabel_type].resistance;

        double power_loss = current * current * resistance;
        double link_cost = a*delay + b*power_loss + c*(distance*20);

        return {link_cost, delay};
    }

    void hardware_modelling() {
        cout<<BLUE<<BOLD<<"\nAvailable ECUs\n"<<RESET;
        cout<<"---------------------------------------------\n";

        for(auto& [i,name]:m)
            cout<<GREEN<<i<<RESET<<" : "<<name<<endl;

        while(true){
            int choice;
            cout<<YELLOW<<"\n1) Enter link  2) Exit : "<<RESET;
            cin>>choice;

            if(choice!=1) return;

            int i,j;
            cout<<CYAN<<"Enter two ECU numbers: "<<RESET;
            cin>>i>>j;

            if(m.find(i)==m.end() || m.find(j)==m.end()){
                cout<<RED<<"Invalid ECU index!\n"<<RESET;
                continue;
            }

            auto [cost,delay] = cost_computation_engine();
            link.push_back({m[i],m[j],delay,cost});
        }
    }

    void optimization_engine() {
        mst_link.clear();
        ts_cost = 0;
        tp_delay = 0;

        sort(link.begin(), link.end(),
            [](auto &a, auto &b){ return a.link_cost < b.link_cost; });

        cout<<BLUE<<BOLD<<"\n=============================================\n";
        cout<<" MINIMUM SPANNING TREE (KRUSKAL)\n";
        cout<<"=============================================\n"<<RESET;

        cout<<left
            <<setw(28)<<"ECU 1"
            <<setw(28)<<"ECU 2"
            <<setw(12)<<"Cost"
            <<"Delay\n";
        cout<<string(75,'-')<<endl;

        for(auto &it: link){
            if(find_parent(it.unit1) != find_parent(it.unit2)){
                union_set(it.unit1, it.unit2);
                mst_link.push_back(it);
                ts_cost += it.link_cost;
                tp_delay += it.delay;

                cout<<GREEN
                    <<setw(28)<<it.unit1
                    <<setw(28)<<it.unit2
                    <<setw(12)<<fixed<<setprecision(2)<<it.link_cost
                    <<it.delay<<" ns\n"<<RESET;
            }
        }

        cout<<string(75,'-')<<endl;
        cout<<CYAN<<"Total System Cost       : "<<ts_cost<<RESET<<endl;
        cout<<CYAN<<"Total Propagation Delay : "<<tp_delay<<" ns"<<RESET<<endl;
    }

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

    ~ecu_communication(){
        cout<<GREEN<<"\n✔ Communication optimization completed successfully\n"<<RESET;
    }
};

// =============================================================

int main(){
    srand(time(nullptr));

    ecu_communication ev;
    ev.hardware_init();
    ev.optimization_init();

    ecu_communication ev2 = ev;
    ev2.optimization_init();

    return 0;
}
