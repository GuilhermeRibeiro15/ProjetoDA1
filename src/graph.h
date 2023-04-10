#ifndef DAPROJECT_GRAPH_H
#define DAPROJECT_GRAPH_H

#include "StationTrack.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

class graph {
public:
    graph();

    /**
 * @brief Creates a new Station object and adds it to the graph's set of stations.
 * @details Time complexity: O(n log n), where n is the number of stations in the graph, due to the sorting of stationSet
 * @param v The index of the node corresponding to the new station in the graph's Station vector.
 * @param station The name of the new station.
 * @param district The district where the new station is located.
 * @param municipality The municipality where the new station is located.
 * @param township The township where the new station is located.
 * @param lineName The name of the line the new station belongs to.
 * @return A pointer to the newly created Station object, or nullptr if a station with the same name already exists.
*/
    Station *
    setStation(int v, const string &station, const string &district, const string &municipality, const string &township,
               const string &lineName);

    /**
 * @brief Sorts two stations by their node index
 * @details Time complexity: O(1)
 * @param s1 Pointer to the first Station object
 * @param s2 Pointer to the second Station object
 * @return true if s1's node index is less than s2's node index
 * @return false otherwise
*/
    bool sortStation(const Station *s1, const Station *s2);


/**
 * @brief Adds a track between two stations in the graph.
 * @details Time complexity: O(1)
 * @param origin The index of the origin station in the stationSet vector.
 * @param dest The index of the destination station in the stationSet vector.
 * @param c The capacity of the track.
 * @param s The name of the line that the track belongs to.
*/
    void addTrack(int origin, int dest, double c, string s);

    /**
 * @brief Find a path from a source node to a target node using breadth-first search algorithm
 * @details Time complexity: O(E + V log V), where E is the number of tracks and V is the number of stations in the graph, due to the use of a breadth-first
 * search algorithm with a priority queue to find the shortest path from the source to the target.
 * @param source Index of the source node in the graph's stationSet vector
 * @param target Index of the target node in the graph's stationSet vector
 * @return true if a path is found, false otherwise
*/
    bool findPath(int source, int target);

    /**
 * @brief Applies the Edmonds-Karp algorithm to find the maximum flow in the graph
 * @param source Index of the source node
 * @param target Index of the target node
 * @return double Maximum flow value in the graph
 *
 * @details The function initializes the flow of each edge to zero and repeatedly finds
 * an augmenting path from the source to the target using the `findPath` function. For each
 * augmenting path, it computes the minimum residual capacity along the path and updates the
 * flow along the path accordingly. The process continues until there are no more augmenting
 * paths.
 * Time complexity: O(V * E^2), where V is the number of stations and E is the number of tracks in the graph,
 * due to the use of the Edmonds-Karp algorithm to find the maximum flow in the graph.
 *
 * @note This function assumes that the graph is a directed graph with edges representing
 * the capacity of the flow from the origin to the destination.
 */
    double edmondsKarp(int source, int target);

/**
 * @brief Finds all pairs of stations with the maximum flow between them using the Edmonds-Karp algorithm.
 * @details Time complexity: O(V^2 * E) where V is the number of stations and E is the number of tracks in the graph.
 * @return A vector of tuples, where each tuple contains two stations and the maximum flow between them.
 */
    vector<tuple<Station, Station, double>> PairsMaxFlow();

    /**
 * @brief Adds a Track object to the trackSet vector.
 * @details Time complexity: O(1)
 * @param track A pointer to the Track object to be added.
*/
    void addToTrackSet(Track *track);

    /**
 * @brief Computes the maximum flow from the source to a specific target in the graph.
 *
 * @details To find the maximum flow, an auxiliary node is added to the graph and all nodes with
 * only one neighbor are connected to the auxiliary node with a standard track of infinite capacity.
 * The maximum flow is then calculated from the auxiliary node to the target node using the
 * Edmonds-Karp algorithm.
 * Time complexity: O(E * f) where E is the number of tracks in the graph and f is the maximum flow
 * @param target The target node to find the maximum flow to.
 * @return The maximum flow from the source to the target node.
 */
    int targetMaxFlow(int target);

    /**
 * @brief Finds the maximum flow for the top k districts and municipalities.
 * @details
 * This function first creates maps of all districts and municipalities in the graph
 * with their corresponding stations. It then computes the maximum flow between all pairs
 * of stations for each district and municipality, and stores the results in sorted order
 * in vectors. The top k results from each vector are printed to standard output.
 * Time complexity: O(V^2 * E^4), where V is the number of stations in the graph and E is the number of tracks in the graph
 *
 * @param k The number of top results to print.
 */


    /**
 * @brief Removes a station from the graph and updates the graph accordingly.
 * @details Time complexity: O(E) where E is the number of tracks in the graph.
 * @param source The index of the station to be removed.
 * @return true if the station was successfully removed, false otherwise.
 */
    bool removeStation(int source);

    /**
 * @brief Removes a track from the graph
 * @details Time complexity: O(deg(source)) where deg(source) is the degree of the source station.
 * @param source The index of the source station
 * @param dest The index of the destination station
 *
 * @return true if the track was successfully removed, false otherwise
*/
    bool removeTrack(int source, int target);

    /**
 * @brief Finds the shortest path between two stations using Dijkstra's algorithm.
 * @details Time complexity: O((V + E) * log V) where V is the number of stations and E is the number of tracks in the graph.
 * @param source The starting station.
 * @param target The destination station.
 * @return A pair containing the shortest path between the two stations as a vector of stations, and the total cost of the path as a double.
*/
    pair<vector<Station *>, double> dijkstra(Station *source, Station *target);

    std::vector<Station *> getStationSet() const;

    vector<Track *> getTrackSet() const;

    void organizeData(int k);

    void findMaxFlowDistrict1(map<string, vector<Station *>> map_districts, map<string, vector<Station *>> map_municipalities, int k);

private:
    vector<Station *> stationSet;
    vector<Track *> trackSet;




    void
    findMaxFlowDistrict2(map<string, vector<Station *>> map_districts,
                         map<string, vector<Station *>> map_municipalities,
                         int k);
};

#endif //DAPROJECT_GRAPH_H
