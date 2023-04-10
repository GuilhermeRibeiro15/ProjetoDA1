#ifndef DAPROJECT_TRIPMANAGER_H
#define DAPROJECT_TRIPMANAGER_H

#include "StationTrack.h"
#include "graph.h"
#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <string>

typedef unordered_set<Station *, stationHash, stationHash> stationTable;

class TripManager {
private:
    stationTable stations;
    graph tracks;
public:

    /**
 *   @brief Default constructor for the TripManager class.
 *   @details This constructor initializes a new TripManager object with default values for its member variables.
 *   Use this constructor when you want to create a new TripManager object with default settings.
 *   Time complexity: O(1)
 *   @param None
 *   @return None
*/
    TripManager();

    /**
 * @brief This function reads the stations and tracks data from two CSV files and creates the corresponding objects.
 * @details It opens and reads the "stations.csv" file and creates a Station object for each line, then adds it to the graph data structure.
 * Then, it opens and reads the "network.csv" file and creates a Track object for each line, linking the corresponding Station objects.
 * The function also adds the newly created Station objects to a hash table for easier lookup.
 * Time complexity: O(V log V + E log V), where V is the number of stations and E is the number of tracks in the input files.
 * @note If either file cannot be opened, the function prints a "File not found" message and returns.
*/
    void lerFicheiros();

    /**
 * @brief Asks the user for the name of a station and prints its information if it exists.
 *
 * @details This function prompts the user to enter the name of a station they want to know about,
 * and searches for the station in the hash table. If the station is found, its information
 * (district, municipality, township, line, number of outgoing and incoming tracks) is printed
 * to the console. If the station is not found, the user is prompted to enter a new name.
 * Time complexity: O(n)
 */
 void askForStation();

/**

 * @brief Finds a Station with the given name in the hashtable of stations.
 * @details Time complexity: O(n), n being the number of stations in the hashtable.
 * @param name The name of the Station to find.
 * @return Station* A pointer to the Station found or nullptr if it does not exist.
*/
Station *findStationInHashtable(const string name);

/**
 * @brief Adds a station to the hash table of stations.
 * @details Time complexity:  O(log V), where V is the number of stations in the stations set
 * @param station The station to be added to the table.
 * @return True if the station was successfully added, false otherwise (if the station already exists in the table).
*/
bool addToStationTable(Station *station);

/**
 * @brief Add a track to the station table and track set.
 * @details Time complexity: O(E log V), where V is the number of stations in the stations set and E is the number of tracks adjacent to the stations
 * @param stationA The first station of the track.
 * @param stationB The second station of the track.
 * @param capacity The capacity of the track.
 * @param service The service provided on the track.
 * @param second Whether the track is being added as the second track in a bidirectional track.
 * @param cost The cost of the track.
*/
void addTrackToStationTable(Station *stationA, Station *stationB, double capacity, string service, bool second,
                            int cost);

/**
 * @brief Prompts the user for a station name and displays information about the outgoing and incoming tracks of the station.
 * @details The function first asks the user to enter a station name. If the name is "Quit", the function returns.
 * Otherwise, it searches for the station in the hashtable using the findStationInHashtable function.
 * If the station is not found, the function informs the user and prompts them to enter the name again.
 * If the station is found, the function displays the station name and a list of outgoing tracks followed by a list of incoming tracks.
 * For each track, the function displays the destination/origin station name, capacity, and service.
 * Time complexity: O(V), where V is the number of stations in the stations set.
*/
void askForTracksOfStation();

/**
 * @brief Displays a menu for accessing various other information about the transportation system.
 *
 * @details The menu allows the user to choose from the following options:
 * - See Incoming and Outgoing Tracks from a Station
 * - Test Max Flow Between 2 Stations
 * - Test Max Flow of All Pairs of Stations
 * - Test Max Flow to a Station
 * - Minimum Cost
 * - Top-k Districts / Municipalities with the biggest Max Flow
 * - Go back
 */
void showOtherInfoMenu();

/**
 * @brief Displays the Other Info menu and prompts the user for input to perform a specific action.
 *
 * @details This function continuously displays the Other Info menu until the user chooses to go back.
 * The user selects an option by entering a corresponding number.
 *
 */
void showOtherInfoMenuController();

/**
 * @brief Finds the maximum flow between two stations using the Edmonds-Karp algorithm.
 *
 * @detailss The function prompts the user to enter the station of origin and the destination station, and finds the maximum
 * flow between them using the Edmonds-Karp algorithm. If either the station of origin or the destination station is
 * invalid, the user is prompted to re-enter their values until valid ones are entered.
 * Its time complexity is O(E * V^2)
 *
 */
void findMaximumFlow();

/**
 * @brief Finds the maximum flow for all pairs of stations.
 * @details This function uses the PairsMaxFlow function from the TracksGraph class to find the maximum flow
 * for all pairs of stations. It then prints the results to the console.
*/
void findMaximumFlowPairs();

/**
 * @brief Finds the maximum flow considering the entire grid in a target station.
 * @details Asks the user for the destination station and calculates the maximum flow that can be achieved in that station,
 * considering all the other stations in the grid.
*/
void findMaximumFlowTarget();

/**
 * @brief Find the minimum cost path between two stations
 * This function prompts the user for the station of origin and the destination station. It then uses Dijkstra's algorithm to find the path with the minimum cost between these two stations, and prints the path and its cost.
*/
void findMinCostPath();


/**
 * @brief Finds the k districts with the highest maximum flow.
 * Asks the user for the number of districts they want to see with the highest maximum flow.
 * Then, calls the findMaxFlowDistrict() method from the Tracks object to print out the
 * requested number of districts with the highest maximum flow.
*/
void findMaximumFlowDistricts();

stationTable getStationTable();

/**
 * @brief Returns the graph of the railway network.
 * @return The graph representing the railway network.
*/
graph getTracks() const;

void addTrackToTrackSet(Station *stationA, Station *stationB, double capacity, string service);

};

#endif //DAPROJECT_TRIPMANAGER_H
