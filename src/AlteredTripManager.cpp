#include "AlteredTripManager.h"
using namespace std;

stationTable AlteredTripManager::getAlteredStationTable() const{
    return alteredStations;
}

bool AlteredTripManager::removeFromAlteredStationTable(Station *station){
    if(alteredStations.find(station) == alteredStations.end()) return false;
    alteredStations.erase(station);
    return true;
}

void AlteredTripManager::copyStationTable(){
    originalStation = TripManager();
    originalStation.lerFicheiros();
    stationTable tmp = originalStation.getStationTable();
    for(auto s : tmp){
        alteredStations.insert(s);
        alteredTracks.setStation(s->getNode(), s->getName(), s->getDistrict(), s->getMunicipality(), s->getTownship(), s->getLine());
        vector<Track*> tmpAdj = s->getAdj();
        vector<Track*> tmpIncoming = s->getIncoming();
        for(auto t: tmpAdj){
            alteredTracks.addToTrackSet(t);
        }
        for(auto t: tmpIncoming){
            alteredTracks.addToTrackSet(t);
        }
    }
}

Station* AlteredTripManager::findStationInAlteredHashtable(const string name){
    auto it = find_if(alteredStations.begin(), alteredStations.end(),[name](const Station* s) { return s->getName() == name; });
    if (it != alteredStations.end()) return *it;
    return nullptr;
}

bool AlteredTripManager::addToAlteredStationTable(Station* station){
    if(alteredStations.find(station) == alteredStations.end()){
        alteredStations.insert(station);
        return true;
    }
    return false;
}

void AlteredTripManager::removeStationAlteredNetwork(){
    string origin;
    cout << "What is the Station you wanna Remove? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if(!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);

    if (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        removeStationAlteredNetwork();
    }

    if(alteredTracks.removeStation(testStationOrigin->getNode()) && removeFromAlteredStationTable(testStationOrigin)) cout << "Removed station.\n\n";
    else cout << "Station not found.\n\n";
    cout << "TESTING2  " << alteredTracks.getNumStations() <<"\n";

}

void AlteredTripManager::removeTrackAlteredNetwork(){
    string origin;
    cout << "What is the Origin Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if(!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);

    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station you wanna Remove? (Enter \"Quit\" to go back)\n";
        getline(cin, origin);
        if(!origin.compare("Quit")) return;
        testStationOrigin = findStationInAlteredHashtable(origin);
    }

    string dest;
    cout << "What is the Destination Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, dest);
    if(!dest.compare("Quit")) return;
    Station *testStationDest = findStationInAlteredHashtable(dest);

    while (testStationDest == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station of the track you wanna remove? (Enter \"Quit\" to go back)\n";
        getline(cin, dest);
        if(!dest.compare("Quit")) return;
        testStationDest = findStationInAlteredHashtable(dest);
    }

    if(alteredTracks.removeTrack(testStationOrigin,testStationDest)) cout << "Removed track.\n";
}

void AlteredTripManager::findMaximumFlowAlteredNetwork() {
    string origin;
    cout << "What is the Station of Origin? (Enter \"Quit\" to go back)\n";
    cin.ignore();
    getline(cin, origin);
    if(!origin.compare("Quit")) return;
    Station *testStationOrigin = findStationInAlteredHashtable(origin);
    while (testStationOrigin == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Station of Origin? (Enter \"Quit\" to go back)\n";
        getline(cin, origin);
        if(!origin.compare("Quit")) return;
        testStationOrigin = findStationInAlteredHashtable(origin);
    }

    string dest;
    cout << "What is the Destination Station? (Enter \"Quit\" to go back)\n";
    getline(cin, dest);
    if(!dest.compare("Quit")) return;
    Station *testStationDestiny = findStationInAlteredHashtable(dest);
    while (testStationDestiny == nullptr) {
        cout << "Invalid station.\n";
        cout << "What is the Destination Station? (Enter \"Quit\" to go back)\n";
        getline(cin, dest);
        if(!dest.compare("Quit")) return;
        testStationDestiny = findStationInAlteredHashtable(dest);
    }

    double totalFlow = alteredTracks.edmondsKarp(testStationOrigin->getNode(), testStationDestiny->getNode());
    cout << "The flow between these two stations is " << totalFlow << '\n';
}

void AlteredTripManager::showAlterNetworkMenuController() {
    copyStationTable();
    cout << "TESTING1  " << alteredTracks.getNumStations() <<"\n";
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

void AlteredTripManager::askforAlteredStation(){
    cout << "What is the name of the station you want to know about? (Enter \"Quit\" to go back)\n";
    string stationName;
    cin.ignore();
    getline(cin, stationName);
    if(!stationName.compare("Quit")) return;
    Station *station = findStationInAlteredHashtable(stationName);
    if (station == nullptr) {
        cout << "Invalid station.\n";
        askforAlteredStation();
    }
    cout << "Station name: " << stationName << endl;
    cout << "District: " << station->getDistrict() << endl;
    cout << "Municipality: " << station->getMunicipality() << endl;
    cout << "Township: " << station->getTownship() << endl;
    cout << "Line: " << station->getLine() << endl;
    cout << "Number of outgoing tracks: " << station->getAdj().size() << endl;
    cout << "Number of incoming tracks: " << station->getIncoming().size() << endl;
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
                askforAlteredStation();
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
    cout << "=========================================================\n";
    cout << "| What do you wanna test in your altered network?       |\n";
    cout << "| 1- Calculate maximum number of trains                 |\n";
    cout << "|    that can travel between two stations.              |\n";
    cout << "| 2- Test stations                                      |\n";
    cout << "| 3- Go back                                            |\n";
    cout << "=========================================================\n";
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