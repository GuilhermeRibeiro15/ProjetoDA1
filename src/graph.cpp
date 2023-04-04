#include "graph.h"

std::vector<Station *> graph::getStationSet() const {
    return stationSet;
}

void graph::addTrack(int origin, int dest, int c, string s) {
    Station* stationOrigin = stationSet[origin];
    Station* stationDest = stationSet[dest];
    stationOrigin->addToAdj(stationOrigin, stationDest, c, s);
    stationDest->addToIncoming(stationOrigin, stationDest, c, s);
    stationSet[origin] = stationOrigin;
    stationSet[dest] = stationDest;
}

void graph::setStation(int v, const string &station, const string &district, const string &municipality, const string &township, const string &lineName) {
    Station* newStation = new Station(station, district, municipality, township, lineName);
    newStation->setNode(v);
    stationSet.push_back(newStation);
}

Station* graph::findStation(const string &name) const {
    for (auto & station : stationSet) {
        if (station->getName() == name)
            return station;
    }
    return nullptr;
}

int graph::getNumStations() const {
    return stationSet.size();
}

bool graph::addStation(const string &name, const string &district, const string &municipality, const string &township, const string &lineName) {
    if (findStation(name) != nullptr)
        return false;
    stationSet.push_back(new Station(name, district, municipality, township, lineName));
    return true;
}

graph::graph(){
}