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
    AlteredTripManager at;
    t.lerFicheiros();
    bool keepRunning = true;
    while (keepRunning){
        showMenu();
        int option;
        cin >> option;
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            option = 0;
        }
        switch(option){
            case 1:
                cout << "Yet to implement" << '\n';
                break;
            case 2:
                t.askForStation();
                break;
            case 3:
                t.showOtherInfoMenuController();
                break;
            case 4:
                at.showAlterNetworkMenuController(t);
                break;
            case 5:
                cout << "Have a good day, enjoy your trip!" << '\n';
                keepRunning = false;
                break;
            default:
                cout << "Invalid Option!" << '\n';
        }
    }
    return 0;
}


void showMenu(){
    cout << "===============================\n";
    cout << "| Menu :                      |\n";
    cout << "| 1- Main Function            |\n";
    cout << "| 2- Station Info             |\n";
    cout << "| 3- Tracks, Max Flow         |\n";
    cout << "| 4- Create Altered Network   |\n";
    cout << "| 5- Quit                     |\n";
    cout << "===============================\n";
    cout << "Pick an option:";
}