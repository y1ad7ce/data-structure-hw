#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

using namespace std;

//TODO: You must fill in all ?????? with the correct types.
typedef long int ID_TYPE; //Type for user IDs
typedef vector<double> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef map<ID_TYPE, vector<ID_TYPE> > ADJ_TYPE; //Adjacency Lists type
typedef map<ID_TYPE, COORD_TYPE > GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these.
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations,
                                std::ofstream& outfile, const ID_TYPE& start_id,
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0]
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!"
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!"
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id,
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile,
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
  ID_TYPE user1;
  ID_TYPE user2;
  while (loadfile >> user1 >> user2) {
    adj_lists[user1].push_back(user2);
  }
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
  // { [userID]  ---->  [<lat, lon>]}
  ID_TYPE userID;
  double lat;
  double lon;
  vector<double> tempCoordinates;
  while (loadfile >> userID >> lat >> lon) {
    tempCoordinates.push_back(lat);
    tempCoordinates.push_back(lon);
    locations[userID] = tempCoordinates; // one id one location one vector
    tempCoordinates.clear();
  }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance){

  if (locations.find(start_id) == locations.end()) {
    // reference id has no location
    outfile << "User ID " << start_id << " does not have a recorded location." << '\n';
    return;
  }

  // reference id's location
  double lat1 = locations.find(start_id)->second[0];
  double lon1 = locations.find(start_id)->second[1];

  map<double, vector<ID_TYPE> > distances;  // map {[distance] ---> [<IDs>]}
  double distance;

  for (GEO_TYPE::const_iterator itr = locations.begin(); \
    itr != locations.end(); itr++) { // go through all locations

    if (itr->first == start_id) {
      continue;
    }

    distance = distanceEarth(lat1, lon1, itr->second[0], itr->second[1]);

    if (distance < max_distance) {
      distances[int(distance)].push_back(itr->first);
    }
  }

  if (distances.size() > 0) {
    outfile << "User IDs within " << max_distance <<  \
      " km of user " << start_id << ":\n";
  }
  else {
    outfile << "There are no users within " << max_distance << \
      " km of user " << start_id << "\n";
  }

  for (map<double, vector<ID_TYPE> >::iterator itr = distances.begin(); itr != distances.end(); itr++) {
    // printing by a map, so sorted order automatically.
    outfile << " " << itr->first << " km:";
    for (size_t i = 0; i < itr->second.size(); i++) {
      outfile << " " << itr->second[i];
    }
    outfile << '\n';
  }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  // users with no friend are not included in adj_lists, so degrees are >= 1 always
  std::map<ID_TYPE, ID_TYPE> count;

  for (ADJ_TYPE::const_iterator itr = adj_lists.begin(); \
    itr != adj_lists.end(); itr++) {

    if (count.find(itr->second.size()) != count.end()) {
      count[itr->second.size()]++; // increment if key found
    } else {
      count[itr->second.size()] = 1; // create one and put 1 as value if not added yet
    }
  }

  outfile << "Histogram for " << adj_lists.size() << " users:" << '\n';
  for (map<ID_TYPE, ID_TYPE>::iterator itr2 = count.begin(); itr2 != count.end(); itr2++) {
    outfile << " Degree " << itr2->first << ": " << itr2->second << '\n';
  }
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  // users with no friend are not included in adj_lists, so degrees are >= 1 always

  outfile << "Degrees for " << adj_lists.size() << " users:" << '\n';

  for (ADJ_TYPE::const_iterator itr = adj_lists.begin(); \
    itr != adj_lists.end(); itr++) {
    outfile << " " << itr->first << ": Degree " << itr->second.size()<< '\n';
  }
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree){

    if (adj_lists.find(start_id) == adj_lists.end()) {
      // id not found, this user has no friend or doesn't exist
      outfile << "There is no user with friends and ID " << start_id << '\n';
      return;
    }

    vector<ID_TYPE> users;
    ID_TYPE id;

    for (size_t i = 0; i < adj_lists.find(start_id)->second.size(); i++) {
      id = adj_lists.find(start_id)->second[i]; // friend's id
      if (adj_lists.find(id) == adj_lists.end()) {
        // friend not found in adj_lists
        continue;
      }
      if (adj_lists.find(id)->second.size() == degree) {
        users.push_back(id);
      }
    }

    if (users.size() == 0) {
      outfile << "User " << start_id << " has 0 friend(s) with degree " << degree << '\n';
      return;
    }

    sort(users.begin(), users.end());
    outfile << "User " << start_id << " has " << users.size() << \
      " friend(s) with degree " << degree << ":";

    for (size_t i = 0; i < users.size(); i++) {
      outfile << " " << users[i];
    }
    outfile << '\n';
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations,
                                std::ofstream& outfile, const ID_TYPE& start_id,
                                double max_distance){
    if (adj_lists.find(start_id) == adj_lists.end()) {
      // id not found, no friend or user doesn't exist
      outfile << "There is no user with friends and ID " << start_id << '\n';
      return;
    }
    if (locations.find(start_id) == locations.end()) {
      // this id has no location associated with
      outfile << "User ID " << start_id << " does not have a recorded location." << '\n';
      return;
    }

    // reference id's location
    double lat1 = locations.find(start_id)->second[0];
    double lon1 = locations.find(start_id)->second[1];

    map<double, vector<ID_TYPE> > distances;
    double distance;
    ID_TYPE id;

    for (size_t i = 0; i < adj_lists.find(start_id)->second.size(); i++) {
      id = adj_lists.find(start_id)->second[i]; // friend's id
      // std::cout << "ID: " << id << '\n';
      distance = distanceEarth(lat1, lon1, \
        locations.find(id)->second[0], locations.find(id)->second[1]);
      // std::cout << "distance: " << distance << '\n';
      if (distance < max_distance) {
        distances[distance].push_back(id); // friend within distance
      }
    }

    if (distances.size() > 0) {
      outfile << "Friends within " << max_distance << " km of user " \
        << start_id << ":\n";
    } else {
      outfile << "There are no friends within " << max_distance \
        << " km of user " << start_id << '\n';
    }

    for (map<double, vector<ID_TYPE> >::iterator itr = distances.begin(); \
      itr != distances.end(); itr++) {
      outfile << " " << itr->first << " km:";

      for (size_t i = 0; i < itr->second.size(); i++) {
        outfile << " " << itr->second[i] << '\n';
      }
    }
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it, unsigned int offset){

    if (start_it == end) {
      // check if the id is valid
      outfile << "There is no user with the requested ID" << '\n';
      return;
    }

    vector<ID_TYPE> users;
    ID_TYPE id = start_it->first;
    ADJ_TYPE::const_iterator itr = start_it;

    if (itr != begin) { // going through smaller key values
      itr--;
      while (itr->first <= id+offset && itr->first >= id-offset) {
        // never go beyond such conditions so there's no extra use of the iterator
        users.insert(users.begin(), itr->first); // put at the front for order
        if (itr == begin) {
          break;
        }
        itr--;
      }
      itr = start_it; // reset
    }

    if (itr++ != end) { // going through greater key values
      while (itr->first <= id+offset && itr->first >= id-offset) {
        // never go beyond such conditions so there's no extra use of the iterator
        if (itr == end) {
          break;
        }
        users.push_back(itr->first); // put at the back for order
        itr++;
      }
    }


    if (users.size() == 0) {
      outfile << "There are no users with an ID within +/-" << offset << " of " << start_it->first << '\n';
      return;
    }

    outfile << "Users with an ID within +/-" << offset << " of " << start_it->first \
      << ":";
    for (unsigned int i = 0; i < users.size(); i++) {
      outfile << " " << users[i];
    }
    outfile << '\n';
}
