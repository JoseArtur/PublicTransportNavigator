#include "Utilities.h"
#include <cmath>

double Utilities::haversine(Coordinates c1, Coordinates c2) {
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

std::list<int> Utilities::getCloseStops(MainGraph *graph, Coordinates c, double distance) {
    list<int> result;
    for(int i = 0; i < graph->size() - 1; i++){
        auto coord = graph->getCoordinates(i);
        double d = Utilities::haversine(coord,c);

        if(d <= distance) result.push_back(i);
    }
    return result;
}
