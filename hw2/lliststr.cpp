#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

LListStr::LListStr(){
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  }

/**
 * Destructor
 */
LListStr::~LListStr(){
  if (size_ == 1)
    delete head_;


  else if (size_ > 1) {
    while (size_ > 0) {
      Item* temp = head_;
      head_ = head_ -> next;
      delete temp;
      size_--;
    }
  }
}

/**
 * Returns the current number of items in the list
 */
int LListStr::size() const {
  return size_;
}

/**
 * Returns true if the list is empty, false otherwise
 */
bool LListStr::empty() const {
  if (size_ == 0)
    return true;
  
  return false;
}

/**
 * Inserts val so it appears at the index given as pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::insert(int pos, const std::string &val)  {
  if (pos < 0 || pos > size_)
    return;

  if (size_ == 0) {
    head_ = new Item;
    tail_ = new Item;
    head_ -> val = val;
    head_ -> next = tail_;
    head_ -> prev = tail_;
    tail_ -> next = head_;
    tail_ -> prev = head_;
    tail_ -> val = val;
    size_++;
  }

  else if (size_ == 1) {
    if(pos == 0) {
      head_ -> val = val;
      size_++;
    }
    else if(pos == 1) {
      tail_ -> val = val;
      size_++;
    }
  }

  else if (pos == size_) {
    Item* add = new Item;
      add -> prev = tail_;
      add -> next = head_;
      add -> val = val;
      add -> prev -> next = add;
      add -> next -> prev = add;
      tail_ = add;
      size_++;
  }

  else {
    Item* temp = head_;
    for (int i = 0; i < pos; i++) {
        temp = temp -> next;
    }

      Item* add = new Item;
      add -> prev = temp -> prev;
      add -> next = temp;
      add -> val = val;
      add -> prev -> next = add;
      add -> next -> prev = add;
      size_++;

    if (temp == head_) {
      head_ = add;
    }

    temp = NULL;
  }
}

/**
 * Removes the value at the index given by pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::remove(int pos){
  if (pos < 0 || pos >= size_)
    return;

  if (size_ == 0) {
    return;
  }

  else if (size_ == 1) {
    head_ = NULL;
    delete head_;
    tail_ = NULL;
    delete tail_;
    size_--;
  }

  else {
    Item* temp = head_;
    for (int i = 0; i < pos; i++) {
        temp = temp -> next;
    }
    
    if (temp == head_) {
      head_ = head_ -> next;
    }

    if (temp == tail_) {
      tail_ = tail_ -> prev;
    }

    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    temp = NULL;
    size_--;
  }

  return;
}

/**
 * Overwrites the old value at the index given by pos with val. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::set(int pos, const std::string &val){
  if (pos < 0 || pos >= size_)
    return;

  if (size_ == 0)
    return;

  else if (size_ == 1)
    head_ -> val = val;

  Item* temp = head_;
  for (int i = 0; i < pos; i++) {
      temp = temp -> next;
  }

  temp -> val = val;
}

/**
 * Returns the value at the index given by pos.  If the index pos is invalid,
 * then you should return the empty string.
 */
string LListStr::get(int pos) const{
  if (pos < 0 || pos >= size_)
    return "";

  if (size_ == 0)
    return head_ -> val;

  Item* temp = head_;
  for (int i = 0; i < pos; i++) {
      temp = temp -> next;
  }
  string value = temp -> val;
  temp = NULL;
  return value;
}