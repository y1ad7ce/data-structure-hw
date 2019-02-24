#ifndef UnrolledLL_h_
#define UnrolledLL_h_
// A simplified implementation of a generic list container class,
// including the list_iterator, but not the const_list_iterators. Three
// separate classes are defined: a Node class, an list_iterator class, and
// the actual list class. The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>

// inner list number of elements defined
const int NUM_ELEMENTS_PER_NODE = 6;
// "forward declarations" for inner list's components are needed
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
 Node() : num_elements(0), next_(NULL), prev_(NULL) {}
 // A helpful additional constructor
 Node(T val) : num_elements(0), next_(NULL), prev_(NULL) { push(val); }
 void push(T val) { elements[num_elements] = val; num_elements++; }
 // REPRESENTATION
 unsigned int num_elements;
 T elements [NUM_ELEMENTS_PER_NODE];
 Node<T>* next_;
 Node<T>* prev_;
};
// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;
// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator() : ptr_(NULL), offset(0) {}
  list_iterator(Node<T>* p) : ptr_(p), offset(0) {}
  list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset(old.offset) {}
  list_iterator<T> operator=(const list_iterator<T> old) {
  ptr_ = old.ptr_; offset = old.offset; return *this; }
  ~list_iterator() {}
  // dereferencing operator gives access to the value at the pointer
  T& operator*() { return (ptr_->elements)[offset]; }
  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
  offset++;
  if (offset == ptr_->num_elements) {
    offset = 0;
    if (ptr_->next_ == NULL) {
      ptr_ = ptr_->next_;
      return NULL;
    }
    ptr_ = ptr_->next_;
  }
  return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
  list_iterator<T> temp(*this);
  offset++;
  if (offset == ptr_->num_elements) {
    offset = 0;
    if (ptr_->next_ == NULL) {
      ptr_ = ptr_->next_;
      return NULL;
    }
    ptr_ = ptr_->next_;
  }
  return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
  if (offset == 0) {
    offset = 0;
    if (ptr_->prev_ == NULL) {
      ptr_ = ptr_->prev_;
      return NULL;
    }
    ptr_ = ptr_->prev_;
  } else { offset--; }
  return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
  list_iterator<T> temp(*this);
  if (offset == 0) {
    offset = 0;
    if (ptr_->prev_ == NULL) {
      ptr_ = ptr_->prev_;
      return NULL;
    }
    ptr_ = ptr_->prev_;
  } else { offset--; }
  return temp;
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;
  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
  return ((ptr_ == r.ptr_) && (offset == r.offset)); }
  bool operator!=(const list_iterator<T>& r) const {
  if (ptr_ == NULL && r.ptr_ != NULL) {
    return true;
  } else if (ptr_ != NULL && r.ptr_ == NULL) {
    return true;
  }
  return ((ptr_ != r.ptr_) || (offset != r.offset)); }
  bool atNewNode() { return offset == 0; }
private:
  // REPRESENTATION
  Node<T>* ptr_; // ptr to node in the list
  unsigned int offset;
};
// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  typedef list_iterator<T> iterator;
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old); }
  UnrolledLL& operator= (UnrolledLL<T>& old);
  ~UnrolledLL() { this->destroy_list(); }
  // simple accessors & modifiers
  unsigned int size() const;
  unsigned int nodeNum() const { return size_; };
  bool empty() const { return head_ == NULL; }
  void print(std::ostream& output) const;
  // read/write access to contents
  const T& front() const { assert (!empty()); return (head_->elements)[0]; }
  T& front() { assert (!empty()); return (head_->elements)[0]; }
  const T& back() const { assert (!empty()); return (tail_->elements)[tail_->num_elements-1]; }
  T& back() { assert (!empty()); return (tail_->elements)[tail_->num_elements-1]; }
  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  iterator erase(UnrolledLL::iterator itr);
  iterator insert(UnrolledLL::iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }
