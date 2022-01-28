#ifndef PROJETO2_FILEREADER_H
#define PROJETO2_FILEREADER_H

#include "MainGraph.h"
//#include "LinesGraph.h"
#include <map>

struct ReadData{
  //  LinesGraph* linesGraph;
    MainGraph* mainGraph;

    unordered_map<string, int>* stopsID;
    unordered_map<string, int>* linesID;
};

class FileReader {
   // LinesGraph* linesGraph;
    MainGraph* mainGraph;

    unordered_map<string, int>* stopsID;
    unordered_map<string, int>* linesID;

    // Aux
  //  vector<string> lines;
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

  //  ReadData getReadData();

    void readStops(unordered_map<string, int> &mapStops, MainGraph &busline);

    void fillEdges(MainGraph graph);
    //void readPath(const string &line, ifstream &file, MainGraph& g1);


    vector<string> getLine();

    int calculateNumberOfStops();


   // void readPaths(MainGraph &busline);

    void readLines(vector<string> &lines);

    void readLines(vector<string> &lines, unordered_map<string, int> &linesID);

    //void readPaths(MainGraph &busline, vector<string> &lines);

    int calculateNumberOfLines();

   // void readPaths();

  //  void readPaths(MainGraph &busline, vector<string> lines);
    void readPath(const string &line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID);

    void readPaths(MainGraph &busline, vector<string> &lines, unordered_map<string, int> &stopsID);

    static double haversine(Coordinates c1, Coordinates c2);
};

#endif //PROJETO2_FILEREADER_H
