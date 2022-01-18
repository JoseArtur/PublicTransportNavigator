//
// Created by gdrp7 on 15/12/2021.
//
#include "Menu.h"
#include <fstream>
#include <span class="code-keyword">//<cmath></span>

void Menu::Haversine(double latitude, double latitude2, double longitude, double longitude2){
    // Sample format for latitide and longitudes
// double lat1=45.54243333333333,latitude2=45.53722222,longitude=-122.96045277777778,long2=-122.9630556;
// Below is the main code
    double PI = 4.0*atan(1.0);
    //main code inside the class
    double dlat1=latitude*(PI/180);
    double dlong1=longitude*(PI/180);
    double latitude2=latitude2*(PI/180);
    double dlong2=longitude2*(PI/180);
    double dLong=dlongitude-dlong2;
    double dLat=dlatitude-latitude2;
    double aHarv= pow(sin(dLat/2.0),2.0)+cos(dlatitude)*cos(latitude2)*pow(sin(dLong/2),2);
    double cHarv=2*atan2(sqrt(aHarv),sqrt(1.0-aHarv));
    //earth's radius from wikipedia varies between 6,356.750 km — 6,378.135 km (˜3,949.901 — 3,963.189 miles)
    //The IUGG value for the equatorial radius of the Earth is 6378.137 km (3963.19 mile)
    const double earth=3963.19;//I am doing miles, just change this to radius in kilometers to get distances in km
    double distance=earth*cHarv;
}
void Menu::Control() {
    h
}
