#ifndef _MAINGRAPH_H_
#define _MAINGRAPH_H_

#include "minHeap.h"
#include <vector>
#include <set>
#include <list>
#include <iostream>

using namespace std;

struct Coordinates{
    double lat;
    double lon;
};

struct Edge {
    int dest;   // Destination node
    double weight; // An integer weight
    string line;
    bool isDay;
};

class MainGraph {
    struct Node {
        string code;
        string adress;
        string zone;

        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double distance;
        int pred;
        string line;
        bool visited;
        set<string> arriveLines;
        set<string> departureLines;

        double latitude;
        double longitude;

    };
    int src,dest;
public:
    int getSrc() const;

    int getDest() const;

private:
    int n;
    bool hasDir;
    vector<Node> nodes;
    double distance = 0.3; // the default distance is 1 km
    bool day = true;
    void dijkstra(int s);
    void bfs(int s, const string &line);
    void bfs(int node);

    vector<pair<int,int>> tmpEdges;
public:
    MainGraph(int nodes, bool dir = false);
    void addEdge(int src, int dest, const string &line = "", double weight = 1,  bool isDay = true);
    void addEdge(int src, int dest, int byStop);

    void setCoordinates(int node, Coordinates c);
    Coordinates getCoordinates(int node);


    int size() const;

    list<int> getMinStopsPath(int src, int dest);
    list<int> getMinDistancePath(int src, int dest);

    list<int> getMinStopsPath(int src, int dest, const string &line);

    string getLine(int id);
    set<string> getArriveLines(int id);
    set<string> getDepartureLines(int id);

    list<Edge> getEdges(int node);

    void clearAuxEdges();
    int addAuxDestinations(const set<int>& dests, const string& line);
    void resetTempNodes();

    vector<int> getPath(int src, int dest);

    set<int> getStopsThatConnects(int node, int dest);
    void setInfo(int idStop, vector<string> info);

    void setDistance(double i);

    void generatePossibleFeetPaths();

    void localByCoordinates(double x, double y);

    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude, string code);

    void addCoordinatesEdge(int v);

    double dijkstra_distance(int a, int b);

    void setTime(int i);

    void destByCoordinates(double x, double y);

    void localByName(string basicString);
};

#endif
