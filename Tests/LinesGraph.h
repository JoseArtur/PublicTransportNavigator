#ifndef PROJETO2_LINESGRAPH_H
#define PROJETO2_LINESGRAPH_H

#include <list>
#include <vector>
#include <set>

using std::list;
using std::vector;
using std::set;

class LinesGraph {
    struct Edge{
        int dest; // Destination Line ID
        set<int> stop;
    };

    struct Node{
        list<Edge> adj; // Connections with others lines
        int distance;
        int pred;
        bool visited;
    };

    int n;
    vector<Node> nodes;

public:
    explicit LinesGraph(int nodes);
    void addEdge(int src, int dest, int byStop);

    int size() const;
    void resetTempNodes();

    vector<int> getPath(int src, int dest);

    set<int> getStopsThatConnects(int node, int dest);
};

#endif //PROJETO2_LINESGRAPH_H
