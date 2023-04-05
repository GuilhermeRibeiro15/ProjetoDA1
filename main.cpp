#include <iostream>
#include "src/TripManager.h"

void showMenu();

int main() {
    TripManager t;
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
    cout << "=========================\n";
    cout << "| Menu :                |\n";
    cout << "| 1- Main Function      |\n";
    cout << "| 2- Station Info       |\n";
    cout << "| 3- Other Info         |\n";
    cout << "| 4- Quit               |\n";
    cout << "=========================\n";
    cout << "Pick an option:";
}