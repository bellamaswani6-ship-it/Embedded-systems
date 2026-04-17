#ifndef CABLE_H
#define CABLE_H

struct cable_type {
    int current;
    double resistance;
    double cost;
};

extern cable_type cabel[3];

#endif
