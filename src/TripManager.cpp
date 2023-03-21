
#include <list>
#include "TripManager.h"
#include "graph.h"


void TripManager::lerficheiros() {
    ifstream stations_file;
    stations_file.open("../resources/stations.csv");
    if (!stations_file.is_open()){
        cout << "File not found\n";
        return;
    }
    list<Station> temp;
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
        Station station(name , district , municipality , township , lineName);
        temp.push_back(station);
    }
    stations_file.close();

    ifstream tracks_file;
    tracks_file.open("../resources/network.csv");
    if (!tracks_file.is_open()){
        cout << "File not found\n";
        return;
    }

    trips = graph();

    auto ptr = temp.begin();
    for (int i = 1; i <= temp.size(); i++){
        trips.setStation(i,ptr->getName());
        ptr++;
    }

    for (const Station& station : temp)
        stations.insert(station);

    getline(tracks_file,line);
    while(getline(tracks_file, line)){
        string stationAName, stationBName, service;
        int capacity;
        istringstream ss(line);
        getline(ss,stationAName,',');
        getline(ss,stationBName , ',');
        ss >> capacity;
        ss.ignore(1);
        getline(ss, service);

        Station* stationA = trips.findStation(stationAName);
        Station* stationB = trips.findStation(stationBName);

        stationA->addTrack(stationA, stationB, capacity, service);
    }
    tracks_file.close();
}
