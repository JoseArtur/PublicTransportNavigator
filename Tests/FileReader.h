#ifndef FILEREADER_H
#define FILEREADER_H

#include "MainGraph.h"
#include <map>


class FileReader {

    multimap<pair<string,string>,int> linesConnections;

public:
    FileReader();
    /**
     * It receive a graph and insert all stops in it and in a unordered map as well,
     * we used this type of data class because it allows O(1) lookups
     * @param mapStops as an unordered_map that stores all stops and it ID
     * @param busline as an directed graph
     */
    void readStops(unordered_map<string, int> &mapStops, MainGraph &busline);

    /**
     *
     * @return
     */
    int calculateNumberOfStops();
    /**
     * It receive a empty vector and insert all lines in it and in a unordered map as well,
     * we used this type of data class because it allows O(1) lookups
     * @param lines
     * @param linesID
     */
    void readLines(vector<string> &lines, unordered_map<string, int> &linesID);

    /**
     *  This method is resposible  for the addition of all edges of the graph, it
     *  check if is a daily rote or a nightly one
     * @param line
     * @param file
     * @param busline
     * @param stopsID
     */
    void LinesEdgesControl(const string &line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID);
    void readPaths(MainGraph &busline, vector<string> &lines, unordered_map<string, int> &stopsID);
    static double haversine(Coordinates c1, Coordinates c2);
};

#endif
