#ifndef PROJETO2_APPLICATION_H
#define PROJETO2_APPLICATION_H

#include <map>
#include <string>
#include "MainGraph.h"
#include "FileReader.h"

class Application {
    unordered_map<string,int> mapStops, mapLines;
    MainGraph busLine;

public:
    Application(MainGraph busLine);
    void start();

    void DisplayMenu();

    void DisplayOptions();
    void StopSelect(unsigned int input );

    void CoordinatesSelect(unsigned int input);
    void SetDefaults();

    void WaysOptions();

    void LessRoteWay(unsigned int input);

    void LessStopsWay(unsigned int input);

    void CheapestWay(unsigned int input);

    void LessChangesWay(unsigned int input);
};

#endif //PROJETO2_APPLICATION_H
