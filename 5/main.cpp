//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end());
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));

  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {
  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //

  std::cout << "All custom tests passed with NUM_ELEMENTS_PER_NODE = 1 and 6" << '\n';

  UnrolledLL<int> a;
  std::list<int> z;

  UnrolledLL<int> b;
  std::list<int> x;

  std::cout << "push_back test and assignment operator test: " << '\n';
  for (int i = 73; i < 87; ++i) {
    a.push_back(i);
    z.push_back(i);
    x.push_back(i);
    assert (SAME(a,x));
  }

  b = a;
  a.print(std::cout);
  b.print(std::cout);
  assert (SAME(b,x));

  std::cout << "pop_back test: " << '\n';
  for (size_t i = 73; i < 87; i++) {
    b.pop_back();
    x.pop_back();
    assert (SAME(b,x));
  }
  b.print(std::cout);

  std::cout << "push_front test:" << '\n';
  for (int i = 73; i < 87; ++i) {
    b.push_front(i);
    x.push_front(i);
    assert (SAME(b,x));
  }
  b.print(std::cout);

  std::cout << "pop_front test: " << '\n';
  for (int i = 73; i < 87; ++i) {
    b.pop_front();
    x.pop_front();
    assert (SAME(b,x));
  }
  b.print(std::cout);

  std::cout << "insert test: " << '\n';
  UnrolledLL<int>::iterator b_itr = b.begin();
  std::list<int>::iterator x_itr = x.begin();
  for (int i = 73; i < 87; ++i) {
    b_itr = b.insert(b_itr, i);
    x_itr = x.insert(x_itr, i);
    assert (SAME(b,x));
  }
  b.print(std::cout);

  std::cout << "erase test(iterator starts with begin()):" << '\n';
  b_itr = b.begin();
  x_itr = x.begin();
  for (int i = 73; i < 87; ++i) {
    b_itr = b.erase(b_itr);
    x_itr = x.erase(x_itr);
    assert (SAME(b,x));
  }
  b.print(std::cout);


  assert (a != b);
  a = b;
  assert (a == b);
}
