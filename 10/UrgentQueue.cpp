#include "Job.h"

void UrgentQueue::push(Job* entry) {
  entry->priority_ptr = this; // set job's pointer pointing to this queue
  entry->urgent_hook = uq_heap.size();

  uq_heap.push_back(entry);
  if (uq_heap.size() == 1) {
    return;
  }

  // maintain heap property
  int i = uq_heap.size()-1;
  while (i > 0) {
    if (uq_heap[i]->getPriority() > uq_heap[(i-1)/2]->getPriority()) {
      swap2_and_hook(uq_heap[i], uq_heap[(i-1)/2]);
      i = (i-1)/2;
    } else {
      break;
    }
  }
}

Job* UrgentQueue::pop() {
  assert( !uq_heap.empty() );

  Job* tmp = uq_heap[0];

  uq_heap[0] = uq_heap[uq_heap.size()-1];
  uq_heap.pop_back();

  MaxHeapify(0);

  for (int i = 0; i < uq_heap.size(); i++) { // reset "hooks"
    uq_heap[i]->urgent_hook = i;
  }

  return tmp;
}

Job* UrgentQueue::top() const {
  assert( !uq_heap.empty() );
  return uq_heap[0];
}

void UrgentQueue::remove_from_index(const int index) {
  uq_heap[index] = uq_heap[uq_heap.size()-1];
  uq_heap.pop_back();

  if (index < uq_heap.size()) {
    MaxHeapify(0);
  }

  for (int i = 0; i < uq_heap.size(); i++) { // reset "hooks"
    uq_heap[i]->urgent_hook = i;
  }
}

void UrgentQueue::swap2_and_hook(Job* &a, Job* &b) {
  // swap jobs and swap the hooks they have
  Job* tmp = a;
  uq_hook tmpH = a->urgent_hook;

  a = b;
  a->urgent_hook = b->urgent_hook;

  b = tmp;
  b->urgent_hook = tmpH;
}

void UrgentQueue::swap2_without_hook(Job* &a, Job* &b) {
  Job* tmp = a;
  a = b;
  b = tmp;
}

void UrgentQueue::MaxHeapify(int i) {
  while (i*2+1 < uq_heap.size()) {
    int j;
    if (i*2+2 < uq_heap.size() && uq_heap[i*2+2]->getPriority() > uq_heap[i*2+1]->getPriority()) {
      j = i*2+2;
    } else {
      j = i*2+1;
    }
    if (uq_heap[j]->getPriority() > uq_heap[i]->getPriority()) {
      swap2_without_hook(uq_heap[j], uq_heap[i]);
      i = j;
    } else {
      break;
    }
  }
}

void UrgentQueue::printHeap(std::ostream & ostr) const {
  ostr << "UQ " << uq_heap.size() << " jobs:" << std::endl;
  for ( unsigned int i=0; i<uq_heap.size(); ++i )
    ostr << "	" << uq_heap[i];
}
