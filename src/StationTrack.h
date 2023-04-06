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
    void addToAdj(Track *track);
    void addToIncoming(Track *track);
    bool getVisited() const;
    void setVisited(const bool visited);
    void setPath(Track *path);
    Track *getPath() const;

private:
    string lineName;
    string township;
    string municipality;
    string district;
    string name;
    vector<Track *> adj;
    vector<Track *> incoming;
    int node = 0;
    bool visited = false;
    Track* path = nullptr;
};

class Track{

public:
    Track(Station *stationA, Station *stationB, double capacity, string service);
    Station *getDest() const;
    Station *getOrigin() const;
    double getCapacity() const;
    string getService() const;
    void setCapacity(const double &capacity);
    void setService(const string &service);
    double getFlow() const;
    void setFlow(const double flow);
    void setPassed(const bool passed);
    bool getPassed() const;
    void setOposite(Track *oposite);
    Track *getOposite() const;

private:
    Station * origin;
    Station * dest;
    double capacity;
    string service;
    double flow = 0.0;
    bool passed = false;
    Track* oposite = nullptr;


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
