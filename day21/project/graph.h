#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "link.h"
using namespace std;

class Graph {
protected:
    vector<communication_link> link;
    vector<communication_link> mst_link;
};

#endif
