#ifndef DAPROJECT_STATIONTRACK_H
#define DAPROJECT_STATIONTRACK_H

#include <iostream>
#include <vector>

using namespace std;

class Track;

class Station {

public:
    Station(string name);
    Station(string name, string district, string municipality, string township, string line);
    vector<Track *> getAdj() const;
    vector<Track *> getIncoming() const;
    void deleteTrack(Track *track);
    bool removeTrack(string destName);
    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;
    void setName(const string &name);
    void setDistrict(const string &district);
    void setMunicipality(const string &municipality);
    void setTownship(const string &township);
    void setLine(const string &line);
    int getNode() const;
    void setNode(const int &node);
    void setAdj(const vector<Track *> &adj);
    void setIncoming(const vector<Track *> &incoming);
    void addToAdj(Station *stationOrigin, Station *stationDest, int c, string s);
    void addToIncoming(Station* stationOrigin, Station* stationDest, int c, string s);

private:
    string lineName;
    string township;
    string municipality;
    string district;
    string name;
    vector<Track *> adj;
    vector<Track *> incoming;
    int node;
};

class Track{

public:
    Track(Station *stationA, Station *stationB, int capacity, string service);
    Station *getDest() const;
    double getWeight() const;
    Station *getOrigin() const;
    int getCapacity() const;
    string getService() const;
    void setCapacity(const int &capacity);
    void setService(const string &service);

private:
    Station * origin;
    Station * dest;
    double weight;
    int capacity;
    string service;
};

struct stationHash
{
    // TODO
    int operator() (const Station* airport) const {
        int res = 1;
        for (char t : airport->getName()){
            res *= t + res;
        }
        return res;
    }

    // TODO
    bool operator() (const Station* s1, const Station* s2) const {
        return s1->getName() == s2->getName();
    }
};



#endif //DAPROJECT_STATIONTRACK_H
