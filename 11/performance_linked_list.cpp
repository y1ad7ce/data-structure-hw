#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


void list_test(const std::string* input_data, int input_count, \
  const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;
  for (int i = 0; i < input_count; i++) // O(N)
    lst.push_back(input_data[i]);

  if (operation == "sort") {
    // STL sort
    lst.sort(); // O(N logN)
    output_count = input_count;
    int i = 0;

    for (std::list<std::string>::iterator itr = lst.begin(); \
      itr != lst.end(); itr++) { // O(N)
      output_data[i] = *itr;
      i++;
    }
  } else if (operation == "remove_dups_same_order") {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    int i = 0; // index for iterator

    for (std::list<std::string>::iterator itr = lst.begin(); \
      itr != lst.end(); itr++) { // O(N)
      bool dup = false;
      for (int j = 0; j < output_count; j++) {
      	if (*itr == output_data[j]) {
      	  dup = true;
      	  break;
      	}
      }
      // if it has not already been added to the output list
      if (!dup) {
      	output_data[output_count] = input_data[i];
      	output_count++;
      }

      i++;
    }
  } else if (operation == "remove_dups_any_order") {
    // use STL sort
	  output_count = 0;
    lst.sort(); // O(N logN)

    if(lst.empty()){
      return;
    }

    std::list<std::string>::iterator itr = lst.begin();
    std::list<std::string>::iterator i = lst.begin(); i++;

    for(; i != lst.end(); i++){ // O(N)
      if(*itr != *i){
        output_data[output_count] = *itr;
        output_count++;
      }
      itr++;
    }

    if(*itr != output_data[output_count-1]) {
        output_data[output_count] = *itr;
        output_count++;
    }
  } else if (operation == "mode") {
    // use the list sort algorithm
    lst.sort(); // O(N logN)
    int current_count = 1;
    std::string mode;
    int mode_count = 0;

    // keep track of two pointers into the structure
    std::list<std::string>::iterator current = lst.begin();
    ++current;
    std::list<std::string>::iterator previous = lst.begin();

    for (; current != lst.end(); ++current, ++previous) { // O(N)
      if (*current == *previous) {
	      // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }

    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }

    // save the mode to the output list
    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
