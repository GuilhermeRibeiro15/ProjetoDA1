#ifndef DAPROJECT_STATIONTRACK_H
#define DAPROJECT_STATIONTRACK_H

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

class Track;

class Station {

public:
    /**
 * @brief Constructor for the Station class.
 * @details Time complexity: O(1)
 * @param name Name of the station.
*/
    Station(string name);

    /**
 * @brief Constructor for a Station object with name, district, municipality, township, and line name
 * @details Time complexity: O(1)
 * @param name the name of the station
 * @param district the district of the station
 * @param municipality the municipality of the station
 * @param township the township of the station
 * @param lineName the name of the line the station belongs to
 */
    Station(string name, string district, string municipality, string township, string line);

/**
 * @brief Add a track to the adjacent tracks of the station
 * @details Time complexity: O(1)
 * @param track a pointer to the track to add
 */
    void addToAdj(Track *track);

    /**
 * @brief Add a track to the incoming tracks of the station
 * @details Time complexity: O(1)
 * @param track a pointer to the track to add
 */
    void addToIncoming(Track *track);

    /**
 * @brief Get the adjacent tracks of the station
 * @details Time complexity: O(1)
 * @return a vector containing pointers to the adjacent tracks of the station
 */
    vector<Track *> getAdj() const;

    /**
 * @brief Get the incoming tracks of the station
 * @details Time complexity: O(1)
 * @return a vector containing pointers to the incoming tracks of the station
 */
    vector<Track *> getIncoming() const;

    /**
 * @brief Delete a track from the adjacent tracks of the station and from the incoming tracks of its destination station
 * @details Time complexity: O(n), n being the number of elements in the adj vector and/or in the incoming vector
 * @param t a pointer to the track to delete
 *
 * @return true if the track was deleted, false otherwise
 */
    bool deleteTrack(Track *track);

    /**
 * @brief Get the name of the station
 * @details Time complexity: O(1)
 * @return the name of the station
 */
    string getName() const;

    /**
 * @brief Get the district of the station
 * @details Time complexity: O(1)
 * @return the district of the station
 */
    string getDistrict() const;

    /**
 * @brief Get the municipality of the station
 * @details Time complexity: O(1)
 * @return the municipality of the station
 */
    string getMunicipality() const;

    /**
 * @brief Get the township of the station
 * @details Time complexity: O(1)
 * @return the township of the station
 */
    string getTownship() const;

    /**
 * @brief Get the name of the line the station belongs to
 * @details Time complexity: O(1)
 * @return the name of the line the station belongs to
 */
    string getLine() const;

    /**
 * @brief Set the name of the station
 * @details Time complexity: O(1)
 * @param name the name to set for the station
 */
    void setName(const string &name);

/**
 * @brief Set the district of the station
 * @details Time complexity: O(1)
 * @param district the district to set for the station
 */
    void setDistrict(const string &district);

    /**
 * @brief Set the municipality of the station
 * @details Time complexity: O(1)
 * @param municipality the municipality to set for the station
 */
    void setMunicipality(const string &municipality);

    /**
 * @brief Setter function for the name of the township where the station is located.
 * @details Time complexity: O(1)
 * @param township Name of the township.
 */
    void setTownship(const string &township);

    /**
 * @brief Setter function for the name of the line where the station is located.
 * @details Time complexity: O(1)
 * @param lineName Name of the line.
 */
    void setLine(const string &line);

    /**
 * @brief Getter function for the node number of the station in a graph.
 * @details Time complexity: O(1)
 * @return Node number of the station.
 */
    int getNode() const;

    /**
 * @brief Setter function for the node number of the station.
 * @details Time complexity: O(1)
 * @param node The node number of the station.
 */
    void setNode(const int &node);

    /**
 * @brief Sets the outgoing tracks of the station
 * @details Time complexity: O(n), n being the number of elements in the adj vector
 * @param adj A vector containing pointers to the outgoing tracks
 */
    void setAdj(const vector<Track *> &adj);

    /**
 * @brief Sets the incoming tracks of the station
 * @details Time complexity: O(n), n being the number of elements in the incoming vector
 * @param incoming A vector containing pointers to the incoming tracks
 */
    void setIncoming(const vector<Track *> &incoming);

