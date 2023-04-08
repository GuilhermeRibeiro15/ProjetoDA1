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
    const graph &getTracks() const;
    TripManager();
    void lerFicheiros();
    void askForStation(graph g);
    Station *findStationInHashtable(const string name);
    bool addToStationTable(Station *station);
    void addTrackToStationTable(Station *stationA, Station *stationB, double capacity, string service, bool second, int cost);
    void askForTracksOfStation(graph g);
    void showOtherInfoMenu();
    void showOtherInfoMenuController();
    void findMaximumFlow();
    void findMaximumFlowPairs();
    void findMaximumFlowTarget();
    void addTrackToTrackSet(Station *stationA, Station *stationB, double capacity, string service);
    void findMinCostPath();
    void findMaximumFlowDistricts();
    void showAlterNetwork();
    void showAlterNetworkMenuController();
    void removeStationAlteredNetwork();
    void removeTrackAlteredNetwork();
    void showTestAlterNetwork();
    void showTestAlterNetworkMenuController();
    void findMaximumFlowAlteredNetwork();

    stationTable getStationTable();
};

#endif //DAPROJECT_TRIPMANAGER_H
