#include <algorithm>
#include "FileReader.h"
#include "fstream"
#include "Utilities.h"
#include "sstream"
#include <cmath>
#define DEBUG

int FileReader:: calculateNumberOfStops(){
    std::ifstream inFile("../dataset/stops.csv");
    return (int)std::count(std::istreambuf_iterator<char>(inFile),
                      std::istreambuf_iterator<char>(), '\n') - 1;
}

int FileReader::calculateNumberOfLines(){
    std::ifstream inFile("../dataset/lines.csv");
    return (int)std::count(std::istreambuf_iterator<char>(inFile),
                      std::istreambuf_iterator<char>(), '\n') - 1;
}

FileReader::FileReader() {
    int numberStops = calculateNumberOfStops();
    int numberLines = calculateNumberOfLines();

    #ifdef DEBUG
    cout << "Number of stops detected: " << numberStops << endl;
    cout << "Number of lines detected: " << numberLines << endl;
    #endif

   // mainGraph = new MainGraph(calculateNumberOfStops(), true);
    stopsID = new unordered_map<string, int>(numberStops);

   // linesGraph = new LinesGraph(numberLines);
    linesID = new unordered_map<string, int>(numberLines);
}

void FileReader::load() {
    loadMainGraph();
    loadLinesGraph();
    //calculatePossibleFeetPaths(.1); // 100 meters
}

void FileReader::loadMainGraph(){
//    readStops();
//    readLines();
   // readPaths();
}

void FileReader::loadLinesGraph() {
//    calculateLinesConnections();
}

void FileReader::readStops(unordered_map<string,int> & mapStops, MainGraph &busline){
    ifstream file("../dataset/stops.csv");
    if(!file.is_open()){
        cerr << "Stops file doesn't exists." << endl;
        return;
    }
    string fileContent;
    // Ignore first line
    getline(file, fileContent);
    int stopID = 0;
    while(getline(file, fileContent)){
        vector<string> info;
        istringstream reader(fileContent);
        string code, name, zone, latitude, longitude;
        getline(reader, code, ',');
        getline(reader, name, ',');
        getline(reader, zone, ',');
        getline(reader,latitude,',');
        getline(reader, longitude);
        info.push_back(code);info.push_back(name);info.push_back(zone);info.push_back(latitude);
        info.push_back(longitude);
        //mainGraph->setCoordinates(stopID, {static_cast<double>(stoi(latitude)), static_cast<double>(stoi(longitude))});
        mapStops.insert({code, stopID});
        busline.setInfo(stopID,info);
        stopID++;
    }
}

void FileReader::readLines(vector<string> &lines, unordered_map<string, int> &linesID) {
    ifstream file("../dataset/lines.csv");
    if(!file.is_open()){
        cerr << "Error: Lines file doesn't exists." << endl;
        return;
    }

    string fileContent;
    // Ignore first line
    getline(file, fileContent);

    int lineID = 0;
    while(getline(file, fileContent)){
        //cout << fileContent << endl;
        istringstream reader(fileContent);
        string code, name;

        getline(reader, code, ',');
        getline(reader, name);

        lines.push_back(code);

        //linesGraph->setLine(id, code);
        linesID.insert({code, lineID});
        lineID++;
    }
}

void FileReader::readPaths( MainGraph &busline, vector<string> &lines, unordered_map<string, int>& stopsID) {
    for(const string& it : lines){
        ifstream file0("../dataset/line_" + it + "_0.csv");
        ifstream file1("../dataset/line_" + it + "_1.csv");

        if(file0.is_open())
        {
            int num; file0 >> num;
            string source; file0 >> source;

            for(int i = 0; i < num - 1; i++){
                string dest; file0 >> dest;

                int sourceID = stopsID.at(source);
                int destID = stopsID.at(dest);

                auto pair1 = busline.getCoordinates(sourceID);
                auto pair2 = busline.getCoordinates(destID);

                busline.addEdge(sourceID,destID,it,haversine(pair1,pair2));
                source = dest;
            }



        }
        if(file1.is_open())
            readPath(it, file1,busline,stopsID);
    }
}
double FileReader::haversine(Coordinates c1, Coordinates c2) {
    double dLat = (c2.lat - c1.lat) * M_PI / 180.0;
    double dLon = (c2.lon - c1.lon) * M_PI / 180.0;

    c1.lat = (c1.lat) * M_PI / 180.0;
    c2.lat = (c2.lat) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(c1.lat) * cos(c2.lat);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
void FileReader::readPath(const string& line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID) {
    int num; file >> num;
    string source; file >> source;

    for(int i = 0; i < num - 1; i++){
        string dest; file >> dest;

        int sourceID = stopsID.at(source);
        int destID = stopsID.at(dest);

        auto pair1 = busline.getCoordinates(sourceID);
        auto pair2 = busline.getCoordinates(destID);

        busline.addEdge(sourceID,destID,line,haversine(pair1,pair2));

        source = dest;
    }
}

void FileReader::calculatePossibleFeetPaths(double distance) {
    int n = 0;
    for(int i = 0; i < mainGraph->size() - 1; i++){
        for(int j = i + 1; j < mainGraph->size(); j++){
            auto pair1 = mainGraph->getCoordinates(i);
            auto pair2 = mainGraph->getCoordinates(j);
            double d = Utilities::haversine(pair1,pair2);

            if(d <= distance){
                mainGraph->addEdge(i, j, "feet", d);
                n++;
            }
        }
    }

    #ifdef DEBUG
        cout << "Added " << n << " edges by feet." << endl;
    #endif
}

void FileReader::fillEdges(MainGraph graph) {

}

/*
void FileReader::calculateLinesConnections() {
    for(int i = 0; i < mainGraph->size(); i++){
        for(const auto& e1 : mainGraph->getEdges(i)){
            for(const auto& e2 : mainGraph->getEdges(e1.dest)){
                if(e1.line == e2.line) continue;
                if(e1.line == "feet" || e2.line == "feet") continue;
                if(e1.line == "11M" && e2.line == "901") {
                    cout << e1.dest << endl;
                }
                linesConnections.insert({{e1.line, e2.line}, e1.dest});
            }
        }
    }

    for(const auto& c : linesConnections)
     //   linesGraph->addEdge(linesID->at(c.first.first), linesID->at(c.first.second), c.second);
}

ReadData FileReader::getReadData() {
   // return {linesGraph, mainGraph, stopsID, linesID};
}
*/