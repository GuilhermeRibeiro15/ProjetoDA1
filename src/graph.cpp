#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include "graph.h"

std::vector<Station *> graph::getStationSet() const {
    return stationSet;
}

std::vector<Track *> graph::getTrackSet() const {
    return trackSet;
}

void graph::addToTrackSet(Track *track) {
    trackSet.push_back(track);
}

void graph::addTrack(int origin, int dest, double c, string s) {
    Station *stationOrigin = stationSet[origin];
    Station *stationDest = stationSet[dest];
    Track *track = new Track(stationOrigin, stationDest, c, s);
    stationOrigin->addToAdj(track);
    stationDest->addToIncoming(track);
    stationSet[origin] = stationOrigin;
    stationSet[dest] = stationDest;
    Track *newTrack = new Track(stationOrigin, stationDest, c, s);
    trackSet.push_back(newTrack);
}

void graph::setStation(int v, const string &station, const string &district, const string &municipality,
                       const string &township, const string &lineName) {
    Station *newStation = new Station(station, district, municipality, township, lineName);
    newStation->setNode(v);
    stationSet.push_back(newStation);
}

Station *graph::findStation(const string &name) const {
    for (auto &station: stationSet) {
        if (station->getName() == name)
            return station;
    }
    return nullptr;
}

int graph::getNumStations() const {
    return stationSet.size();
}

bool graph::addStation(const string &name, const string &district, const string &municipality, const string &township,
                       const string &lineName) {
    if (findStation(name) != nullptr) return false;
    stationSet.push_back(new Station(name, district, municipality, township, lineName));
    return true;
}

bool graph::findPath(int source, int target) {
    std::queue<Station *> q;
    for (auto s: stationSet) {
        s->setVisited(false);
        s->setPath(nullptr);
    }
    q.push(stationSet[source]);
    q.front()->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->getVisited() && e->getCapacity() - e->getFlow() > 0) {
                w->setPath(e);
                w->setVisited(true);
                q.push(w);
                if (w->getNode() == target) return true;
            }
        }
        for (auto e: v->getIncoming()) {
            auto w = e->getOrigin();
            if (!w->getVisited() && e->getFlow() != 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }
    return false;
}

double graph::edmondsKarp(int source, int target) {
    for (auto v: stationSet) {
        for (auto e: v->getAdj()) e->setFlow(0);
    }
    double totalFlow = 0;
    while (findPath(source, target)) {
        double minResidual = 100000000;
        int dest = target;
        while (dest != source) {
            auto e = stationSet[dest]->getPath();
            double residual;
            if (e->getDest()->getNode() == dest) {
                residual = e->getCapacity() - e->getFlow();
                dest = e->getOrigin()->getNode();
            } else {
                residual = e->getFlow();
                dest = e->getDest()->getNode();
            }
            if (residual < minResidual) minResidual = residual;
        }

        dest = target;
        while (dest != source) {
            auto e = stationSet[dest]->getPath();
            if (e->getDest()->getNode() == dest) {
                e->setFlow(e->getFlow() + minResidual);
                dest = e->getOrigin()->getNode();
            } else {
                e->setFlow(e->getFlow() - minResidual);
                dest = e->getDest()->getNode();
            }
        }
        totalFlow += minResidual;
    }
    return totalFlow;
}

vector<Station *> graph::getEndStationsOfLine() {
    vector<Station *> endStations;
    vector<Station *> difLines;
    bool flag = false;
    for (auto s: stationSet) {
        if (s->getAdj().size() == 1) {
            endStations.push_back(s);
        } else {
            for (auto e: s->getAdj()) {
                difLines.push_back(e->getDest());
            }
            for (auto l: difLines) {
                for (auto l1: difLines) {
                    if (l->getLine() == l1->getLine()) flag = true;
                }
                if (!flag) endStations.push_back(l);
                flag = false;
            }
        }
    }
    return endStations;
}

bool sortdesc(const pair<double, string> &a, const pair<double, string> &b) {
    return a.first > b.first;
}