private:
  // private helper functions
  void copy_list(UnrolledLL<T>& old);
  void destroy_list();
  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;

  // this size_ represents the number of Node objects the list contains,
  // not exactly the number of elements in the entire list.
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (UnrolledLL<T>& old) {
 // check for self-assignment
 if (&old != this) {
 this->destroy_list();
 this->copy_list(old);
 }
 return *this;
}
template <class T>
unsigned int UnrolledLL<T>::size() const {
  // member variable size_ is the number of Nodes in the list
  // In each Node, num_elements needs to be summed up in order to get
  // the number of elements in the entire list.
  unsigned int count = 0;
  Node<T>* aNode = head_;
  // std::cout << "SIZE" << size_ << '\n';
  for (size_t i = 0; i < size_; i++) {
    count += aNode->num_elements;
    // std::cout << "____" << aNode->num_elements << '\n';
    for (size_t j = 0; j < aNode->num_elements; j++) {
      // std::cout << "++" << (aNode->elements)[j] << '\n';
    }
    aNode = aNode->next_;
  }
  return count;
}
template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  // corner cases: first Node is full
  if (size_ == 0) { // if the list is empty.
    Node<T>* newHead = new Node<T>(v);
    head_ = tail_ = newHead;
    size_++;
  } else { // list not empty
    if (head_->num_elements == NUM_ELEMENTS_PER_NODE) {
      // if the first Node is full, create a new head and "push_front" to there
      Node<T>* newHead = new Node<T>(v);
      newHead->next_ = head_;
      head_->prev_ = newHead;
      head_ = newHead;
      size_++;
    } else { // the first Node is not full
      for (size_t i = head_->num_elements; i > 0; i--) {
        // move every element to the next, starting backwards
        (head_->elements)[i] = (head_->elements)[i-1];
      }
      (head_->elements)[0] = v;
      (head_->num_elements)++;
    }
  }

}
template <class T>
void UnrolledLL<T>::pop_front() {
  assert (!empty()); // make sure not popping an empty list.
  if (head_->num_elements == 1) {
    if (size_ == 1) {
      this -> destroy_list();
    } else {
      head_ = head_->next_;
      delete head_->prev_;
      head_->prev_ = NULL;
      size_--;
    }
  } else {
    for (size_t i = 0; i < (head_->num_elements)-1; i++) {
      (head_->elements)[i] = (head_->elements)[i+1];
    }
    (head_->num_elements)--;
  }
}
template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  if (size_ == 0) { // empty list
    Node<T>* newEle = new Node<T>(v);
    head_ = newEle;
    tail_ = newEle;
    size_++;
  } else { // not empty list
    if (tail_->num_elements < NUM_ELEMENTS_PER_NODE) {
      // tail_ Node not full
      tail_->push(v);
    } else { // tail_ Node full
      Node<T>* newEle = new Node<T>(v);
      tail_->next_ = newEle;
      newEle->prev_ = tail_;
      tail_ = newEle;
      size_++;
    }
  }
}
template <class T>
void UnrolledLL<T>::pop_back() {
  assert (!empty()); // make sure not popping an empty list.
  if (tail_->num_elements == 1) { // tail_ Node has only one element
    if (size_ == 1) { // list has only one Node
      this -> destroy_list();
    } else { // list has multiple Nodes
      tail_ = tail_->prev_;
      delete tail_->next_;
      tail_->next_ = NULL;
      size_--;
    }
  } else { // tail_ Node has multiple elements
    (tail_->num_elements)--;
  }
}
// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& comp, UnrolledLL<T>& comp2) {
 if (comp.size() != comp2.size()) return false;
 typename UnrolledLL<T>::iterator comp_itr = comp.begin();
 typename UnrolledLL<T>::iterator comp2_itr = comp2.begin();
 // walk over both lists, looking for a mismatched value
 while (comp_itr != comp.end()) {
 if (*comp_itr != *comp2_itr) return false;
 comp_itr++; comp2_itr++;
 }
 return true;
}
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(UnrolledLL::iterator itr) {
  // Note: list's erase function should return an iterator pointing to the
  // element that followed the last element erased by the function call

  // no returned iterator specified in the case means that returning
  // the iterator unchanged would be fine

  assert (!empty());

  if (itr.ptr_->num_elements == 1) {
    // if this is erasing the only element in the Node

    // if there is only one Node left
    if (size_ == 1) { this -> destroy_list(); return begin(); }

    if (itr.ptr_ == head_) {
      // if this is the head_ Node
      head_ = head_->next_;
      delete head_->prev_;
      head_->prev_ = NULL;
      itr.ptr_ = head_;
      size_--;
    } else if (itr.ptr_ == tail_) {
      // if this is the tail_ Node
      tail_ = tail_->prev_;
      delete tail_->next_;
      tail_->next_ = NULL;
      itr.ptr_ = tail_;
      itr.offset = tail_->num_elements;
      size_--;
    } else { // if this is not head_ or tail_ Node
      itr.ptr_ = itr.ptr_->next_;
      itr.ptr_->prev_ = itr.ptr_->prev_->prev_;
      delete itr.ptr_->prev_->next_;
      itr.ptr_->prev_->next_ = itr.ptr_;
      itr.offset = 0;
      size_--;
    }
  } else { // if not erasing the only element in the Node
    if (itr.offset != (itr.ptr_->num_elements) - 1) {
      // if erasing element is not the last element in the Node
      for (size_t i = 0; i < (itr.ptr_->num_elements) - (itr.offset) - 1; i++) {
        // move the following elements forwards
        (itr.ptr_->elements)[i+(itr.offset)] = \
        (itr.ptr_->elements)[i+(itr.offset)+1];
      }
      (itr.ptr_->num_elements)--;
    } else { // erasing the last element in the Node
      (itr.ptr_->num_elements)--;
      if (itr.ptr_->next_ == NULL) {
        return end();
      }
      itr.offset = 0; // go to next Node's first element
      itr.ptr_ = itr.ptr_->next_;
    }
  }
  return itr;
}
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(UnrolledLL::iterator itr, const T& v) {
  // Note: list's insert function returns an iterator that points to the first
  // of the newly inserted elements
  if (size_ == 0) { // if the list is empty.
    Node<T>* aNode = new Node<T>(v);
    head_ = tail_ = aNode;
    size_++;
    return this->begin();
  } else { // list not empty
    if (itr.ptr_->num_elements == NUM_ELEMENTS_PER_NODE) {
      // extra credit
      // if (offset == 0) {
      //   Node<T>* aNode = new Node<T>(v);
      //   itr.ptr_->prev_ = aNode;
      //   aNode->next_ = itr.ptr_;
      //   itr.ptr = aNode;
      // }

      // Node inserting in is full, split the second half and put it into a new NODE
      Node<T>* aNode = new Node<T>();

      // move the elements to a new node
      for (size_t i = 0; i < itr.ptr_->num_elements - itr.offset; i++) {
        aNode->elements[i] = itr.ptr_->elements[itr.offset+i];
      }

      // set numbers of elements and insert the new value
      aNode->num_elements = itr.ptr_->num_elements - itr.offset;
      itr.ptr_->num_elements = itr.offset + 1;
      itr.ptr_->elements[itr.offset] = v;

      // link the new Node
      if (size_ > 1) { // if there were multiple Nodes
        itr.ptr_->next_->prev_ = aNode;
        aNode->next_ = itr.ptr_->next_;
      }
      itr.ptr_->next_ = aNode;
      aNode->prev_ = itr.ptr_;
      size_++;
    } else { // Node inserting in not full
      // move the elements of second half
      for (size_t i = itr.ptr_->num_elements; i > itr.offset; i--) {
        itr.ptr_->elements[i] = itr.ptr_->elements[i-1];
      }
      itr.ptr_->elements[itr.offset] = v;
      itr.ptr_->num_elements++;
    }
  }


  return itr; // itr always unchanged
}
template <class T>
void UnrolledLL<T>::copy_list(UnrolledLL<T>& old) {
  UnrolledLL::iterator itr = old.begin();
  Node<T>* newNode;
  Node<T>* aNode; // helper Node pointer

  // Looping through Nodes in the list
  for (size_t i = 0; i < old.nodeNum(); i++) {
    // create new Node
    newNode = new Node<T>();
    size_++;

    if (i == 0) { head_ = newNode; }
    else { // linking Nodes every time after creating the second Node
      aNode->next_ = newNode;
      newNode->prev_ = aNode;
    }

    if (i == old.nodeNum()-1) { tail_ = newNode;}

    // assigning values;
    for (size_t i = 0; i < NUM_ELEMENTS_PER_NODE; i++) {
      (newNode->elements)[i] = *itr;
      (newNode->num_elements)++;
      itr++;
      if (itr.atNewNode()) { i = NUM_ELEMENTS_PER_NODE; }
    }

    // keep track of the newest node created.
    aNode = newNode;
  }
}
template <class T>
void UnrolledLL<T>::destroy_list() {
  Node<T>* aNode; // helper Node pointer
  while (head_ != NULL) {
    aNode = head_;
    head_ = aNode->next_;
    delete aNode;
  }
  head_ = tail_ = NULL;
  size_ = 0;
}
template <class T>
void UnrolledLL<T>::print(std::ostream& output) const {
  std::cout << "UnrolledLL, size: " << size() << '\n';
  Node<T>* aNode = head_;
  while (aNode != NULL) {
    std::cout << " node:[" << aNode->num_elements << "]";
    for (size_t i = 0; i < aNode->num_elements; i++) {
      std::cout << " " << aNode->elements[i];
    } std::cout << std::endl;
    aNode = aNode->next_;
  }
}

#endif
