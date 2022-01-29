#ifndef PROJETO2_FILEREADER_H
#define PROJETO2_FILEREADER_H

#include "MainGraph.h"
#include <map>


class FileReader {

    multimap<pair<string,string>,int> linesConnections;

public:
    FileReader();
    void readStops(unordered_map<string, int> &mapStops, MainGraph &busline);
    int calculateNumberOfStops();
    void readLines(vector<string> &lines, unordered_map<string, int> &linesID);
    void readPath(const string &line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID);
    void readPaths(MainGraph &busline, vector<string> &lines, unordered_map<string, int> &stopsID);
    static double haversine(Coordinates c1, Coordinates c2);
};

#endif //PROJETO2_FILEREADER_H
