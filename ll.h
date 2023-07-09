#include "node.h"

class LL {
  NodePtr hol; // head of linked list
  NodePtr tail; // tail of linked list
  int size;

public:
  LL();
  int deletes(int value);
  int isEmpty();
  void insert(int value);
  void printList();
  void printListR();
 
  ~LL();
};

LL::LL() {
  hol = NULL;
  tail = NULL;
  size = 0;
}

LL::~LL() {
  cout << "Deleting all nodes" << endl;
  NodePtr currentPtr = hol;
  int i;
  for (i = 0; i < size; i++) {
    NodePtr nextPtr = currentPtr->get_next();
    delete currentPtr;
    currentPtr = nextPtr;
  }
}

void LL::insert(int value) {
  NodePtr newPtr = new Node(value);
  if (newPtr != NULL) {
    if (isEmpty()) {
      hol = newPtr;
      tail = newPtr;
      newPtr->set_next(newPtr);
      newPtr->set_prev(newPtr);
    } else if (value <= hol->get_data()) { // insert at the beginning
      newPtr->set_next(hol);
      newPtr->set_prev(tail);
      hol->set_prev(newPtr);
      tail->set_next(newPtr);
      hol = newPtr;
    } else if (value >= tail->get_data()) { // insert at the end
      newPtr->set_next(hol);
      newPtr->set_prev(tail);
      tail->set_next(newPtr);
      hol->set_prev(newPtr);
      tail = newPtr;
    } else { // insert in the middle
      NodePtr currentPtr = hol->get_next();
      while (currentPtr != hol && value > currentPtr->get_data()) {
        currentPtr = currentPtr->get_next();
      }
      NodePtr previousPtr = currentPtr->get_prev();
      previousPtr->set_next(newPtr);
      newPtr->set_prev(previousPtr);
      newPtr->set_next(currentPtr);
      currentPtr->set_prev(newPtr);
    }
    size++;
  } else {
    cout << value << " not inserted. No memory available." << endl;
  }
}

int LL::deletes(int value) {
  if (isEmpty()) {
    cout << "List is empty." << endl;
    return '\0';
  }

  NodePtr currentPtr = hol;
  NodePtr previousPtr = tail;

  // Find the node to delete
  while (currentPtr->get_data() != value && currentPtr->get_next() != hol) {
    previousPtr = currentPtr;
    currentPtr = currentPtr->get_next();
  }

  if (currentPtr->get_data() == value) {
    if (size == 1) { // Delete the only node in the list
      hol = NULL;
      tail = NULL;
    } else {
      previousPtr->set_next(currentPtr->get_next());
      currentPtr->get_next()->set_prev(previousPtr);
      if (currentPtr == hol) {
        hol = currentPtr->get_next();
      } else if (currentPtr == tail) {
        tail = previousPtr;
        tail->set_next(hol);  // Update the next pointer of the last node
      }
    }
    delete currentPtr;
    size--;
    return value;
  }
  return '\0';
}


int LL::isEmpty() {
  return (hol == NULL);
}

void LL::printList() {
  if (isEmpty()) {
    cout << "List is empty." << endl;
    return;
  }

  cout << "The list is:\n";
  NodePtr currentPtr = hol;
  do {
    currentPtr->print();
    cout << " -> ";
    currentPtr = currentPtr->get_next();
  } while (currentPtr != hol);
  cout << "NULL" << endl;
}

void LL::printListR() {
  if (isEmpty()) {
    cout << "List is empty." << endl;
    return;
  }

  cout << "The reversed list is:\n";
  NodePtr currentPtr = tail;
  do {
    currentPtr->print();
    cout << " -> ";
    currentPtr = currentPtr->get_prev();
  } while (currentPtr != tail);
  cout << "NULL" << endl;
}

