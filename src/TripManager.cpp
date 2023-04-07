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

void TripManager::addTrackToStationTable(Station* stationA, Station* stationB, double capacity, string service, bool second, int cost){
    Track* track = new Track(stationA, stationB, capacity, service);
    if(stations.find(stationA) != stations.end() && stations.find(stationB) != stations.end()){
        stationA->addToAdj(track);
        stationB->addToIncoming(track);
        track->setCost(cost);
        tracks.addToTrackSet(track);
    }
    else{
        delete track;
        track = nullptr;
    }

    if(second && track != nullptr){
        for(auto t : stationB->getAdj()){
            if(t->getDest()->getName() == stationA->getName()){
                t->setOposite(track);
                track->setOposite(t);
            }
        }
    }
}

void TripManager::addTrackToTrackSet(Station* stationA, Station* stationB, double capacity, string service){
    if (stations.find(stationA) != stations.end() && stations.find(stationB) != stations.end()) {
        Track* track = new Track(stationA, stationB, capacity, service);
        tracks.addToTrackSet(track);
    }
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
    getline(stations_file, line);
    while (getline(stations_file, line)) {
        string name, district, municipality, township, lineName;
        istringstream ss(line);
        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, lineName);

        tracks.setStation(i, name, district, municipality, township, lineName);
        i++;
    }
    stations_file.close();

    vector<Station *> temp = tracks.getStationSet();

    ifstream tracks_file;
    tracks_file.open("../resources/network.csv");
    if (!tracks_file.is_open()){
        cout << "File not found\n";
        return;
    }

    for (auto station: temp) {
        addToStationTable(station);
    }

    getline(tracks_file,line);
    while(getline(tracks_file, line)){
        string stationAName, stationBName, service;
        double capacity;
        int cost;
        istringstream ss(line);
        getline(ss, stationAName, ',');
        getline(ss, stationBName, ',');
        ss >> capacity;
        ss.ignore(1);
        getline(ss, service);

        double capacityA = capacity / 2.0;
        double capacityB = capacity - capacityA;
        Station *stationA;
        Station* stationB;

        stationA = findStationInHashtable(stationAName);
        stationB = findStationInHashtable(stationBName);

        if(service == "STANDARD") cost = 2;
        else if(service == "ALFA PENDULAR") cost = 4;

        addTrackToStationTable(stationA, stationB, capacityA, service, false, cost);
        addTrackToStationTable(stationB, stationA, capacityB, service, true, cost);
    }
    tracks_file.close();
}

void TripManager::askForStation(){
    cout << "What is the name of the station you want to know about?\n";
    string stationName;
    cin.ignore();
    getline(cin, stationName);
    Station *station = findStationInHashtable(stationName);
    while (station == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the name of the station you want to know about?\n";
        getline(cin, stationName);
        station = findStationInHashtable(stationName);
    }
    cout << "Station name: " << stationName << endl;
    cout << "District: " << station->getDistrict() << endl;
    cout << "Municipality: " << station->getMunicipality() << endl;
    cout << "Township: " << station->getTownship() << endl;
    cout << "Line: " << station->getLine() << endl;
    cout << "Number of outgoing tracks: " << station->getAdj().size() << endl;
    cout << "Number of incoming tracks: " << station->getIncoming().size() << endl;
}

void TripManager::showOtherInfoMenuController() {
    bool KeepRunning = true;
    while (KeepRunning) {
        showOtherInfoMenu();
        int option;
        cin >> option;
        switch (option) {
            case 1:
                askForTracksofStation();
                break;
            case 2:
                findMaximumFlow();
                break;
            case 3:
                findMaximumFlowPairs();
                break;
            case 4:
                findMaximumFlowTarget();
                break;
            case 5:
                findMinCostPath();
                break;
            case 6:
                findMaximumFlowDistricts();
                break;
            case 7:
                KeepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
                break;
        }
    }
}

