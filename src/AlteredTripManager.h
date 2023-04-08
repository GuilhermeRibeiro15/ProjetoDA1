#ifndef DAPROJECT_ALTEREDTRIPMANAGER_H
#define DAPROJECT_ALTEREDTRIPMANAGER_H

#include <list>
#include <algorithm>
#include "TripManager.h"
#include "graph.h"
#include "StationTrack.h"

typedef unordered_set<Station*,stationHash,stationHash> stationTable;

class AlteredTripManager {
private:
    stationTable alteredStations;
    graph alteredTracks;
    TripManager originalStation;
public:
    stationTable getAlteredStationTable() const;
    void copyStationTable();
    Station *findStationInAlteredHashtable(const string name);
    bool addToAlteredStationTable(Station *station);
    void showAlterNetwork();
    void removeStationAlteredNetwork();
    void showAlterNetworkMenuController();
    void removeTrackAlteredNetwork();
    void showAlterNetworkTest();
    void showTestAlterNetworkMenuController();
    void findMaximumFlowAlteredNetwork();
    void askforAlteredStation();
    bool removeFromAlteredStationTable(Station *station);
};


#endif //DAPROJECT_ALTEREDTRIPMANAGER_H
