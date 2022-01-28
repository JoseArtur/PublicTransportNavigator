#ifndef PROJETO2_FILEREADER_H
#define PROJETO2_FILEREADER_H

#include "MainGraph.h"
//#include "LinesGraph.h"
#include <map>


class FileReader {

    multimap<pair<string,string>,int> linesConnections;

    void readStops();
    void readStop(const string& line, int id);
    void readLines();
    void readLine(const string& line, int id);

    void readPath(const string& line, ifstream &file);
    void calculatePossibleFeetPaths(double distance);
    void calculateLinesConnections();

    void loadMainGraph();
    void loadLinesGraph();
public:
    FileReader();
    void load();
    void readStops(unordered_map<string, int> &mapStops, MainGraph &busline);
    void fillEdges(MainGraph graph);
    vector<string> getLine();
    int calculateNumberOfStops();
    void readLines(vector<string> &lines);
    void readLines(vector<string> &lines, unordered_map<string, int> &linesID);
    int calculateNumberOfLines();
    void readPath(const string &line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID);
    void readPaths(MainGraph &busline, vector<string> &lines, unordered_map<string, int> &stopsID);
    static double haversine(Coordinates c1, Coordinates c2);
};

#endif //PROJETO2_FILEREADER_H