void TripManager::askForTracksofStation() {
    int counter = 1;
    cout << "What is the name of the station you want to know about?\n";
    string stationName;
    cin.ignore();
    getline(cin, stationName);
    Station *station = findStationInHashtable(stationName);
    while (station == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the name of the station you want to know about?\n";
        getline(cin, stationName);
        station = findStationInHashtable(stationName);
    }
    cout << "Station name: " << stationName << endl;
    cout << "----------Outgoing tracks:----------\n";
    for (auto track: station->getAdj()) {
        cout << counter++ << "." << '\n';
        cout << "Destination: " << track->getDest()->getName() << endl;
        cout << "Capacity: " << track->getCapacity() << endl;
        cout << "Service: " << track->getService() << endl;
    }
    counter = 1;
    cout << "----------Incoming tracks----------\n";
    for (auto track: station->getIncoming()) {
        cout << counter++ << "." << '\n';
        cout << "Origin: " << track->getOrigin()->getName() << endl;
        cout << "Capacity: " << track->getCapacity() << endl;
        cout << "Service: " << track->getService() << endl;
    }
}

void TripManager::findMaximumFlow() {
    string origin;
    cout << "What is the Station of Origin?\n";
    cin.ignore();
    getline(cin, origin);
    Station *testStationOrigin = findStationInHashtable(origin);
    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station of Origin?\n";
        getline(cin, origin);
        testStationOrigin = findStationInHashtable(origin);
    }


    string dest;
    cout << "What is the Destination Station?\n";
    getline(cin, dest);
    Station *testStationDestiny = findStationInHashtable(dest);
    while (testStationDestiny == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station?\n";
        getline(cin, dest);
        testStationDestiny = findStationInHashtable(dest);
    }

    double totalFlow = tracks.edmondsKarp(testStationOrigin->getNode(), testStationDestiny->getNode());
    cout << "The flow between these two stations is " << totalFlow << '\n';
}

void TripManager::findMaximumFlowPairs() {
    vector<tuple<Station, Station, double>> totalFlow = tracks.PairsMaxFlow();

    cout << "These are the pairs of stations with the most flow:\n";
    for (auto v: totalFlow) {
        cout << "Origin: " << std::get<0>(v).getName() << " | Destiny:" << std::get<1>(v).getName() << " | Flow: " << std::get<2>(v) << '\n';
    }
    cout << "\n";
}

void TripManager::findMaximumFlowTarget() {
    cin.ignore();
    string dest;
    cout << "What is the Destination Station?\n";
    getline(cin, dest);
    Station *testStationDestiny = findStationInHashtable(dest);

    while (testStationDestiny == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station?\n";
        getline(cin, dest);
        testStationDestiny = findStationInHashtable(dest);
    }


    double totalFlow = tracks.targetMaxFlow(testStationDestiny->getNode());
    cout << "The flow considering the entire grid in that station is: " << totalFlow << "\n";

}

void TripManager::findMaximumFlowDistricts() {
    int k;
    cout << "How many districts do you want to see? ";
    cin >> k;
    tracks.findMaxFlowDistrict(k);
}

void TripManager::findMinCostPath(){
    int counter = 0;
    cin.ignore();
    string origin;
    cout << "What is the Station of Origin?\n";
    getline(cin, origin);
    string dest;
    cout << "What is the Station of Destination?\n";
    getline(cin, dest);
    pair<vector<Station *>, double> minCost = tracks.dijkstra(findStationInHashtable(origin), findStationInHashtable(dest));
    cout << "The minimum cost path between these two stations is: " << '\n';
    for (int i = 0; i < minCost.first.size() - 1; i++){
        counter++;
        if(counter == 6){
            counter = 0;
            cout << minCost.first[i]->getName();
            cout << '\n';
            continue;
        }
        else cout << minCost.first[i]->getName() << " -> ";
    }
    cout << minCost.first[minCost.first.size() - 1]->getName() << '\n';
    cout << "The cost is: " << minCost.second << '\n';
}


void TripManager::showOtherInfoMenu() {
    cout << "=========================================================\n";
    cout << "| Other Info :                                          |\n";
    cout << "| 1- See Incoming and Outgoing Tracks from a Station    |\n";
    cout << "| 2- Test Max Flow Between 2 Stations                   |\n";
    cout << "| 3- Test Max Flow of All Pairs of Stations             |\n";
    cout << "| 4- Test Max Flow to a Station                         |\n";
    cout << "| 5- Minimum Cost                         |\n";
    cout << "| 6- Top-k Districts with the biggest Max Flow          |\n";
    cout << "| 7- Go back                                            |\n";
    cout << "=========================================================\n";
    cout << "Pick an option:";
}

