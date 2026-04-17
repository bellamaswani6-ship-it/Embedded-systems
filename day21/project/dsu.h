#ifndef DSU_H
#define DSU_H

#include <unordered_map>
#include <string>
using namespace std;

class DSU {
protected:
    unordered_map<string,string> parent;
    unordered_map<string,int> rank;

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
};

#endif
