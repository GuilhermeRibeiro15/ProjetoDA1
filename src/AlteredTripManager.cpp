#include "AlteredTripManager.h"

using namespace std;

stationTable AlteredTripManager::getAlteredStationTable() const {
    return alteredStations;
}

bool AlteredTripManager::removeFromAlteredStationTable(Station *station) {
    auto it = alteredStations.find(station);
    if (it == alteredStations.end()) return false;
    alteredStations.erase(it);
    return true;
}

void
AlteredTripManager::addTrackToAlteredStationTable(Station *stationA, Station *stationB, double capacity, string service,
                                                  bool second, int cost) {
    Track *track = new Track(stationA, stationB, capacity, service);
    if (alteredStations.find(stationA) != alteredStations.end() &&
        alteredStations.find(stationB) != alteredStations.end()) {
        stationA->addToAdj(track);
        stationB->addToIncoming(track);
        track->setCost(cost);
        alteredTracks.addToTrackSet(track);
    } else {
        delete track;
        track = nullptr;
    }

    if (second && track != nullptr) {
        for (auto t: stationB->getAdj()) {
            if (t->getDest()->getName() == stationA->getName()) {
                t->setOposite(track);
                track->setOposite(t);
            }
        }
    }
}

void AlteredTripManager::lerFicheirosAltered() {
    ifstream stations_file;
    alteredTracks = graph();
    int i = 0;
    stations_file.open("../resources/stations.csv");
    if (!stations_file.is_open()) {
        cout << "File not found\n";
        return;
    }
    string line;
    getline(stations_file, line);
    while (getline(stations_file, line)) {
        string name, district, municipality, township, lineName;
        istringstream ss(line);
        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, lineName);

        Station *testStation = alteredTracks.setStation(i, name, district, municipality, township, lineName);

        if (testStation != nullptr) {
            i++;
            addToAlteredStationTable(testStation);
        }
    }
    stations_file.close();

    ifstream tracks_file;
    tracks_file.open("../resources/network.csv");
    if (!tracks_file.is_open()) {
        cout << "File not found\n";
        return;
    }

    getline(tracks_file, line);
    while (getline(tracks_file, line)) {
        string stationAName, stationBName, service;
        double capacity;
        int cost = 0;
        istringstream ss(line);
        getline(ss, stationAName, ',');
        getline(ss, stationBName, ',');
        ss >> capacity;
        ss.ignore(1);
        getline(ss, service);

        double capacityA = capacity / 2.0;
        double capacityB = capacity - capacityA;
        Station *stationA;
        Station *stationB;

        stationA = findStationInAlteredHashtable(stationAName);
        stationB = findStationInAlteredHashtable(stationBName);

        if (service == "STANDARD") cost = 2;
        else if (service == "ALFA PENDULAR") cost = 4;

        addTrackToAlteredStationTable(stationA, stationB, capacityA, service, false, cost);
        addTrackToAlteredStationTable(stationB, stationA, capacityB, service, true, cost);
    }
    tracks_file.close();
}

Station *AlteredTripManager::findStationInAlteredHashtable(const string name) {
    auto it = find_if(alteredStations.begin(), alteredStations.end(),
                      [name](const Station *s) { return s->getName() == name; });
    if (it != alteredStations.end()) return *it;
    return nullptr;
}

bool AlteredTripManager::addToAlteredStationTable(Station *station) {
    if (alteredStations.find(station) == alteredStations.end()) {
        alteredStations.insert(station);
        return true;
    }
    return false;
}

void AlteredTripManager::removeStationAlteredNetwork() {
    string origin;
    cout << "What is the Station you wanna Remove? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if (!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);

    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station you wanna Remove? (Enter \"Quit\" to go back)\n";
        getline(cin, origin);
        if (!origin.compare("Quit")) return;
        testStationOrigin = findStationInAlteredHashtable(origin);
    }

    if (alteredTracks.removeStation(testStationOrigin->getNode()) && removeFromAlteredStationTable(testStationOrigin))
        cout << "Removed station.\n\n";
    else cout << "Station not found.\n\n";
}

void AlteredTripManager::removeTrackAlteredNetwork() {
    string origin;
    cout << "What is the Origin Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if (!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);

    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station you wanna Remove? (Enter \"Quit\" to go back)\n";
        getline(cin, origin);
        if (!origin.compare("Quit")) return;
        testStationOrigin = findStationInAlteredHashtable(origin);
    }

    string dest;
    cout << "What is the Destination Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
    getline(cin, dest);
    if (!dest.compare("Quit")) return;
    Station *testStationDest = findStationInAlteredHashtable(dest);

    while (testStationDest == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
        getline(cin, dest);
        if (!dest.compare("Quit")) return;
        testStationDest = findStationInAlteredHashtable(dest);
    }

    if (alteredTracks.removeTrack(testStationOrigin->getNode(), testStationDest->getNode())) cout << "Removed track.\n";
    else cout << "Track not found.\n";
}

