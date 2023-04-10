#ifndef DAPROJECT_ALTEREDTRIPMANAGER_H
#define DAPROJECT_ALTEREDTRIPMANAGER_H

#include <list>
#include <algorithm>
#include <map>
#include "TripManager.h"
#include "graph.h"
#include "StationTrack.h"

typedef unordered_set<Station *, stationHash, stationHash> stationTable;

class AlteredTripManager {
private:
    stationTable alteredStations;
    graph alteredTracks;
    TripManager originalStation;
    bool first = true;
    string stationsFile;
public:
    const string &getStationsFile() const;

    void setStationsFile(const string &stationsFile);

    const string &getTracksFile() const;

    void setTracksFile(const string &tracksFile);

private:
    string tracksFile;
public:
    /**
 * @brief This function reads the stations and tracks data from two CSV files and creates the corresponding objects.
 * @details It opens and reads the "stations.csv" file and creates a Station object for each line, then adds it to the graph data structure.
 * Then, it opens and reads the "network.csv" file and creates a Track object for each line, linking the corresponding Station objects.
 * The function also adds the newly created Station objects to a hash table for easier lookup.
 * Time complexity: O(V log V + E log V), where V is the number of stations and E is the number of tracks in the input files.
 * @note If either file cannot be opened, the function prints a "File not found" message and returns.
 * @param stationsFile name of the file with the information on stations
 * @param tracksFile name of the file with the information on tracks connecting the stations
 * @return 0 in case of correct reading of the files, -1 otherwise.
*/
    int lerFicheirosAltered(string stationsFile, string tracksFile);

    /**
 * @brief Adds a track to the altered station table.
 * @details Time complexity: O(log E + k), where E is the number of tracks in the tracks set and k is the number of tracks adjacent to stationB
 * @param stationA The origin station.
 * @param stationB The destination station.
 * @param capacity The capacity of the track.
 * @param service The service offered in the track.
 * @param second A boolean to indicate if there is a reverse track.
 * @param cost The cost of the track.
 * @details If the two stations are already in the alteredStations hash table, the track will be added to the adjacency list
 * of stationA and incoming list of stationB, the cost of the track will be set, and the track will be added to the alteredTracks set.
 * If a reverse track is provided, it will be linked with the current track. Otherwise, the current track will not be created.
 *
*/
    void addTrackToAlteredStationTable(Station *stationA, Station *stationB, double capacity, string service, bool second, int cost);

    /**
 * @brief Finds a Station with the given name in the hashtable of altered stations.
 * @details Time complexity: O(n), n being the number of stations in the hashtable.
 * @param name The name of the Station to find.
 * @return Station* A pointer to the Station found or nullptr if it does not exist.
*/
    Station *findStationInAlteredHashtable(const string name);

    /**
 * @brief Adds a station to the hash table of altered stations.
 * @details Time complexity:  O(log V), where V is the number of stations in the stations set
 * @param station The station to be added to the table.
 * @return True if the station was successfully added, false otherwise (if the station already exists in the table).
*/
    bool addToAlteredStationTable(Station *station);

/**
 * @brief Displays a menu with options to make changes to the altered network.
*/
    void showAlterNetwork();

    /**
 * @brief Displays the Alter Network menu and prompts the user for input to perform a specific action.
 *
 * @details This function continuously displays the Alter Network menu until the user chooses to go back.
 * The user selects an option by entering a corresponding number.
 * Time complexity: O(N) where N is the number of iterations it takes for the user to exit the loop.
 *
 * @param t The original TripManager object used to build the original network.
 */
    void showAlterNetworkMenuController(TripManager t);


    /**
 * @brief Removes a station from the altered network.
 * @details This function removes a station from the altered network. It first prompts the user to input the name of the
 * station they want to remove, and then checks if the station exists in the altered network. If the station is
 * found, it is removed along with all its tracks. If the removal is successful, a message is displayed to the
 * user confirming the removal. Otherwise, an error message is displayed.
 * Time complexity: O(n+E), with n being the number of stations in the hashtable, and E being E being the number of tracks in the graph
*/
    void removeStationAlteredNetwork();

    /**
 * @brief Removes a track from the altered network.
 * @details This function prompts the user for the origin and destination stations of the track they want to remove, and then removes
 * that track from the altered network, if it exists. If either the origin or destination station are invalid, the user is prompted
 * again until a valid station is provided. If the user enters "Quit" at any point, the function returns without removing any track.
 * Time complexity: O(n + deg(source)), where n is the number of stations in the hashtable and deg(source) is the degree (number of edges incident to) the source node.
*/
    void removeTrackAlteredNetwork();

    /**
 * @brief Displays a menu with options to test changes to the altered network.
*/
    void showAlterNetworkTest();

    /**
 * @brief Displays the Alter Network Test menu and prompts the user for input to perform a specific action.
 *
 * @details This function continuously displays the Alter Network Test menu until the user chooses to go back.
 * The user selects an option by entering a corresponding number.
 * Time complexity: O(N) where N is the number of iterations it takes for the user to exit the loop.

 *
 */
    void showTestAlterNetworkMenuController();

    /**
 * @brief This method prompts the user to input the origin and destination stations, and then calculates the maximum number of trains that can travel between them in the altered network using the Edmonds-Karp algorithm.
 * @details The method uses the findStationInAlteredHashtable() method to verify if the input stations are valid. If the user enters "Quit" at any point, the method returns. If the stations are valid, the method calculates the maximum flow between them using the edmondsKarp() method of the AlteredGraph class. The total flow value is then printed to the console.
 * Time complexity: O(V * E^2 + n), where V and E are the number of stations and tracks in the network, respectively, and n is the number of stations in the hashtable
 * @note The Edmonds-Karp algorithm is used to find the maximum flow in a network. It runs in O(V*E^2) time, where V is the number of vertices and E is the number of edges in the network.
*/
    void findMaximumFlowAlteredNetwork();

    /**
 * @brief Removes a station from the altered network's hash table of stations.
 * @details Time complexity: O(log n), where n is the number of stations in the alteredStationsSet
 * @param station Pointer to the station to be removed.
 * @return true if the station was removed successfully, false otherwise.
*/
    bool removeFromAlteredStationTable(Station *station);

    /**
 * @brief Finds the top-k stations most affected by changes made to the network.
 *
 * @details This function calculates the difference in maximum flow between the original network and the altered network
 * for each station that was changed, and returns the top k stations that were affected the most. The result
 * is displayed on the console.
 * Time complexity: O(V * E * f + V * log(V)), where N is the number of stations in the alteredStations hash table, E is the number of tracks in the graph and f is the Maximum flow.
 * @param k The number of stations to return.
 */
    void findMostAffectedStations(int k);

    /**
 * @brief Returns the altered station table.
 * @details Time complexity: O(1)
 * @return stationTable The altered station table.
*/
    stationTable getAlteredStationTable() const;
};


#endif //DAPROJECT_ALTEREDTRIPMANAGER_H
