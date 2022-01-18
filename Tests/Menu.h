//
// Created by gdrp7 on 15/12/2021.
//

#ifndef HEAD_MENU_H
#define HEAD_MENU_H

#include "luggage.h"
#include "plane.h"
#include "airport.h"
#include "Cart.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Menu {

public:
    void UseDefault();
    void Control(); // inputs data to files
    void DisplayMenu();
    void DisplayOptions();
    static void Help();
    void Haversine();


};

#endif //HEAD_MENU_H
