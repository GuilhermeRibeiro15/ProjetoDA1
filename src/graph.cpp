#include <queue>
#include <unordered_map>
#include <algorithm>
#include "graph.h"

std::vector<Station *> graph::getStationSet() const {
    return stationSet;
}

std::vector<Track*> graph::getTrackSet() const {
    return trackSet;
}

void graph::addToTrackSet(Track *track) {
    trackSet.push_back(track);
}

void graph::addTrack(int origin, int dest, double c, string s) {
    Station *stationOrigin = stationSet[origin];
    Station *stationDest = stationSet[dest];
    Track* track = new Track(stationOrigin, stationDest, c, s);
    stationOrigin->addToAdj(track);
    stationDest->addToIncoming(track);
    stationSet[origin] = stationOrigin;
    stationSet[dest] = stationDest;
    Track* newTrack = new Track(stationOrigin, stationDest, c, s);
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

vector<Station*> graph::getEndStationsOfLine(){
    vector<Station*> endStations;
    vector<Station*> difLines;
    bool flag = false;
    for (auto s: stationSet) {
        if (s->getAdj().size() == 1){
            endStations.push_back(s);
        }
        else{
            for(auto e : s->getAdj()){
                difLines.push_back(e->getDest());
            }
            for(auto l : difLines){
                for(auto l1 : difLines){
                    if(l->getLine() == l1->getLine()) flag = true;
                }
                if(!flag) endStations.push_back(l);
                flag = false;
            }
        }
    }
    return endStations;
}

vector<tuple<Station, Station>> graph::PairsMaxFlow() {
    double maxComp = -999;
    std::vector<std::tuple<Station, Station>> Res;
    for (auto a_it = stationSet.begin(); a_it != stationSet.end(); ++a_it) {
        Station *a = *a_it;
        for (auto b_it = std::next(a_it); b_it != stationSet.end(); ++b_it) {
            Station *b = *b_it;
            double maxTest = edmondsKarp((*a).getNode(), (*b).getNode());
            if (maxTest > maxComp) {
                if (Res.size() > 0) Res.clear();
                maxComp = maxTest;
                Res.push_back({*a, *b});
            }
            else if (maxTest == maxComp) {
                Res.push_back({*a, *b});
            }
        }
    }
    return Res;
}


int graph::targetMaxFlow(int target) {
    setStation(stationSet.size(), "Aux", "none", "none","none", "none");
    Station* infinity = stationSet[stationSet.size() - 1];

    for (auto v: stationSet){
        if(v->getAdj().size() == 1 && v->getNode()!=infinity->getNode() && v->getNode() != target){
            addTrack(infinity->getNode(), v->getNode(), INT_MAX, "STANDARD");
        }
    }

    double result = edmondsKarp(infinity->getNode(), target);

    for(auto v : infinity->getAdj()){
        infinity->deleteTrack(v);
    }

    getStationSet().pop_back();

    delete(infinity);


    return result;
}

pair<vector<Station *>, double> graph::dijkstra(Station *source, Station *target) {
    unordered_map<Station *, double> dist;
    unordered_map<Station *, Station *> prev;
    priority_queue<pair<double, Station *>, vector<pair<double, Station *>>, greater<pair<double, Station *>>> pq;

    for (auto station : stationSet) {
        dist[station] = 999999;
        prev[station] = nullptr;
        pq.push(make_pair(999999, station));
    }

    dist[source] = 0.0;
    pq.push(make_pair(0.0, source));

    while (!pq.empty()) {
        Station *currStation = pq.top().second;
        pq.pop();

        if (currStation == target) {
            break;
        }

        for (auto track : currStation->getAdj()) {
            Station *adjStation = track->getDest();
            double alt = dist[currStation] + track->getCost();

            if (alt < dist[adjStation]) {
                dist[adjStation] = alt;
                prev[adjStation] = currStation;
                pq.push(make_pair(alt, adjStation));
            }
        }
    }

    vector<Station *> path;
    Station *currStation = target;
    double cost = dist[target];

    if (prev[currStation] == nullptr) {
        return make_pair(path, 9999999);
    }

    while (currStation != nullptr) {
        path.push_back(currStation);
        currStation = prev[currStation];
    }
    std::reverse(path.begin(), path.end());

    return make_pair(path, cost);
}



graph::graph() {
}


