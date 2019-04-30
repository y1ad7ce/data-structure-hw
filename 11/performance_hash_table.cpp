#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


void hash_table_test(const std::string* input_data, int input_count, \
  const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR
  std::unordered_map<std::string, std::pair<std::string, int> > ht(input_count);

  std::string prevStr = "";
  int maxCount = 0;
  std::string maxKey;

  for (int i = 0; i < input_count; i++) { // O(N)
    if (ht.find(input_data[i]) == ht.end()) { // O(1) -> O(N)
      // if not found, insert
      ht.insert(std::make_pair(input_data[i], std::make_pair(prevStr, 1))); // O(1) -> O(N)
      prevStr = input_data[i];
    }
    else { // code in this else statment doesn't add up complexity to the
           // program but help with the operations below
      ht[input_data[i]].second++;

      if (ht[input_data[i]].second > maxCount) {
        maxCount = ht[input_data[i]].second;
        maxKey = input_data[i];
      }
    }
  }

  if (operation == "sort") {
    // not sensible implementation
  } else if (operation == "remove_dups_same_order") { // O(N)
    output_count = ht.size();

    for (int i = output_count-1; i >= 0 ; i--) {
      output_data[i] = prevStr;
      prevStr = ht[prevStr].first; // go to previous in input order
    }
  } else if (operation == "remove_dups_any_order") { // O(N)
    output_count = 0;

    for (std::unordered_map<std::string, std::pair<std::string, int> > \
      ::iterator itr = ht.begin(); itr != ht.end(); itr++) {
      output_data[output_count] = itr->first;
      output_count++;
    }
  } else if (operation == "mode") { // O(1)
    output_data[0] = maxKey;
    output_count = 1;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
