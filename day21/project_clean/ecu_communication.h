#ifndef ECU_COMMUNICATION_H
#define ECU_COMMUNICATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include <limits>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "vehicle.h"
#include "cable.h"

using namespace std;

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

    // PRIVATE HELPERS
    pair<double,double> cost_computation_engine();
    void hardware_modelling();
    void print_connected_components();
    void reset_mst();
    void optimization_engine();
    string find_parent(string x);
    void union_set(string a,string b);
    int getIndex(const string &s);
    void run_dijkstra();
    void add_ecu();
    void architecture_menu();

public:
    ecu_communication();
    ecu_communication(const ecu_communication& old);
    ~ecu_communication();

    void run();   
};

#endif
