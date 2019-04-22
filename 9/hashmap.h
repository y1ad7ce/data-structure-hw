#ifndef _HASHMAP_H
#define _HASHMAP_H

#include "movie.h"

using namespace std;


class HashNode {
public:
  string key;
  movie* value;

  // Constructor of hashnode
  HashNode(string k, movie* val) : key{k}, value{val} {}

  // Accessors
  string getKey() { return key; }
  movie* getValue() { return value; }
};

class HashMap {
public:
  HashMap();
  HashMap(int cap, float ocp);
  ~HashMap();

  int hashCode(const string key) const;
  void insertNode(const string key, movie* value);
  void insertAMovie(movie* value);

  void checkOccupancy();
  void setOccupancy(const float newOccupancy);
  void setTableSize(const int tSize);
  void resize_table() { resize(capacity*2); }

  vector<movie*> get(const string key) const;
  int size_of_content() const { return size; }


private:
  void resize(const int newSize);

  // hash element array
  HashNode **table;

  int capacity; // the hash table size
  float occupancy;

  // current size, size of content
  int size;
};

#endif
