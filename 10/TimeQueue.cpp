#include "Job.h"

void TimeQueue::push(Job* entry) {
  entry->time_ptr = this; // set job's pointer pointing to this queue
  entry->time_hook = tq_heap.size();

  tq_heap.push_back(entry);
  if (tq_heap.size() == 1) {
    return;
  }

  // maintain heap property
  int i = tq_heap.size()-1;
  while (i > 0) {
    if (tq_heap[i]->getTime() < tq_heap[(i-1)/2]->getTime()) {
      swap1_and_hook(tq_heap[i], tq_heap[(i-1)/2]);
      i = (i-1)/2;
    } else {
      break;
    }
  }
}

Job* TimeQueue::pop() {
  assert( !tq_heap.empty() );

  Job* tmp = tq_heap[0];

  tq_heap[0] = tq_heap[tq_heap.size()-1];
  tq_heap.pop_back();

  MinHeapify(0);

  for (int i = 0; i < tq_heap.size(); i++) { // reset "hooks"
    tq_heap[i]->time_hook = i;
  }

  return tmp;
}

Job* TimeQueue::top() const {
  assert( !tq_heap.empty() );
  return tq_heap[0];
}

void TimeQueue::remove_from_index(const int index) {
  tq_heap[index] = tq_heap[tq_heap.size()-1];
  tq_heap.pop_back();

  if (index < tq_heap.size()) {
    MinHeapify(0);
  }

  for (int i = 0; i < tq_heap.size(); i++) { // reset "hooks"
    tq_heap[i]->time_hook = i;
  }
}

void TimeQueue::swap1_and_hook(Job* &a, Job* &b) {
  // swap jobs and swap the hooks they have
  Job* tmp = a;
  tq_hook tmpH = a->time_hook;

  a = b;
  a->time_hook = b->time_hook;

  b = tmp;
  b->time_hook = tmpH;
}

void TimeQueue::swap1_without_hook(Job* &a, Job* &b) {
  Job* tmp = a;
  a = b;
  b = tmp;
}


void TimeQueue::MinHeapify(int i) {
  while (i*2+1 < tq_heap.size()) {
    int j;
    if (i*2+2 < tq_heap.size() && tq_heap[i*2+2]->getTime() < tq_heap[i*2+1]->getTime()) {
      j = i*2+2;
    } else {
      j = i*2+1;
    }
    if (tq_heap[j]->getTime() < tq_heap[i]->getTime()) {
      swap1_without_hook(tq_heap[j], tq_heap[i]);
      i = j;
    } else {
      break;
    }
  }
}

void TimeQueue::printHeap(std::ostream & ostr) const {
  ostr << "TQ " << tq_heap.size() << " jobs:" << std::endl;
  for ( unsigned int i=0; i<tq_heap.size(); ++i )
    ostr << "	" << tq_heap[i];
}
