#ifndef ECU_COMMUNICATION_H
#define ECU_COMMUNICATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <limits>

#include "vehicle.h"
#include "cable.h"
#include "graph.h"
#include "dsu.h"

using namespace std;

class ecu_communication : public Graph, public DSU {

    double a,b,c;
    double ts_cost = 0, tp_delay = 0;

    unordered_set<string> activeNodes;
    unordered_map<int,string> m;

    pair<double,double> cost_computation_engine();
    void hardware_modelling();
    void reset_mst();
    void optimization_engine();
    void run_dijkstra();
    void print_connected_components();
    int getIndex(const string&);

public:
    ecu_communication();
    ecu_communication(const ecu_communication&);
    void architecture_menu();
    void add_ecu();
    ~ecu_communication();
};

#endif
