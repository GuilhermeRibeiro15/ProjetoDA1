#include "StationTrack.h"

/*    Functions    */

Track * Station::addTrack(Station *o,Station *d, int c, string s) {
    auto newTrack = new Track(o, d, c, s);
    adj.push_back(newTrack);
    d->incoming.push_back(newTrack);
    return newTrack;
}

bool Station::removeTrack(string destName) {
    bool removedStation = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Track *track = *it;
        Station *dest = track->getStationB();
        if (dest->getName() == destName) {
            it = adj.erase(it);
            deleteTrack(track);
            removedStation = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedStation;
}

void Station::deleteTrack(Track *track) {
    Station *dest = track->getStationB();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getStationA()->getName() == name) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete track;
}

/*    Station      */

string Station::getName() const {
    return this->name;
}

std::vector<Track*> Station::getAdj() const {
    return this->adj;
}

std::vector<Track *> Station::getIncoming() const {
    return this->incoming;
}

Station::Station(string name, string district, string municipality, string township, string lineName){
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->lineName = lineName;
}

string Station::getDistrict() const {
    return this->district;
}

string Station::getMunicipality() const{
    return this->municipality;
}

string Station::getTownship() const{
    return this->township;
}

string Station::getLine() const{
    return this->lineName;
}

void Station::setName(const string &name){
    Station::name = name;
}

void Station::setDistrict(const string &district){
    Station::district = district;
}

void Station::setMunicipality(const string &municipality){
    Station::municipality = municipality;
}

void Station::setTownship(const string &township){
    Station::township = township;
}

void Station::setLine(const string &lineName){
    Station::lineName = lineName;
}

/*    Track    */

Track::Track(Station *stationA, Station *stationB, int capacity, string service){
    this->stationA = stationA;
    this->stationB = stationB;
    this->capacity = capacity;
    this->service = service;
}

Station * Track::getStationB() const {
    return this->stationB;
}

double Track::getWeight() const {
    return this->weight;
}

Station * Track::getStationA() const {
    return this->stationA;
}

int Track::getCapacity() const {
    return this->capacity;
}

string Track::getService() const{
    return this->service;
}

void Track::setCapacity(const int &capacity) {
    Track::capacity = capacity;
}

void Track::setService(const string &service){
    Track::service = service;
}