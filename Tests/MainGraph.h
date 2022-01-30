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
    unordered_map<string,int> mapStops, mapLines;
public:
    void setMapStops(const unordered_map<string, int> &mapStops);

private:

    vector< pair<int, pair<int, int>> > edges;

    struct Node {
        string code;
        string adress;
        string zone;
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double distance;
        int pred;
        string line;
        bool visited;
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

     /**
    * This is an dijkstra algorithm s,
     * the weight is the distance
     * It calculate the best path wit less distance
     * Time Complexity : O (E * log(V)),  where E is the edge's number and V the node's number.
     * @param s as Node's number
      */
    void dijkstra(int s);

    /** This is the implementation of BFS ( Breadth First Search ), which is suitable to find the
     * shortest path in a graph. It uses an adjacent list
     *Time Complexity : O(V + E), wher V is the node's number and E is the edge's number
     * @param node as node's number
     */
    void bfs(int node);
public:
    MainGraph(int nodes, bool dir = false);

    void addEdge(int src, int dest, const string &line = "", double weight = 1,  bool isDay = true);


    Coordinates getCoordinates(int node);
    int size() const;

    /** by receiving a vector with informations about a stop, it sets the node with the idStop number
     * with the informations in info
     * @param idStop as the node number/id
     * @param info as a vector of informations about this node
     */
    void setInfo(int idStop, vector<string> info);


    /**
     * It adds all possible walk options in the range pre-established by the user or the default one
     * already defaulted which is 0.3 km = 300 meters
     * Time Complexity : O ( n^2 ), where n is the number of edges
     */
    void WalkPossibleRotes();

    /**
     * It sets the user location using given coordinates by creating a node that represent the initial location
     * @param x as latitude
     * @param y as longitude
     */
    void localByCoordinates(double x, double y);

    /** by receiving  information about a stop, it sets the node, that has the given id number
    * with the information in (name,zone,latitude,longitude,code)
    * @param id
    * @param name
    * @param zone
    * @param latitude
    * @param longitude
    * @param code
    */
    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude, string code);

    /**
     * It adds all possible edges in the range of the pre-established distance
     * @param v as the number of the edge
     */
    void addCoordinatesEdge(int v);

    /**
     *  It uses the classic dijkstra to find the best path with minimum distance between node a and node b
     *
     * @param a as number of the source node
     * @param b as number of the destination node
     * @return the total distance in this path or -1 if it isn't possible to reach the second node from the first
     */
    double dijkstra_distance(int a, int b);

    void setTime(int i);

    void destByCoordinates(double x, double y);

    /**
     * It sets the user location, using the number of the stop,
     * by creating a node that represent the initial location
     * @param basicString as ID/number of the stop
     */
    void localByName(int stopID);

    /**
     * It sets the user destination, using the number of the stop,
     * by creating a node that represent the initial location
     * @param stopID as ID/number of the stop
     */
    void destinationByName(int stopID);

    /**
     * This is the implementation of the kruskal's algorithm, where we generates a MST for this graph,
     * but is good to know that it only works property with undirected graphs
     * Time Complexity : O (E * log(V)), where E is the edge's number and V the node's number.
     * @return the total cost of the MST
     */
    int kruskal();


    static bool sortByWeight(pair<int, pair<int, int>> e1, pair<int, pair<int, int>> e2);

    /**
     * This is an dijkstra algorithm slight different, because in this one,
     * the weight isn't the distance but the different zones.
     * It calculate the best path with fewer zones
     * Time Complexity : O (E * log(V)),  where E is the edge's number and V the node's number.
     * @param s as Node's number
     */
    void dijkstraByZone(int s);
    void setDistance(double i);

    string getZone(int node);

    /**
     * It use the  dijkstra by zones, to find the best path
     * between two nodes with fewer zones passed
     * @param a as number of source node
     * @param b as number of destination node
     * @return a list with the complete path between this two nodes
     */
    list<int> getCheapest(int a, int b);

    /**
      * It use the  bfs, to find the best path
      * between two nodes with fewer stops passed
      * @param src as number of source node
      * @param dest as number of destination node
      * @return a list with the complete path between this two nodes
      */
    list<int> getMinStopsPath(int src, int dest);

    /**
        * It use the classic dijkstra,to find the best path
        * between two nodes with fewer distance
        * @param src as number of source node
        * @param dest as number of destination node
        * @return a list with the complete path between this two nodes
        */
    list<int> getMinDistancePath(int src, int dest);

    /**
     * This is an dijkstra algorithm slight different, because in this one,
     * the weight isn't the distance but the different lines.
     * It calculate the best path with fewer lines taken
     * Time Complexity : O (E * log(V)),  where E is the edge's number and V the node's number.
     * @param s as Node's number
     */
    void dijkstraByLine(int s);


    /**
    * It use the adaptation of the dijkstra, named dijikstra by line,to find the best path
    * between two nodes with fewer lines
    * @param a as source's node number/id
    * @param b as destination's node number/id
    * @return a list with the path of all nodes.
    */
    list<int> getMinLines(int a, int b);

    /**
     * It is resposible for display the infos about a path in the console
     * @param path as the list of all nodes in a path
     * @param dest as the destination number
     */
    void result(list<int> path, int dest);
};

#endif
