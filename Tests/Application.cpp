#include <fstream>
#include <algorithm>
#include "Application.h"
#include "FileReader.h"
#include "MainGraph.h"


using namespace std;
Application::Application()  {
  //  reader.load();

  //  data = Data(reader.getReadData());
}
/*int calculateNumberOfStops(){
    std::ifstream inFile("../dataset/stops.csv");
    return (int)std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n') - 1;
}*/
void Application::start() {
    FileReader reader;
    unordered_map<string, int>* linesID;
    linesID = new unordered_map<string, int> (reader.calculateNumberOfLines());
    unordered_map<string, int>* stopsID;
    stopsID = new unordered_map<string, int> (reader.calculateNumberOfStops());

    MainGraph busLine((reader.calculateNumberOfStops()),true);
    unordered_map<string,int> mapStops, mapLines;
     reader.readStops(mapStops,busLine);
     vector<string> lines;
    // busLine.addEdge(125,1462,"1",0.4);
     reader.readLines(lines,mapLines);
     reader.readPaths(busLine,lines,mapStops);
     cout<<"hello";
   //  for(auto e:mapStops) cout<<e.first<<endl;
    //testMinDistance({41.18302268191288, -8.601038341104502}, {41.16762022369338, -8.617084201223456});

    //testMinDistance(data.getStopsIndex()->at("HSJ5"), data.getStopsIndex()->at("SVP1"));
    //testMinStops(data.getStopsIndex()->at("VIS3"), data.getStopsIndex()->at("PRG2"));

    //data.performAction("HSJ5", "SVP1", ACTION::MinDistance);
    //data.performAction("VIS3", "PRG2", ACTION::MinLines);
    //data.performAction("HSJ5", "PRG2", ACTION::MinLines);
    //data.performAction("HSJ5", "CM3", ACTION::MinLines);
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
            case 3: SetDefaults(); break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}


void Application::DisplayOptions() {
    unsigned int input;
    do {
        cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
                "FIRST TELL ME IF YOU WANT TO USE YOUR COORDINATES OR USE A EXISTING STOP"
                "\n1) COORDINATES"
                "\n2) EXISTING STOP"
                "\n0) - Back"
                "\n\nChoose an option: ";
        cin >> input;
        cin.clear(); cin.ignore(1000, '\n');
        switch (input) {
            case 0: break;
            case 1: CoordinatesSelect(input); break;
            case 2: StopSelect(input); break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}

void Application::CoordinatesSelect(unsigned int input, MainGraph& busLine) {
    cout << "give the coordinates (x y) : ";
    double latitude,longitude;
    cin >> latitude;
    cin>> longitude;
    cout << endl;

        busLine.localByCoordinates(latitude,longitude);
    } //in case user puts a coordinate x,y


void Application::StopSelect(unsigned int input) {

}

/* EM desenvolvimento, teoricamente isso serve pra botar a distancia maxima que a pessoa quer andar e se ela ta indo de noite ou de dia
void Application::SetDefaults(MainGraph &busLine) {
    int distance,time;
    cout << "\n*** TRANSPORT MANAGEMENT SYSTEM *** \n"
            "WELCOME TO THE DEFAULT CONFIGURATION SYSTEM"
            "\n First I want to know your maximum range of meters that you are willing to walk between two stops"
            "\n Insert in meters";
            cin>>distance;
            busLine.setDistance(distance);
    cout<<"\n Thank you, now I would like to know the hour of your trip";
    cin>>time;
    if(time>)
            "\n\nChoose an option: ";
        cout<<"WELCOME TO THE DEFAULT CONFIGURATION SYSTEM";

}/*
