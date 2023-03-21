#include "graph.h"

std::vector<Station *> graph::getStationSet() const {
    return stationSet;
}

void graph::setStation(int v, const string &station) {
    stationSet[v]->setName(station);
}

Station* graph::findStation(const string &name) const {
    for (auto v : stationSet)
        if (v->getName() == name)
            return v;
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