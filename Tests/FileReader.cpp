#include <algorithm>
#include "FileReader.h"
#include "fstream"
#include "sstream"
#include <cmath>

int FileReader:: calculateNumberOfStops(){
    std::ifstream inFile("../dataset/stops.csv");
    return (int)std::count(std::istreambuf_iterator<char>(inFile),
                      std::istreambuf_iterator<char>(), '\n') - 1;
}
FileReader::FileReader() {
}
void FileReader::readStops(unordered_map<string,int> & mapStops, MainGraph &busline){
    ifstream file("../dataset/stops.csv");
    if(!file.is_open()){
        cerr << "error." << endl;
        return;
    }
    string fileContent;
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
        mapStops.insert({code, stopID});
        busline.setInfo(stopID,info);
        stopID++;
    }
}

void FileReader::readLines(vector<string> &lines, unordered_map<string, int> &linesID) {
    ifstream file("../dataset/lines.csv");
    if(!file.is_open()){
        cerr << "Error: " << endl;
        return;
    }

    string fileContent;
    getline(file, fileContent);

    int lineID = 0;
    while(getline(file, fileContent)){
        istringstream reader(fileContent);
        string code, name;
        getline(reader, code, ',');
        getline(reader, name);
        lines.push_back(code);
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
            bool isDay = true;
            if(it.back() == 'M') // it is the line
            {isDay = false;}
            for(int i = 0; i < num - 1; i++){
                string dest; file0 >> dest;

                int sourceID = stopsID.at(source);
                int destID = stopsID.at(dest);
                auto pair1 = busline.getCoordinates(sourceID);
                auto pair2 = busline.getCoordinates(destID);
                busline.addEdge(sourceID,destID,it,haversine(pair1,pair2),isDay);
                source = dest;
            }
        }
        if(file1.is_open())
            readPath(it, file1,busline,stopsID);
    }
}

void FileReader::readPath(const string& line, ifstream &file, MainGraph &busline, unordered_map<string, int> stopsID) {
    int num; file >> num;
    string source; file >> source;
    bool isDay = true;
    if(line.back() == 'M')
        {isDay = false;}
    for(int i = 0; i < num - 1; i++){
        string dest; file >> dest;

        int sourceID = stopsID.at(source);
        int destID = stopsID.at(dest);

        auto pair1 = busline.getCoordinates(sourceID);
        auto pair2 = busline.getCoordinates(destID);

        busline.addEdge(sourceID,destID,line,haversine(pair1,pair2),isDay);

        source = dest;
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







