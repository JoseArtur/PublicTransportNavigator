#ifndef PROJETO2_APPLICATION_H
#define PROJETO2_APPLICATION_H

#include <map>
#include <string>
#include "graph.h"
#include "MainGraph.h"
#include "FileReader.h"
using std::map;
using std::string;

class Application {

   // FileReader reader;
    //Data data;
public:
    Application();
    void start();

    void DisplayMenu(MainGraph &busLine);

    void DisplayOptions(MainGraph &busLine);

    void CoordinatesSelect();

    void StopSelect(unsigned int input, MainGraph& busLine);

    void CoordinatesSelect(unsigned int input, MainGraph& busLine);
    void generatePossibleFeetPaths();
    void SetDefaults(MainGraph &busLine);
};

#endif //PROJETO2_APPLICATION_H
