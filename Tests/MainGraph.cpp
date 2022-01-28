#include <queue>
#include "MainGraph.h"
#include "FileReader.h"
#define INF 1241412421414.5

MainGraph::MainGraph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 2) {}

int MainGraph::size() const { return n; }

void MainGraph::addEdge(int src, int dest, const string& line, double weight) {
    if (src < 0 || src >= n + 2 || dest < 0 || dest >= n + 2){
        cout << "Can't add the edge." << endl;
        return;
    }
    nodes[src].adj.push_back({dest, weight, line});
    if(line != "feet"){
        nodes[src].departureLines.insert(line);
        nodes[dest].arriveLines.insert(line);
    }
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

void MainGraph::setCoordinates(int node, Coordinates c) {
    nodes[node].latitude = c.lat;
    nodes[node].longitude = c.lon;
}

Coordinates MainGraph::getCoordinates(int node) {
    return {nodes[node].latitude, nodes[node].longitude};
}

string MainGraph::getLine(int id) {
    return nodes[id].line;
}

list<int> MainGraph::getMinDistancePath(int a, int b) {
    dijkstra(a);
    if (nodes[b].distance == INF) return {};

    list<int> path;
    if (nodes[b].distance == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

void MainGraph::dijkstra(int s) {
    MinHeap<int, double> q(n, -1);
    for (int v = 0; v < n; v++) {
        nodes[v].distance = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].distance = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;

    while (q.getSize()>0) {
        int u = q.removeMin();
        //cout << "Node " << u << " with dist = " << nodes[u].distance << endl;
        nodes[u].visited = true;

        for (const auto &e : nodes[u].adj) {
            if(e.line == "feet") continue;
            int v = e.dest;
            double w = e.weight;
            if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].pred = u;
                nodes[v].line = e.line;
            }
        }
    }
}

void MainGraph::bfs(int v) {
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
                nodes[w].line = e.line;
            }
        }
    }
}

list<int> MainGraph::getMinStopsPath(int src, int dest) {
    bfs(src);

    list<int> path;
    int node = dest;
    while(node != src){
        path.push_front(node);
        node = nodes[node].pred;
    }
    path.push_front(src);
    return path;
}

list<Edge> MainGraph::getEdges(int node) {
    return nodes[node].adj;
}

set<string> MainGraph::getArriveLines(int id) {
    return nodes[id].arriveLines;
}

set<string> MainGraph::getDepartureLines(int id) {
    return nodes[id].departureLines;
}

list<int> MainGraph::getMinStopsPath(int src, int dest, const string &line) {
    bfs(src, line);
    if(nodes[dest].distance == -1 || nodes[dest].pred == -1) return {};

    list<int> path;
    int node = dest;
    while(node != src){
        path.push_front(node);
        node = nodes[node].pred;
        if(node == -1) return {};
    }
    path.push_front(src);
    return path;
}

void MainGraph::bfs(int v, const string &line) {
    for (int i = 0; i < n + 2; i++){
        nodes[i].visited = false;
        nodes[i].distance = -1;
        nodes[i].pred = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        if(u == 99)
            cout << "";
        //cout << u << " "; // show node order
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if(w == 2488)
                cout << "";
            if (!nodes[w].visited && e.line == line) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                nodes[w].pred = u;
                nodes[w].line = e.line;
            }
        }
    }
}

void MainGraph::clearAuxEdges() {
    nodes[n].adj.clear();

    for(const auto& pair : tmpEdges){
        if(pair.first == 868 && pair.second == 2488)
            cout << "";
        auto l = nodes[pair.first].adj;
        for(auto i = l.begin(); i != l.end(); i++){
            if((*i).dest == pair.second){
                l.erase(i);
                break;
            }
        }
    }
    tmpEdges.clear();
}

int MainGraph::addAuxDestinations(const set<int> &dests, const string& line) {
    for(const auto& dest : dests){
        if(dest == 868)
            cout << "";
        tmpEdges.push_back({dest, n + 1});
        addEdge(dest, n + 1, line);
    }
    return n + 1;
}
void MainGraph::setInfo(int idStop, vector<string> info){
    nodes[idStop].code = info[0];
    nodes[idStop].adress = info[1];
    nodes[idStop].zone = info[2];
    nodes[idStop].latitude = stod(info[3]);
    nodes[idStop].longitude = stod(info[4]);
}
void  MainGraph::setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude, string code) {
    nodes[id].adress = name;
    nodes[id].zone = zone;
    nodes[id].latitude = latitude;
    nodes[id].longitude = longitude;
    nodes[id].code = code;
}

void MainGraph::setDistance(int i) {

}
void MainGraph::generatePossibleFeetPaths()
{int distance = 4;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            auto pair1 = getCoordinates(i);
            auto pair2 = getCoordinates(j);
            double d = FileReader::haversine(
                    pair1,pair2);

            if(d <= distance)
                addEdge(i, j, "feet", d);
        }
    }
}
void MainGraph::localByCoordinates(double x, double y, double distance) {

    int src = n - 2;
    vector<string> a;
    setNodeInfo(src,"initial"," ",x,y,"INIT");
    addCoordinatesEdge(src,distance);
    /*for(auto a: nodes[src].adj)
    {
        cout << a.dest << " " << a.line << nodes[a.dest].name << endl;
    }*/
    generatePossibleFeetPaths();
}
void MainGraph::addCoordinatesEdge(int v, double distance)
{
    auto pair1 = getCoordinates(v);
    for(int i = 0; i < n -1; i++)
    {
        auto pair2 = getCoordinates(i);
        double d = FileReader::haversine(
                pair1,pair2);
        if(d <= distance && v != i)
        {
            addEdge(i, v, "feet", d);
            addEdge(v, i, "feet", d);
        }
    }
}