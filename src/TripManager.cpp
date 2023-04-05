#include <list>
#include <algorithm>
#include "TripManager.h"
#include "graph.h"

Station* TripManager::findStationInHashtable(const string name){
    auto it = find_if(stations.begin(), stations.end(),[name](const Station* s) { return s->getName() == name; });
    if (it != stations.end()) return *it;
    return nullptr;
}

bool TripManager::addToStationTable(Station* station){
    if(stations.find(station) == stations.end()){
        stations.insert(station);
        return true;
    }
    return false;
}

bool TripManager::addTrackToStationTable(Station* stationA, Station* stationB, double capacity, string service){
    if(stations.find(stationA) != stations.end() && stations.find(stationB) != stations.end()){
        stationA->addToAdj(stationA, stationB, capacity, service);
        stationB->addToIncoming(stationA, stationB, capacity, service);
        return true;
    }
    return false;
}


void TripManager::lerFicheiros() {
    ifstream stations_file;
    tracks = graph();
    int i = 0;
    stations_file.open("../resources/stations.csv");
    if (!stations_file.is_open()){
        cout << "File not found\n";
        return;
    }
    string line;
    getline(stations_file,line);
    while(getline(stations_file, line)){
        string name , district , municipality , township, lineName;
        istringstream ss(line);
        getline(ss,name,',');
        getline(ss,district , ',');
        getline(ss,municipality , ',');
        getline(ss,township,',');
        getline(ss,lineName);

        tracks.setStation(i, name , district , municipality , township , lineName);
        i++;
    }
    stations_file.close();

    vector<Station*> temp = tracks.getStationSet();

    ifstream tracks_file;
    tracks_file.open("../resources/network.csv");
    if (!tracks_file.is_open()){
        cout << "File not found\n";
        return;
    }

    for(auto station : temp){
        addToStationTable(station);
    }

    getline(tracks_file,line);
    while(getline(tracks_file, line)){
        string stationAName, stationBName, service;
        double capacity;
        istringstream ss(line);
        getline(ss,stationAName,',');
        getline(ss,stationBName , ',');
        ss >> capacity;
        ss.ignore(1);
        getline(ss, service);

        double capacityA = capacity / 2.0;
        double capacityB = capacity - capacityA;
        Station* stationA;
        Station* stationB;

        stationA = findStationInHashtable(stationAName);
        stationB = findStationInHashtable(stationBName);

        addTrackToStationTable(stationA, stationB, capacityA, service);
        addTrackToStationTable(stationB, stationA, capacityB, service);
    }
    tracks_file.close();
}

void TripManager::askForStation(){
    cout << "What is the name of the station you want to know about?\n";
    string stationName;
    cin.ignore();
    getline(cin, stationName);
    Station* station = findStationInHashtable(stationName);
    cout << "Station name: " << stationName << endl;
    cout << "District: " << station->getDistrict() << endl;
    cout << "Municipality: " << station->getMunicipality() << endl;
    cout << "Township: " << station->getTownship() << endl;
    cout << "Line: " << station->getLine() << endl;
    cout << "Number of outgoing tracks: " << station->getAdj().size() << endl;
    cout << "Number of incoming tracks: " << station->getIncoming().size() << endl;
}

void TripManager::showOtherInfoMenuController(){
    bool KeepRunning = true;
    while(KeepRunning){
        showOtherInfoMenu();
        int option;
        cin >> option;
        switch(option){
            case 1:
                askForTracksofStation();
                break;
            case 2:
                findMaximumFlow();
                break;
            case 3:
                KeepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
                break;
        }
    }
}

void TripManager::askForTracksofStation(){
    int counter = 1;
    cout << "What is the name of the station you want to know about?\n";
    string stationName;
    cin.ignore();
    getline(cin, stationName);
    Station* station = findStationInHashtable(stationName);
    cout << "Station name: " << stationName << endl;
    cout << "----------Outgoing tracks:----------\n";
    for(auto track : station->getAdj()){
        cout << counter++ << "." << '\n';
        cout << "Destination: " << track->getDest()->getName() << endl;
        cout << "Capacity: " << track->getCapacity() << endl;
        cout << "Service: " << track->getService() << endl;
    }
    counter = 1;
    cout << "----------Incoming tracks----------\n";
    for(auto track : station->getIncoming()){
        cout << counter++ << "." << '\n';
        cout << "Origin: " << track->getOrigin()->getName() << endl;
        cout << "Capacity: " << track->getCapacity() << endl;
        cout << "Service: " << track->getService() << endl;
    }
}

void TripManager::findMaximumFlow(){
    string origin;
    cout << "What is the Station of Origin?\n";
    cin.ignore();
    getline(cin, origin);
    string dest;
    cout << "What is the Station of Destination?\n";
    getline(cin, dest);
    double totalFlow = tracks.edmondsKarp(findStationInHashtable(origin)->getNode(), findStationInHashtable(dest)->getNode());
    cout << "The flow between these two stations is " << totalFlow << '\n';
}


void TripManager::showOtherInfoMenu(){
    cout << "============================\n";
    cout << "| Other Info :             |\n";
    cout << "| 1- Track of Station Info |\n";
    cout << "| 2- Test Edmonds Karp     |\n";
    cout << "| 3- Go back               |\n";
    cout << "============================\n";
    cout << "Pick an option:";
}

