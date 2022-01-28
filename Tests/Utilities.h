#ifndef PROJETO2_UTILITIES_H
#define PROJETO2_UTILITIES_H

#include <list>
#include "MainGraph.h"

class Utilities {
public:
    static double haversine(Coordinates c1, Coordinates c2);
    static std::list<int> getCloseStops(MainGraph* graph, Coordinates c, double distance);
};

#endif //PROJETO2_UTILITIES_H
