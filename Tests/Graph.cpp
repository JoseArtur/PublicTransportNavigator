#include <algorithm>
#include <queue>
#include "graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph::setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude) {
    nodes[id].name = name;
    nodes[id].zone = zone;
    nodes[id].latitude = latitude;
    nodes[id].longitude = longitude;
}

void Graph::addEdge(int src, int dest, const string& line, double weight) {
    if (src<0 || src>n-1 || dest<0 || dest>n-1){
        cout << "Can't add the edge." << endl;
        return;
    }
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
    edges.push_back({src, {dest, weight}});
}

int Graph::prim(int r) {
    for(int i = 1; i < nodes.size(); i++){
        nodes[i].distance = INT32_MAX;
        nodes[i].parent = -1;
    }
    nodes[r].distance = 0;

    MinHeap<int, int> heap(nodes.size(), -1);
    for(int i = 1; i < nodes.size(); i++)
        heap.insert(i, nodes[i].distance);

    while(heap.getSize() != 0){
        int close = heap.removeMin();
        for(auto edge : nodes[close].adj){
            if(heap.hasKey(edge.dest)
               && edge.weight < nodes[edge.dest].distance){
                nodes[edge.dest].parent = close;
                nodes[edge.dest].distance = edge.weight;
                heap.decreaseKey(edge.dest, edge.weight);
            }
        }
    }

    int result = 0;
    for(const auto &node : nodes){
        if(node.parent != -1)
            result += node.distance;
    }
    return result;
}

bool Graph::sortEdgesByWeight(edgeInfo e1, edgeInfo e2){
    return e1.second.second < e2.second.second;
}

int Graph::kruskal() {
    int result = 0;
    DisjointSets<int> sets;
    for(int i = 1; i < nodes.size(); i++)
        sets.makeSet(i);

    sort(edges.begin(), edges.end(), sortEdgesByWeight);

    for(const auto &edge : edges){
        if(sets.find(edge.first) != sets.find(edge.second.first)){
            result += edge.second.second;
            sets.unite(edge.first, edge.second.first);
        }
    }

    return result;
}

pair<double, double> Graph::getCoordinates(int node) {
    return {nodes[node].latitude, nodes[node].longitude};
}

int Graph::size() {
    return n;
}

void Graph::bfs(int v) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].distance = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}