void AlteredTripManager::findMaximumFlowAlteredNetwork() {
    string origin;
    cout << "What is the Station of Origin? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if (!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);
    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station of Origin? (Enter \"Quit\" to go back)\n";
        getline(cin, origin);
        if (!origin.compare("Quit")) return;
        testStationOrigin = findStationInAlteredHashtable(origin);
    }

    string dest;
    cout << "What is the Destination Station? (Enter \"Quit\" to go back)\n";
    getline(cin, dest);
    if (!dest.compare("Quit")) return;
    Station *testStationDestiny = findStationInAlteredHashtable(dest);
    while (testStationDestiny == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station? (Enter \"Quit\" to go back)\n";
        getline(cin, dest);
        if (!dest.compare("Quit")) return;
        testStationDestiny = findStationInAlteredHashtable(dest);
    }

    double totalFlow = alteredTracks.edmondsKarp(testStationOrigin->getNode(), testStationDestiny->getNode());
    cout << "The flow between these two stations is " << totalFlow << '\n';
}


bool compareTuples(const tuple<Station *, int, int> &t1, const tuple<Station *, int, int> &t2) {
    int diff1 = get<1>(t1) - get<2>(t1);
    int diff2 = get<1>(t2) - get<2>(t2);
    if (diff1 == diff2) {
        return std::get<0>(t1)->getName() < std::get<0>(t2)->getName();
    }
    return diff1 > diff2;
}


void AlteredTripManager::findMostAffectedStations(int k) {
    vector<tuple<Station *, int, int>> comparisons;
    int oldValue, newValue;

    for (auto s: alteredStations) {
        Station *originalS = nullptr;
        if (s != nullptr) originalS = originalStation.findStationInHashtable(s->getName());
        if (originalS != nullptr) {
            oldValue = originalStation.getTracks().targetMaxFlow(originalS->getNode());
            newValue = alteredTracks.targetMaxFlow(s->getNode());
            comparisons.emplace_back(s, oldValue, newValue);
        }
    }

    sort(comparisons.begin(), comparisons.end(), compareTuples);

    cout << "The top " << k << " stations affected by your changes were: \n";
    for (auto v: comparisons) {
        cout << "Station: " << std::get<0>(v)->getName() << " | Old:" << std::get<1>(v) << " | New: " << std::get<2>(v)
             << '\n';
        k--;
        if (k == 0) break;
    }
}

void AlteredTripManager::showAlterNetworkMenuController(TripManager t) {
    if (first) {
        lerFicheirosAltered();
        originalStation = t;
        first = false;
    }
    bool KeepRunning = true;
    while (KeepRunning) {
        showAlterNetwork();
        int option;
        cin >> option;
        switch (option) {
            case 1:
                removeStationAlteredNetwork();
                break;
            case 2:
                removeTrackAlteredNetwork();
                break;
            case 3:
                showTestAlterNetworkMenuController();
                break;
            case 4:
                KeepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
                break;
        }
    }
}

void AlteredTripManager::showTestAlterNetworkMenuController() {
    bool KeepRunning = true;
    while (KeepRunning) {
        showAlterNetworkTest();
        int option;
        cin >> option;
        switch (option) {
            case 1:
                findMaximumFlowAlteredNetwork();
                break;
            case 2:
                cout << "How many affected stations do you wanna see?\n";
                int k;
                cin >> k;
                findMostAffectedStations(k);
                break;
            case 3:
                KeepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
                break;
        }
    }
}

void AlteredTripManager::showAlterNetworkTest() {
    cout << "===================================================================\n";
    cout << "| What do you wanna test in your altered network?                  |\n";
    cout << "| 1- Calculate maximum number of trains                            |\n";
    cout << "|    that can travel between two stations.                         |\n";
    cout << "| 2- Find out the stations most affected by the line failures      |\n";
    cout << "| 3- Go back                                                       |\n";
    cout << "===================================================================\n";
    cout << "Pick an option:";
}

void AlteredTripManager::showAlterNetwork() {
    cout << "=========================================================\n";
    cout << "| What changes do you wanna do to your network?         |\n";
    cout << "| 1- Remove a Station                                   |\n";
    cout << "| 2- Remove a Track                                     |\n";
    cout << "| 3- Test new network with the changes you made         |\n";
    cout << "| 4- Go back                                            |\n";
    cout << "=========================================================\n";
    cout << "Pick an option:";
}