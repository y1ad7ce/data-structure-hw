#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();


void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR
  std::map<std::string, std::pair<std::string, int> > mp;
  std::string prevStr = "";

  int maxCount = 0;
  std::string maxKey;

  for (int i = 0; i < input_count; i++) { // O(N)
    if (mp.find(input_data[i]) == mp.end()) { // O(log N) ---> map find
      // if not found, insert
      mp.insert(std::pair<std::string, std::pair<std::string, int> > \
        (input_data[i], std::pair<std::string, int>(prevStr, 1))); // O(log N) ---> map insert
      prevStr = input_data[i];
    }
    else { // code in this else statment doesn't add up complexity to the
           // program but help with the operations below
      mp[input_data[i]].second++;

      if (mp[input_data[i]].second > maxCount) {
        maxCount = mp[input_data[i]].second;
        maxKey = input_data[i];
      }
    }
  }


  if (operation == "sort") { // O(N)
    output_count = 0;

    for(std::map<std::string, std::pair<std::string, \
      int> >::iterator it = mp.begin(); it != mp.end(); ++it) {

      for (int i = 0; i < it->second.second; i++) { // print as many as counted
        output_data[output_count] = it->first;
        output_count++;
      }
    }
  } else if (operation == "remove_dups_same_order") { // O(N)
    output_count = mp.size();

    for (int i = output_count-1; i >= 0; i--) {
      output_data[i] = prevStr;
      prevStr = mp[prevStr].first; // go to previous in input order
    }
  } else if (operation == "remove_dups_any_order") { // O(N)
    output_count = 0;

    for(std::map<std::string, std::pair<std::string, int> >::iterator \
      it = mp.begin(); it != mp.end(); ++it) {

      output_data[output_count] = it->first;
      output_count++;
    }
  } else if (operation == "mode") { // O(1)
    output_count = 1;
    output_data[0] = maxKey;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
