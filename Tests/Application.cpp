#include <fstream>
#include <algorithm>
#include "Application.h"


using namespace std;


void Application::start() {

    FileReader reader;
    busLine = MainGraph(reader.calculateNumberOfStops()+2,true);

    //  busLine((reader.calculateNumberOfStops()+2),true);
     reader.readStops(mapStops,busLine);
     vector<string> lines;
    // busLine.addEdge(125,1462,"1",0.4);
     reader.readLines(lines,mapLines);
     reader.readPaths(busLine,lines,mapStops);
    list<int> lib;
     double a ;
     //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  //   busLine.localByCoordinates(41.180548, -8.594938);
  // busLine.destByCoordinates(41.172245, -8.597604);
  // busLine.getMinDistancePath(busLine.getSrc(),busLine.getDest());
    //a = busLine.dijkstra_distance(busLine.getSrc(),busLine.getDest());
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
   // busLine.localByName(913);
   // busLine.destinationByName(910);
  //  busLine.getMinDistancePath(busLine.getSrc(),busLine.getDest());
   DisplayMenu();

}
void Application::DisplayMenu() {
    unsigned int input;
    do {
        cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
                "\n1) - Show Options"
                "\n2) - Help"
                "\n3) - Set Default"
                "\n0) - Exit"
                "\n\nChoose an option: ";
        cin >> input;
        cin.clear(); cin.ignore(1000, '\n');
        switch (input) {
          //  case 0: Control();
            case 1: DisplayOptions(); break;
          //  case 2: Help(); break;
            case 3: SetDefaults( ); break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}


void Application::DisplayOptions() {
    unsigned int input;
    do {
        cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
                "FIRST TELL ME IF YOU WANT TO USE YOUR COORDINATES OR USE A EXISTING STOP"
                "\n1) SET SOURCE COORDINATES"
                "\n2) SET DESTINATION COORDINATES"
                "\n3) SET SOURCE STOP"
                "\n4) SET DESTINATION STOP"
                "\n5) SELECT THE WAY"
                "\n0) - Back"
                "\n\nChoose an option: ";
        cin >> input;
        cin.clear(); cin.ignore(1000, '\n');
        switch (input) {
            case 0: break;
            case 1: CoordinatesSelect(input); break;
            case 2:CoordinatesSelect(input);break;
            case 3: StopSelect(input); break;
            case 4:StopSelect(input); break;
            case 5: WaysOptions();break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}

void Application::CoordinatesSelect(unsigned int input) {
    cout << "give the coordinates (x y) : "<<endl;
    double latitude,longitude;
    cin >> latitude;
    cin>> longitude;
    cout << endl;

    if(input ==1)busLine.localByCoordinates(latitude,longitude);
    if(input == 2) busLine.destByCoordinates(latitude,longitude);
    } //in case user puts a coordinate x,y


void Application::StopSelect(unsigned int input) {
    cout<< "insert the name of the stop: " <<endl;
    string name;
    cin>>name;
    int id;
    std::unordered_map<std::string,int>::const_iterator got = mapStops.find (name);
    if ( got == mapStops.end() ) return;
    else{ id = got->second;
    cout<<id;}
    if(input == 3) busLine.localByName(id);
    if(input == 4) busLine.destinationByName(id);
}

// EM desenvolvimento, teoricamente isso serve pra botar a distancia maxima que a pessoa quer andar e se ela ta indo de noite ou de dia
void Application::SetDefaults() {
    int time;
    double distance;
    cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
            "WELCOME TO THE DEFAULT CONFIGURATION SYSTEM"
            "\n First I want to know your maximum range of meters that you are willing to walk between two stops"
            "\n Insert in meters";
            cin>>distance;
            busLine.setDistance(distance);
    cout<<"\n Thank you, now I would like to know the hour of your trip";
    cin>>time;
    busLine.setTime(time);
            "\n\nChoose an option: ";
        cout<<"WELCOME TO THE DEFAULT CONFIGURATION SYSTEM";

}

Application::Application(MainGraph busLine) : busLine(busLine) {

}

void Application::WaysOptions() {
    unsigned int input;
    do {
        cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
                "\n1) LESS ROTES WAY"
                "\n2) LESS STOPS WAY"
                "\n3) CHEAPEST WAY"
                "\n4) LESS CHANGES BETWEEN BUSES"
                "\n0) - Back"
                "\n\nChoose an option: ";
        cin >> input;
        cin.clear(); cin.ignore(1000, '\n');
        switch (input) {
            case 0: break;
            case 1: LessRoteWay(input); break;
            case 2:LessStopsWay(input);break;
            case 3: CheapestWay(input); break;
            case 4:LessChangesWay(input); break;
            case 5: WaysOptions();break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}

void Application::LessRoteWay(unsigned int input) {
    busLine.getMinDistancePath(busLine.getSrc(),busLine.getDest());
    double distance;
    distance =  busLine.dijkstra_distance(busLine.getSrc(),busLine.getDest());
    cout<<distance;
}

void Application::LessStopsWay(unsigned int input) {
    busLine.getMinStopsPath(busLine.getSrc(),busLine.getDest());
}

void Application::CheapestWay(unsigned int input) {

}

void Application::LessChangesWay(unsigned int input) {

}
