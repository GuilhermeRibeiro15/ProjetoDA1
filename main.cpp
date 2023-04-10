#include <iostream>
#include "src/TripManager.h"
#include "src/AlteredTripManager.h"

/**

@brief Displays the main menu options and reads user input to execute the corresponding function.
The function starts by creating objects of the TripManager and AlteredTripManager classes, and then reads user input to
execute the selected option, until the user chooses to quit the program. The function handles input errors and displays
error messages accordingly. The menu options are:
1: Not implemented.
2: Displays information about a station.
3: Displays information about tracks and their maximum flow.
4: Creates an altered network and displays the top k stations affected by the changes.
5: Quits the program.
@return 0 upon successful completion of the program.
*/

void showMenu();

int main() {
    TripManager t;
    string stationsFile;
    string tracksFile;
    cout << "Insert the name of the file with the stations: ";
    getline(cin, stationsFile);
    cout << "Insert the name of the file with the tracks: ";
    getline(cin, tracksFile);
    stationsFile = "../resources/" + stationsFile;
    tracksFile = "../resources/" + tracksFile;
    AlteredTripManager at;
    int test = t.lerFicheiros(stationsFile, tracksFile);
    if (test) {
        cout << "Files not found.\nQuitting.\n";
        return 0;
    }
    at.setStationsFile(stationsFile);
    at.setTracksFile(tracksFile);
    bool keepRunning = true;
    while (keepRunning) {
        showMenu();
        int option;
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            option = 0;
        }
        switch (option) {
            case 1:
                t.askForStation();
                break;
            case 2:
                t.showTracksAndMaxFlowMenu();
                break;
            case 3:
                at.showAlterNetworkMenuController(t);
                break;
            case 4:
                cout << "Have a good day, enjoy your trip!" << '\n';
                keepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
        }
    }
    return 0;
}


void showMenu() {
    cout << "===============================\n";
    cout << "| Menu :                      |\n";
    cout << "| 1- Station Info             |\n";
    cout << "| 2- Tracks, Max Flow         |\n";
    cout << "| 3- Create Altered Network   |\n";
    cout << "| 4- Quit                     |\n";
    cout << "===============================\n";
    cout << "Pick an option:";
}