#ifndef __TIMEQUEUE_H_
#define __TIMEQUEUE_H_
//You can change/add to these #includes
#include <ctime>
#include <sstream>
#include <vector>
#include <cassert>

typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{
private:
  std::vector<Job*> tq_heap;

public:
  TimeQueue() {}

  void push(Job* entry);
  Job* pop();
  Job* top() const;
  void remove_from_index(const int index);
  void swap1_and_hook(Job* &a, Job* &b);
  void swap1_without_hook(Job* &a, Job* &b);

  int size() const { return tq_heap.size(); }
  bool empty() const { return tq_heap.empty(); }

  void printHeap(std::ostream & ostr) const;

private:
  void MinHeapify(const int i);
};


#endif
