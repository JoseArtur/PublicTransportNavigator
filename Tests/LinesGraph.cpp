#include "LinesGraph.h"
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
/*
LinesGraph::LinesGraph(int num) {
    n = num;
    nodes = vector<Node>(num + 2);
}

void LinesGraph::addEdge(int src, int dest, int byStop) {
    if(src < 0 || src > n + 1 || dest < 0 || dest > n + 1){
        cout << "Can't add the edge." << endl;
        return;
    }

    if(src == 13 && dest == 6)
        cout << "";
    for(auto& e : nodes[src].adj){
        if(e.dest == dest){
            e.stop.insert(byStop);
            return;
        }
    }
    nodes[src].adj.push_back({dest, {byStop}});
}

int LinesGraph::size() const {
    return n;
}

void LinesGraph::bfs(int v) {
    for (int i = 0; i < n; i++){
        nodes[i].visited = false;
        nodes[i].distance = -1;
    }

    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                nodes[w].pred = u;
            }
        }
    }
}

vector<int> LinesGraph::getPath(int src, int dest) {
    bfs(src);

    vector<int> path;
    int node = nodes[dest].pred;
    while(node != src){
        path.insert(path.begin(), node);
        node = nodes[node].pred;
    }
    return path;
}

void LinesGraph::resetTempNodes() {
    nodes[n].adj.clear();
    nodes[n + 1].adj.clear();
}

set<int> LinesGraph::getStopsThatConnects(int node, int dest) {
    for(const auto& e : nodes[node].adj)
        if(e.dest == dest) return e.stop;
    return {};
}
*/