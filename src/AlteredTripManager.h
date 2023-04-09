#ifndef DAPROJECT_ALTEREDTRIPMANAGER_H
#define DAPROJECT_ALTEREDTRIPMANAGER_H

#include <list>
#include <algorithm>
#include <map>
#include "TripManager.h"
#include "graph.h"
#include "StationTrack.h"

typedef unordered_set<Station*,stationHash,stationHash> stationTable;

class AlteredTripManager {
private:
    stationTable alteredStations;
    graph alteredTracks;
    TripManager originalStation;
    bool first = true;
public:
    void lerFicheirosAltered();
    stationTable getAlteredStationTable() const;
    void addTrackToAlteredStationTable(Station* stationA, Station* stationB, double capacity, string service, bool second, int cost);
    void copyStationTable();
    Station *findStationInAlteredHashtable(const string name);
    bool addToAlteredStationTable(Station *station);
    void showAlterNetwork();
    void removeStationAlteredNetwork();
    void showAlterNetworkMenuController(TripManager t);
    void removeTrackAlteredNetwork();
    void showAlterNetworkTest();
    void showTestAlterNetworkMenuController();
    void findMaximumFlowAlteredNetwork();
    void askforAlteredStation();
    bool removeFromAlteredStationTable(Station *station);
    void findMostAffectedStations(int k);
};


#endif //DAPROJECT_ALTEREDTRIPMANAGER_H
