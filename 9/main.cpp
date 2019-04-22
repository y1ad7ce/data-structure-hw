#include <fstream>
#include <sstream>
#include <algorithm>

#include "hashmap.h"

using namespace std;

void readMoives(ifstream &inputFile, vector<movie*> &movies) {
  // this function reads the movie file and create movie object
  // objects are created on heap, a vector of pointers is the actual use

  string title, year, time, tmp, gList, aList, rList;

  while(getline(inputFile, title)) {
    getline(inputFile, year);
    getline(inputFile, time);
    getline(inputFile, gList);
    getline(inputFile, aList);
    getline(inputFile, rList);

    movie *m = new movie(title, year, time, gList, aList, rList);
    movies.push_back(m);
  }
}

void readActors(ifstream &inputFile, map<string, string> &actors) {
  // this function reads the actor file and build a STL map
  // structure: <key->actor ID, val->actor name>
  string id;
  string name;
  while (inputFile >> id) {
    inputFile >> name;
    actors[id] = name;
  }
}

void makeHashMap(HashMap &HashTable, const vector<movie*> &movies) {
  // this function constructs the hash table.
  // see insertAMovie() for more details about using a movie object
  // to insert the 64 queries into the hash table

  for (size_t i = 0; i < movies.size(); i++) {
    HashTable.insertAMovie(movies[i]);
  }
}

void printSearchResults(const vector<vector<movie*> > &allSearchResults, \
  const map<string, string> &actors) {
    // std::cout << "FINAL OUTPUT: ------------------------>" << '\n';
  for (size_t i = 0; i < allSearchResults.size(); i++) {

    if (allSearchResults[i].size() == 0) {
      cout << "No results for query." << '\n';
    } else {
      cout << "Printing " << allSearchResults[i].size() \
        << " result(s):" << '\n';
    }

    for (size_t j = 0; j < allSearchResults[i].size(); j++) {
      // priting out search results for one query
      allSearchResults[i][j]->print(std::cout, actors);
    }
  }
}

void clearMovies(vector<movie*> &movies) {
  // clean up the heap
  for (size_t i = 0; i < movies.size(); i++) {
    delete movies[i];
  }
}

int main(int argc, char *argv[]) {

  string str, inputF;
  string query = "";


  vector<movie*> movies;
  map<string, string> actors;

  // Hash Map
  int table_size = 100;
  float occupancy = 0.5;
  HashMap HashTable(table_size, occupancy);

  vector<movie*> results; // search results from one query
  vector<vector<movie*> > allSearchResults; // results from all queries

  while (cin >> str) {
    // std::cout << "read one word: -----> " << str << '\n';

    if (str == "query") {
      for (size_t i = 0; i < 7; i++) {
        getline(cin, str);
        query += str;
      }
      // std::cout << "Doing query: " << query << '\n';
      results = HashTable.get(query);
      // std::cout << "Got " << results.size() << " results" << '\n';
      allSearchResults.push_back(results);
      query = "";
    }

    else if (str == "table_size") {
      cin >> str;
      table_size = stoi(str);
      HashTable.setTableSize(table_size);
    }

    else if (str == "occupancy") {
      cin >> str;
      occupancy = stof(str);
      HashTable.setOccupancy(occupancy);
    }

    else if (str == "movies") {
      cin >> inputF;
      ifstream inputFile1(inputF);
      readMoives(inputFile1, movies);
      makeHashMap(HashTable, movies);
    }

    else if (str == "actors") {
      cin >> inputF;
      ifstream inputFile2(inputF);
      readActors(inputFile2, actors);
    }

    else if (str == "quit") {
      break;
    }
  }

  printSearchResults(allSearchResults, actors);

  clearMovies(movies);
}
