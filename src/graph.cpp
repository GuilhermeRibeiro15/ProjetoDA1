#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <functional>
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
    trackSet.push_back(track);
}

bool graph::sortStation(const Station *s1, const Station *s2) {
    return s1->getNode() < s2->getNode();
}

Station *graph::setStation(int v, const string &station, const string &district, const string &municipality,
                       const string &township, const string &lineName) {
    graph myGraph;
    bool flag = false;
    Station *newStation = new Station(station, district, municipality, township, lineName);
    for (auto i: stationSet) {
        if (i->getName() == newStation->getName()) flag = true;
    }
    if (!flag) {
        newStation->setNode(v);
        stationSet.push_back(newStation);
        std::sort(stationSet.begin(), stationSet.end(),
                  std::bind(&graph::sortStation, &myGraph, std::placeholders::_1, std::placeholders::_2));
        return newStation;
    }
    delete (newStation);
    return nullptr;
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

bool sortDesc(const pair<double, string> &a, const pair<double, string> &b) {
    return a.first > b.first;
}

void graph::organizeData(int k) {
    map<string, vector<Station *>> map_districts;
    set<string> districts;
    map<string, vector<Station *>> map_municipalities;
    set<string> municipalities;
    for (auto it: stationSet) {
        districts.insert(it->getDistrict());
        municipalities.insert(it->getMunicipality());
    }
    for (auto it: districts) {
        vector<Station *> aux;
        for (auto itr: stationSet) {
            if (itr->getDistrict() == it) {
                aux.push_back(itr);
            }
        }
        map_districts.insert({it, aux});
    }

    for (auto it: municipalities) {
        vector<Station *> aux;
        for (auto itr: stationSet) {
            if (itr->getMunicipality() == it) {
                aux.push_back(itr);
            }
        }
        map_municipalities.insert({it, aux});
    }
    int option;
    cout << "Which view of the problem do you want to see?" << endl;
    cout << "1 - The max flow pair of each district / municipality" << endl;
    cout << "2 - The sum of the max flows of each district / municipality" << endl;
    cin >> option;

    switch (option) {
        case 1:
            findMaxFlowDistrict1(map_districts, map_municipalities, k);
            break;
        case 2:
            findMaxFlowDistrict2(map_districts, map_municipalities, k);
            break;
    }
}

void graph::findMaxFlowDistrict1(map<string, vector<Station *>> map_districts, map<string, vector<Station *>> map_municipalities, int k) {
    vector<pair<double, string>> result_districts;
    vector<pair<double, string>> result_municipalities;

    for (auto it: map_districts) {
        double maxComp = -999;
        for (auto itr: it.second) {
            for (auto itrb: it.second) {
                double maxTest = edmondsKarp((*itr).getNode(), (*itrb).getNode());
                if (maxTest > maxComp) maxComp = maxTest;
            }
        }
        result_districts.push_back(make_pair(maxComp, it.first));
    }

    for (auto it: map_municipalities) {
        double maxComp = -999;
        for (auto itr: it.second) {
            for (auto itrb: it.second) {
                double maxTest = edmondsKarp((*itr).getNode(), (*itrb).getNode());
                if (maxTest > maxComp) maxComp = maxTest;
            }
        }
        result_municipalities.push_back(make_pair(maxComp, it.first));
    }
    std::sort(result_districts.begin(), result_districts.end(), sortDesc);
    std::sort(result_municipalities.begin(), result_municipalities.end(), sortDesc);

    cout << endl << "Districts : " << endl << endl;
    for (int i = 0; i < k; i++) {
        cout << result_districts[i].second << " | Flow: " << result_districts[i].first << endl;
    }
    cout << endl << "Municipalities: " << endl << endl;
    for (int i = 0; i < k; i++) {
        cout << result_municipalities[i].second << " | Flow: " << result_municipalities[i].first << endl;
    }
}

void graph::findMaxFlowDistrict2(map<string, vector<Station *>> map_districts, map<string, vector<Station *>> map_municipalities, int k) {
    vector<pair<double, string>> result_districts;
    vector<pair<double, string>> result_municipalities;

    for (auto it: map_districts) {
        double maxComp = 0;
        for (auto itr: it.second) {
            for (auto itrb: it.second) {
                maxComp += edmondsKarp((*itr).getNode(), (*itrb).getNode());
            }
        }
        result_districts.push_back(make_pair(maxComp, it.first));
    }

    for (auto it: map_municipalities) {
        double maxComp = 0;
        for (auto itr: it.second) {
            for (auto itrb: it.second) {
                maxComp += edmondsKarp((*itr).getNode(), (*itrb).getNode());
            }
        }
        result_municipalities.push_back(make_pair(maxComp, it.first));
    }
    std::sort(result_districts.begin(), result_districts.end(), sortDesc);
    std::sort(result_municipalities.begin(), result_municipalities.end(), sortDesc);

    cout << endl << "Districts : " << endl << endl;
    for (int i = 0; i < k; i++) {
        cout << result_districts[i].second << " | Flow: " << result_districts[i].first << endl;
    }
    cout << endl << "Municipalities: " << endl << endl;
    for (int i = 0; i < k; i++) {
        cout << result_municipalities[i].second << " | Flow: " << result_municipalities[i].first << endl;
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

    removeStation(infinity->getNode());

    return result;
}

bool graph::removeStation(int source) {

    Station *station = stationSet[source];
    if (station == stationSet.end().operator*()) return false;

    std::vector<Track *> outgoingTracks = station->getAdj();
    for (auto t: outgoingTracks) {
        station->deleteTrack(t);
        auto it = std::find(trackSet.begin(), trackSet.end(), t);
        if (it != trackSet.end()) trackSet.erase(it);
    }

    std::vector<Track *> incomingTracks = station->getIncoming();
    for (auto t: incomingTracks) {
        t->getOrigin()->deleteTrack(t);
        auto it = std::find(trackSet.begin(), trackSet.end(), t);
        if (it != trackSet.end()) trackSet.erase(it);
    }

    for (int i = source + 1; i < stationSet.size(); i++) {
        stationSet[i]->setNode(i - 1);
    }

    auto it = std::remove_if(stationSet.begin(), stationSet.end(),
                             [&](Station *s) { return s == station; });
    if (it != stationSet.end()) {
        stationSet.erase(it, stationSet.end());
    }
    else{return false;}


    delete station;

    return true;
}

bool graph::removeTrack(int source, int dest) {
    Station *sourceStation = stationSet[source];
    if (sourceStation == nullptr) return false;

    vector<Track *> adj = sourceStation->getAdj();
    for (auto it = adj.begin(); it != adj.end(); it++) {
        Track *t = *it;
        if (t->getDest()->getNode() == dest) {
            sourceStation->deleteTrack(t);
            auto it = std::find(trackSet.begin(), trackSet.end(), t);
            if (it != trackSet.end()) trackSet.erase(it);
            return true;
        }
    }

    return false;
}

pair<vector<Station *>, double> graph::dijkstra(Station *source, Station *target) {
    unordered_map<Station *, double> dist;
    unordered_map<Station *, Station *> prev;
    priority_queue<pair<double, Station *>, vector<pair<double, Station *>>, greater<pair<double, Station *>>> pq;

    for (auto station: stationSet) {
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

        for (auto track: currStation->getAdj()) {
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


