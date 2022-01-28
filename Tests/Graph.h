#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include "disjointSets.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        string line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int distance;
        int parent;
        bool visited;

        string name;
        string zone;
        double latitude;
        double longitude;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;

    typedef pair<int,pair<int,double>> edgeInfo;
    vector<edgeInfo> edges; // {source, {destiny, weight} }
    static bool sortEdgesByWeight(edgeInfo e1, edgeInfo e2);

public:
    Graph(int nodes, bool dir = false);

    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude);
    void addEdge(int src, int dest, const string &line = "", double weight = 0);

    pair<double,double> getCoordinates(int node);

    void bfs(int v);

    int prim(int v);
    int kruskal();

    int size();

    void generatePossibleFeetPaths(double distance);

    void generatePossibleFeetPaths();
};

#endif
