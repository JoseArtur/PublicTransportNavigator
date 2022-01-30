#include <queue>
#include "MainGraph.h"
#include "FileReader.h"
#include <set>
#include <algorithm>
#include "disjointSets.h"
#define INF INT_MAX / 2

MainGraph::MainGraph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 2) {}

int MainGraph::size() const { return n; }

void MainGraph::addEdge(int src, int dest, const string& line, double weight, bool isDay) {
    if (src < 0 || src >= n + 2 || dest < 0 || dest >= n + 2){
        cout << "error." << endl;
        return;
    }
    nodes[src].adj.push_back({dest, weight, line, isDay});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
    edges.push_back({weight, {src, dest}});
}


Coordinates MainGraph::getCoordinates(int node) {
    return {nodes[node].latitude, nodes[node].longitude};
}


list<int> MainGraph::getMinDistancePath(int a , int b ) {
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
    double oldDistance = 0;
   result(path,b);
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
        nodes[u].visited = true;

        for (const auto &e : nodes[u].adj) {
            if((day && e.isDay) || (!day && !e.isDay) ){
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
}
void MainGraph::dijkstraByZone(int s) {
    MinHeap<int, double> q(n, -1);
    for (int v = 0; v < n; v++) {
        nodes[v].distance = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].distance = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    set<string> zones, EMPTY;
    zones = EMPTY;
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        set<string> zones, EMPTY;
        zones = EMPTY;
        for (const auto &e : nodes[u].adj) {
            if((day && e.isDay) || (!day && !e.isDay) ){
                //zones.insert(nodes[u].zone);
                zones.erase("");
                zones.erase(" ");
                int v = e.dest;
                string testA = nodes[v].zone;
                string testB = nodes[u].zone;
                zones.erase("");
                zones.erase(" ");
                int w;
                if(nodes[u].zone == nodes[v].zone || nodes[u].zone == " "){
                    w = 0;
                }else w =1;

                if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                    nodes[v].distance = nodes[u].distance + w;
                    q.decreaseKey(v, nodes[v].distance);
                    nodes[v].pred = u;
                    nodes[v].line = e.line;
                }
            }
        }
    }
}
void MainGraph::dijkstraByLine(int s) {
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
        nodes[u].visited = true;
        set<string> lines, EMPTY;
        lines = EMPTY;
        lines.insert(nodes[u].line);
        for (const auto &e : nodes[u].adj) {
            if((day && e.isDay) || (!day && !e.isDay) ){

                lines.insert(nodes[u].line);
                lines.erase("");
                lines.erase(" ");
                int v = e.dest;
                int w = lines.size();
                if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                    nodes[v].distance = nodes[u].distance + w;
                    q.decreaseKey(v, nodes[v].distance);
                    nodes[v].pred = u;
                    nodes[v].line = e.line;
                }
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
        for (const auto& e : nodes[u].adj) {
            if((day && e.isDay) || (!day && !e.isDay) ){

                int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                nodes[w].pred = u;
                nodes[w].line = e.line;
            }}
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
   result(path,dest);
    return path;
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

void MainGraph::setDistance(double i) {
        distance = i;
}
void MainGraph::generatePossibleFeetPaths()
{
    for(int i = 0; i < n ; i++){
        for(int j = i + 1; j < n; j++){
            auto pair1 = getCoordinates(i);
            auto pair2 = getCoordinates(j);
            double d = FileReader::haversine(
                    pair1,pair2);

            if(d <= distance)
                addEdge(i, j, "walk", d,day);
        }
    }
}
void MainGraph::localByCoordinates(double x, double y) {
     src = n - 2;
    vector<string> a;
    setNodeInfo(src,"Start Position"," ",x,y,"START");
    addCoordinatesEdge(src);
    generatePossibleFeetPaths();
}
void MainGraph::destByCoordinates(double x, double y) {
    dest = n - 1;
    setNodeInfo(dest,"Final Position"," ",x,y,"END");
    addCoordinatesEdge(dest);
}

void MainGraph::addCoordinatesEdge(int v)
{
    auto pair1 = getCoordinates(v);
    for(int i = 0; i < n ; i++)
    {
        auto pair2 = getCoordinates(i);
        double d = FileReader::haversine(
                pair1,pair2);
        if(d <= distance && v != i)
        {
            addEdge(i, v, "walk", d, day);
            addEdge(v, i, "walk", d, day);
        }
    }
}
double MainGraph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].distance == INF) return -1;
    auto f= nodes[b].adress;
    return nodes[b].distance;

}

