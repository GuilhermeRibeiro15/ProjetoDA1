#include "StationTrack.h"

/*    Functions    */

void Station::addToAdj(Track *track){
    adj.push_back(track);
}

void Station::addToIncoming(Track *track){
    incoming.push_back(track);
}

bool Station::removeTrack(string destName) {
    bool removedStation = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Track *track = *it;
        Station *dest = track->getDest();
        if (dest->getName() == destName) {
            it = adj.erase(it);
            deleteTrack(track);
            removedStation = true;
        }
        else {
            it++;
        }
    }
    return removedStation;
}

void Station::deleteTrack(Track *track) {
    Station *dest = track->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrigin()->getName() == name) {
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

Station::Station(string name){
    this->name = name;
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

int Station::getNode() const {
    return this->node;
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

void Station::setNode(const int &node){
    Station::node = node;
}

void Station::setAdj(const vector<Track *> &adj) {
    Station::adj = adj;
}

void Station::setIncoming(const vector<Track *> &incoming) {
    Station::incoming = incoming;
}

bool Station::getVisited() const {
    return this->visited;
}

void Station::setVisited(const bool visited) {
    Station::visited = visited;
}

Track* Station::getPath() const{
    return this->path;
}

void Station::setPath(Track* path){
    Station::path = path;
}

/*    Track    */

Track::Track(Station *stationA, Station *stationB, double capacity, string service){
    this->origin = stationA;
    this->dest = stationB;
    this->capacity = capacity;
    this->service = service;
}

Station * Track::getDest() const {
    return this->dest;
}

Station * Track::getOrigin() const {
    return this->origin;
}

double Track::getCapacity() const {
    return this->capacity;
}

string Track::getService() const{
    return this->service;
}

void Track::setCapacity(const double &capacity) {
    Track::capacity = capacity;
}

void Track::setService(const string &service){
    Track::service = service;
}

double Track::getFlow() const {
    return this->flow;
}

void Track::setFlow(const double flow) {
    Track::flow = flow;
}

void Track::setPassed(const bool passed) {
    Track::passed = passed;
}

bool Track::getPassed() const {
    return this->passed;
}

void Track::setOposite(Track *oposite) {
    Track::oposite = oposite;
}

Track *Track::getOposite() const {
    return this->oposite;
}