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

    MainGraph busLine((reader.calculateNumberOfStops()+2),true);
    unordered_map<string,int> mapStops, mapLines;
     reader.readStops(mapStops,busLine);
     vector<string> lines;
    // busLine.addEdge(125,1462,"1",0.4);
     reader.readLines(lines,mapLines);
     reader.readPaths(busLine,lines,mapStops);
    list<int> lib;
     double a ;
    busLine.localByCoordinates(41.180548, -8.594938);
    busLine.destByCoordinates(41.172245, -8.597604);

    busLine.getMinDistancePath(busLine.getSrc(),busLine.getDest());
    a = busLine.dijkstra_distance(busLine.getSrc(),busLine.getDest());
  //   DisplayMenu(busLine);
   //  for(auto e:mapStops) cout<<e.first<<endl;
    //testMinDistance({41.18302268191288, -8.601038341104502}, {41.16762022369338, -8.617084201223456});

    //testMinDistance(data.getStopsIndex()->at("HSJ5"), data.getStopsIndex()->at("SVP1"));
    //testMinStops(data.getStopsIndex()->at("VIS3"), data.getStopsIndex()->at("PRG2"));

    //data.performAction("HSJ5", "SVP1", ACTION::MinDistance);
    //data.performAction("VIS3", "PRG2", ACTION::MinLines);
    //data.performAction("HSJ5", "PRG2", ACTION::MinLines);
    //data.performAction("HSJ5", "CM3", ACTION::MinLines);
}
void Application::DisplayMenu(MainGraph &busLine) {
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
            case 1: DisplayOptions(busLine); break;
          //  case 2: Help(); break;
            case 3: SetDefaults( busLine); break;
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}


void Application::DisplayOptions(MainGraph &busLine) {
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
            case 1: CoordinatesSelect(input,busLine); break;
            case 2:CoordinatesSelect(input,busLine);break;
            case 3: StopSelect(input,busLine); break;
            case 4:StopSelect(input,busLine); break;
            case 5: {busLine.getMinDistancePath(busLine.getSrc(),busLine.getDest());
            busLine.dijkstra_distance(busLine.getSrc(),busLine.getDest());
            }
            default: cout << "\n\nInvalid input!\n\n";
        }
    } while (input);
}

void Application::CoordinatesSelect(unsigned int input, MainGraph& busLine) {
    cout << "give the coordinates (x y) : "<<endl;
    double latitude,longitude;
    cin >> latitude;
    cin>> longitude;
    cout << endl;

    if(input ==1)busLine.localByCoordinates(latitude,longitude);
    if(input == 2) busLine.destByCoordinates(latitude,longitude);
    } //in case user puts a coordinate x,y


void Application::StopSelect(unsigned int input, MainGraph & busLine) {
    cout<< "insert the name of the stop: " <<endl;
    string name;
    cin>>name;
    if(input == 1) busLine.localByName(name);
}

// EM desenvolvimento, teoricamente isso serve pra botar a distancia maxima que a pessoa quer andar e se ela ta indo de noite ou de dia
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
    busLine.setTime(time);
            "\n\nChoose an option: ";
        cout<<"WELCOME TO THE DEFAULT CONFIGURATION SYSTEM";

}
