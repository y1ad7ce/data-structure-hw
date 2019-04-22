#include <bits/stdc++.h>
#include "hashmap.h"

HashMap::HashMap(int cap, float ocp) {
  // Initial capacity of hash array
  capacity = cap;
  occupancy = ocp;
  size = 0;
  table = new HashNode*[capacity];

  // Initialise all elements of array as NULL
  for(int i=0 ; i < capacity ; i++)
    table[i] = NULL;
}

HashMap::~HashMap() {
  // destroy all buckets one by one
  for (int i = 0; i < capacity; ++i) {
    if (table[i] != NULL) {
      delete table[i];
      table[i] = NULL;
    }
  }
  // destroy the hash table
  delete [] table;
}


int HashMap::hashCode(const string key) const {
   /*Reference: http://www.partow.net/programming/hashfunctions/
   This is a general-purpose, very good hash function for strings.*/
  unsigned int hash = 1315423911;
  for(unsigned int i = 0; i < key.length(); i++)
    hash ^= ((hash << 5) + key[i] + (hash >> 2));
  return hash % capacity;
}

void HashMap::insertNode(const string key, movie* value) {
  // Function to add key value pair
  checkOccupancy();

  HashNode *temp = new HashNode(key, value);

  // Apply hash function to find index for given key
  int hashIndex = hashCode(key);

  // find next free space
  while(table[hashIndex] != NULL) {
    hashIndex++;
    hashIndex %= capacity;
  }

  //if new node to be inserted increase the current size
  if(table[hashIndex] == NULL)
    size++;

  table[hashIndex] = temp;
}

void HashMap::insertAMovie(movie* Val) {
  vector<string> allKeys = Val->getAllStringKeys();

  for (size_t i = 0; i < allKeys.size(); i++) {
    insertNode(allKeys[i], Val);
  }
}

void HashMap::checkOccupancy() {
  if (size/occupancy > capacity) {
    resize_table();
  }
}

void HashMap::setOccupancy(const float newOccupancy) {
  occupancy = newOccupancy;
  checkOccupancy(); // if new occupancy is lower, check if resize is needed
}

void HashMap::setTableSize(const int tSize) {
  if (tSize < size) {
    cerr << "Error: Trying to resize to a size too small for current content stored in the hash table" << '\n';
    return;
  }
  resize(tSize);
}

vector<movie*> HashMap::get(const string key) const {
  // Function to search the values for a given key
  vector<movie*> results;

  // Apply hash function to find index for given key
  int hashIndex = hashCode(key);
  int count = 0;

  //finding the node with given key
  while(table[hashIndex] != NULL) {

    // count = 0;
    if(count++ >= capacity)  //to avoid infinite loop
      return results;

    //if node found return its value
    if(table[hashIndex]->key == key)
      results.push_back(table[hashIndex]->value);

    hashIndex++;
    hashIndex %= capacity;
  }

  //If not found return null
  return results;
}

void HashMap::resize(const int newSize) {
  // resize the hash table to a given size
  int oldCapacity = capacity;
  capacity = newSize;

  HashNode **oldArr = table;
  table = new HashNode*[capacity];

  // initialize all values of the new table to NULL
  for (int i = 0; i < capacity; i++)
    table[i] = NULL;

  size = 0;

  // copy from the old table, insertNode() will rehash
  for (int j = 0; j < oldCapacity; j++)
    if (oldArr[j] != NULL) {
      insertNode(oldArr[j]->getKey(), oldArr[j]->getValue());
      delete oldArr[j];
      oldArr[j] = NULL;
    }

  delete[] oldArr;
}
