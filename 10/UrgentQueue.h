#ifndef __URGENTQUEUE_H_
#define __URGENTQUEUE_H_
//You can change/add to these #includes
#include <ctime>
#include <sstream>
#include <vector>
#include <cassert>

typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue {

private:
  std::vector<Job*> uq_heap;

public:
  UrgentQueue() {}

  void push(Job* entry);
  Job* pop();
  Job* top() const;
  void remove_from_index(const int index);
  void swap2_and_hook(Job* &a, Job* &b);
  void swap2_without_hook(Job* &a, Job* &b);

  int size() const { return uq_heap.size(); }
  bool empty() const { return uq_heap.empty(); }

  void printHeap(std::ostream & ostr) const;

private:
  void MaxHeapify(int i);

};


#endif
