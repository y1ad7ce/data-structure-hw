#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();

// https://stackoverflow.com/questions/2439283/how-can-i-create-min-stl-priority-queue
struct compare {
  bool operator()(const std::string& l, const std::string& r) {
    return l > r;
  }
};


void priority_queue_test(const std::string* input_data, int input_count, \
  const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  // std::priority_queue<std::string, std::vector<std::string>, compare> \
  //   pq(input_data, input_data+input_count);
  std::priority_queue<std::string, std::vector<std::string>, compare > \
    pq(input_data, input_data+input_count);


  if (operation == "sort") {
    output_count = 0;

    for (int i = 0; i < input_count; i++) { // O(N)
      output_data[output_count] = pq.top();
      pq.pop(); // O(logN)
      output_count++;
    }
  } else if (operation == "remove_dups_same_order") {
    // not sensible implementation
  } else if (operation == "remove_dups_any_order") {
    output_count = 0;
    std::string tmp = "";

    for (int i = 0; i < input_count; i++) { // O(N)
      if (pq.top() != tmp) {
        output_data[output_count] = pq.top();
        output_count++;

        tmp = pq.top();
      }
      pq.pop();  // O(logN)
    }
  } else if (operation == "mode") {
    output_count = 0;
    std::string tmp = "";
    int current_count = 0;
    int mode_count = 0;

    for (int i = 0; i < input_count; i++) { // O(N)
      if (pq.top() != tmp) {
        output_data[output_count] = pq.top();
        output_count++;

        current_count = 0;
        tmp = pq.top();
      }
      else {
        current_count++;

        if (current_count > mode_count) {
          mode_count = current_count;
          output_data[0] = pq.top();
        }
      }

      pq.pop(); // O(logN)
    }

    output_count = 1;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