void graph::findMaxFlowDistrict(int k) {
    vector<pair<double, string>> result;
    map<string, vector<Station *>> map;
    set<string> districts;
    for (auto it: stationSet) {
        districts.insert(it->getDistrict());
    }
    for (auto it: districts) {
        vector<Station *> aux;
        for (auto itr: stationSet) {
            if (itr->getDistrict() == it) {
                aux.push_back(itr);
            }
        }
        map.insert({it, aux});
    }

    for (auto it: map) {
        double maxComp = -999;
        for (auto itr: it.second) {
            for (auto itrb: it.second) {
                double maxTest = edmondsKarp((*itr).getNode(), (*itrb).getNode());
                if (maxTest > maxComp) maxComp = maxTest;
            }
        }
        result.push_back(make_pair(maxComp, it.first));
    }
    std::sort(result.begin(), result.end(), sortdesc);
    for (int i = 0; i < k; i++) {
        cout << "District: " << result[i].second << " | Flow: " << result[i].first << endl;
    }
}

vector<tuple<Station, Station, double>> graph::PairsMaxFlow() {
    double maxComp = -999;
    std::vector<std::tuple<Station, Station, double>> Res;
    for (auto a_it = stationSet.begin(); a_it != stationSet.end(); ++a_it) {
        Station *a = *a_it;
        for (auto b_it = std::next(a_it); b_it != stationSet.end(); ++b_it) {
            Station *b = *b_it;
            double maxTest = edmondsKarp((*a).getNode(), (*b).getNode());
            if (maxTest == maxComp) {
                Res.push_back({*a, *b, maxComp});
            } else if (maxTest > maxComp) {
                if (Res.size() > 0) Res.clear();
                maxComp = maxTest;
                Res.push_back({*a, *b, maxComp});
            }
        }
    }
    return Res;
}


int graph::targetMaxFlow(int target) {
    setStation(stationSet.size(), "Aux", "none", "none", "none", "none");
    Station *infinity = stationSet[stationSet.size() - 1];

    for (auto v: stationSet) {
        if (v->getAdj().size() == 1 && v->getNode() != infinity->getNode() && v->getNode() != target) {
            addTrack(infinity->getNode(), v->getNode(), INT_MAX, "STANDARD");
        }
    }

    double result = edmondsKarp(infinity->getNode(), target);

    for (auto v: infinity->getAdj()) {
        infinity->deleteTrack(v);
    }

    getStationSet().pop_back();

    delete (infinity);


    return result;
}

graph graph::deepCopy() {
    graph copy;
    std::unordered_map<Station*, Station*> nodeMap;

    for (auto s : stationSet) {
        Station* newStation = new Station(*s);
        copy.setStation(newStation->getNode(), newStation->getName(), newStation->getDistrict(), newStation->getMunicipality(),newStation->getTownship(), newStation->getLine());
        nodeMap[s] = newStation;
    }

    for (auto s : stationSet) {
        Station* newSource = nodeMap[s];
        for (auto t : s->getAdj()) {
            Station* newTarget = nodeMap[t->getDest()];
            Track* newTrack = new Track(newSource, newTarget, t->getCapacity(), t->getService());
            copy.addTrack(newSource->getNode(), newTarget->getNode(), newTrack->getCapacity(), newTrack->getService());
        }
    }

    return copy;
}

bool graph::removeStation(Station* station) {
    // Find the station in the station set
    if (station == nullptr) return false;

    // Remove all incoming and outgoing tracks from the station
    std::vector<Track*> incomingTracks = station->getIncoming();
    for (auto t : incomingTracks) {
        t->getOrigin()->deleteTrack(t);
    }
    std::vector<Track*> outgoingTracks = station->getAdj();
    for (auto t : outgoingTracks) {
        t->getDest()->deleteTrack(t);
    }

    auto it = std::find(stationSet.begin(), stationSet.end(), station);
    if (it != stationSet.end()) {
        stationSet.erase(it);
    }
    else{return false;}

    // Delete the station object
    delete station;

    return true;
}

bool graph::removeTrack(Station* source, Station* target) {
    bool test1, test2;
    // Find the track in the source station's outgoing edges
    for (auto it = source->getAdj().begin(); it != source->getAdj().end(); ++it) {
        if ((*it)->getDest() == target) {
            source->getAdj().erase(it);
            test1 = true;
            break;
        }
    }

    // Find the track in the target station's incoming edges
    for (auto it = target->getIncoming().begin(); it != target->getIncoming().end(); ++it) {
        if ((*it)->getOrigin() == source) {
            target->getIncoming().erase(it);
            test2 = true;
            break;
        }
    }

    return test1 & test2;
}



graph::graph() {
}