    /**
 * @brief Returns whether the station has been visited during a traversal
 * @details Time complexity: O(1)
 * @return True if the station has been visited, false otherwise
 */
    bool getVisited() const;

    /**
 * @brief Sets whether the station has been visited during a traversal
 * @details Time complexity: O(1)
 * @param visited True if the station has been visited, false otherwise
 */
    void setVisited(const bool visited);


/**
 * @brief Setter function for the path of a track from the station.
 * @details Time complexity: O(1)
 *
 * @param path The path of the track from the station.
 */
    void setPath(Track *path);

/**
 * @brief Getter for the shortest path
 * @details Time complexity: O(1)
 * @return A pointer to the shortest path
     */
    Track *getPath() const;

private:
    string lineName;
    string township;
    string municipality;
    string district;
    string name;
    vector<Track *> adj;
    vector<Track *> incoming;
    int node = 0;
    bool visited = false;
    Track *path = nullptr;

    bool deleteIncomingTrack(Track *t);
};

class Track {

public:
    /**
 * @brief Construct a new Track object.
 * @details Time complexity: O(1)
 * @param stationA Pointer to the first station.
 * @param stationB Pointer to the second station.
 * @param capacity Capacity of the track.
 * @param service Service provided on the track.
 */
    Track(Station *stationA, Station *stationB, double capacity, string service);


/**
 * @brief Get the destination station of the track.
 * @details Time complexity: O(1)
 * @return Pointer to the destination station.
 */
    Station *getDest() const;

    /**
 * @brief Get the origin station of the track.
 * @details Time complexity: O(1)
 * @return Pointer to the origin station.
 */
    Station *getOrigin() const;

    /**
 * @brief Get the capacity of the track.
 * @details Time complexity: O(1)
 * @return Capacity of the track.
 */
    double getCapacity() const;

    /**
 * @brief Get the service provided on the track.
 * @details Time complexity: O(1)
 * @return Service provided on the track.
 */
    string getService() const;

    /**
 * @brief Set the capacity of the track.
 * @details Time complexity: O(1)
 * @param capacity Capacity of the track.
 */
    void setCapacity(const double &capacity);

    /**
 * @brief Set the service provided on the track.
 * @details Time complexity: O(1)
 * @param service Service provided on the track.
 */
    void setService(const string &service);

    /**
 * @brief Get the flow on the track.
 * @details Time complexity: O(1)
 * @return Flow on the track.
 */
    double getFlow() const;

    /**
 * @brief Set the flow on the track.
 * @details Time complexity: O(1)
 * @param flow Flow on the track.
 */
    void setFlow(const double flow);

    /**
 * @brief Set whether the track has been passed or not.
 * @details Time complexity: O(1)
 * @param passed True if the track has been passed, false otherwise.
 */
    void setPassed(const bool passed);

    /**
 * @brief Get whether the track has been passed or not.
 * @details Time complexity: O(1)
 * @return True if the track has been passed, false otherwise.
 */
    bool getPassed() const;

    /**
 * @brief Set the opposite track.
 * @details Time complexity: O(1)
 * @param oposite Pointer to the opposite track.
 */
    void setOposite(Track *oposite);

    /**
 * @brief Get the opposite track.
 * @details Time complexity: O(1)
 * @return Pointer to the opposite track.
 */
    Track *getOposite() const;

    /**
 * @brief Get the cost of the track.
 * @details Time complexity: O(1)
 * @return Cost of the track.
 */
    int getCost() const;

    /**
 * @brief Set the cost of the track.
 * @details Time complexity: O(1)
 * @param cost Cost of the track.
 */
    void setCost(const int cost);

private:
    Station *origin;
    Station *dest;
    double capacity;
    string service;
    int cost = 0;
    double flow = 0.0;
    bool passed = false;
    Track *oposite = nullptr;


};

struct stationHash {
    // TODO
    int operator()(const Station *station) const {
        int res = 1;
        for (char t: station->getName()) {
            res *= t + res;
        }
        return res;
    }

    // TODO
    bool operator()(const Station *s1, const Station *s2) const {
        return s1->getName() == s2->getName();
    }
};


#endif //DAPROJECT_STATIONTRACK_H
