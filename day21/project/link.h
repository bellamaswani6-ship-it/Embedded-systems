#ifndef LINK_H
#define LINK_H

#include <string>
using namespace std;

struct communication_link {
    string unit1, unit2;
    double delay, link_cost;
};

#endif