void MainGraph::setTime(int i) {
    if(i>0 && i<4) day = false;
}


int MainGraph::getSrc() const {

    return src;
}

int MainGraph::getDest() const {
    return dest;
}

void MainGraph::localByName(int id) {

    src = n - 2;
    Coordinates c1 = getCoordinates(id);
    vector<string> a;
    setNodeInfo(src,"ORIGIN"," ",c1.lat,c1.lon,"ORIG");
    addCoordinatesEdge(src);
    generatePossibleFeetPaths();
}
void MainGraph::destinationByName(int id) {
    dest = n - 1;
    Coordinates c1 = getCoordinates(id);
    setNodeInfo(dest,"destination"," ",c1.lat,c1.lon,"DEST");
    addCoordinatesEdge(dest);
}
 bool MainGraph::sortByWeight(pair<int, pair<int, int>> e1, pair<int, pair<int, int>> e2){
    return e1.first < e2.first;
}
int MainGraph::kruskal(){
    int T = 0;
    DisjointSets<int> sets;
    set<int> parades;
    set<int> ends;
    for(int i = 1; i < nodes.size(); i++)
        sets.makeSet(i);
    sort(edges.begin(),edges.end(), sortByWeight);
    for(auto edge:edges) {
        if (sets.find(edge.second.first) != sets.find(edge.second.second) && (parades.find(edge.second.first) == parades.end()) && (ends.find(edge.second.second) == ends.end())) {
            parades.insert(edge.second.first);
            ends.insert(edge.second.second);
            auto iter = std::find_if(std::begin(mapStops), std::end(mapStops),[& edge](auto &&pair) { return pair.second == edge.second.first; });
            string source = iter->first;
            auto iter2 = std::find_if(std::begin(mapStops), std::end(mapStops),[& edge](auto &&pair) { return pair.second == edge.second.second; });
            string dest = iter2 -> first;
             cout <<source << " - " << dest << endl;
            T = T + edge.first;
            sets.unite(edge.second.first, edge.second.second);
        }
    }
    return T;
}

void MainGraph::setMapStops(const unordered_map<string, int> &mapStops) {
    MainGraph::mapStops = mapStops;
}


list<int> MainGraph::getCheapest(int a , int b ) {
    dijkstraByZone(a);

    if (nodes[b].distance == INF) return {};

    list<int> path;
    if (nodes[b].distance == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
   result(path,b);
    return path;
}

list<int> MainGraph::getMinLines(int a , int b ) {
    dijkstraByLine(a);

    if (nodes[b].distance == INF) return {};

    list<int> path;
    if (nodes[b].distance == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
  result(path,b);
    return path;
}

string MainGraph::getZone(int node) {
    return nodes[node].zone;
}

string MainGraph::getLineOfEdge(int node) {
    return nodes[node].line;
}
void MainGraph::result(list<int> path,int dest){
    set<string> zones; // In here all zones will be added
    set<string> lines;
    double oldDistance= 0;
    for(auto e:path){
        zones.insert(nodes[e].zone);
        lines.insert(nodes[e].line);
        if(nodes[e].code != "ORIG"){
        cout<<"|CODE: "<<nodes[e].code<<" |NAME: "
        <<nodes[e].adress<<
        " |DISTANCE: "<<nodes[e].distance;

        if(nodes[e].line == "walk") {
            double walked = 0;
            if(nodes[e].distance != 0)
            {
                walked = nodes[e].distance - oldDistance;
                cout<<"||"<<" "<< walked * 1000<<" METERS to walk"<<endl;}
            else cout<<endl;
        }
        else cout<< " |LINE: "<<nodes[e].line<<" "<<nodes[e].zone<<endl;
        oldDistance = nodes[e].distance;
    }
    }
    zones.erase("");
    zones.erase(" ");
    lines.erase("");
    lines.erase(" ");
    cout<<"You are passing through "<<zones.size()<<" zones"<<endl;
    cout<<"You are passing through "<<lines.size()<<" LINES"<<endl;
    cout<<"The total distance is "<<nodes[dest].distance<<endl;

}
