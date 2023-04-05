#ifndef DAPROJECT_TRIPMANAGER_H
#define DAPROJECT_TRIPMANAGER_H

#include "StationTrack.h"
#include "graph.h"
#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <string>

typedef unordered_set<Station*,stationHash,stationHash> stationTable;

class TripManager{
private:
    stationTable stations;
    graph tracks;
public:
    void lerFicheiros();
    void askForStation();
    Station *findStationInHashtable(const string name);
    bool addToStationTable(Station *station);
    void addTrackToStationTable(Station *stationA, Station *stationB, double capacity, string service, bool second);
    void askForTracksofStation();
    void showOtherInfoMenu();
    void showOtherInfoMenuController();
    void findMaximumFlow();
    void findMaximumFlowPairs();
    bool addTrackToTrackSet(Station *stationA, Station *stationB, double capacity, string service);
};

#endif //DAPROJECT_TRIPMANAGER_H
