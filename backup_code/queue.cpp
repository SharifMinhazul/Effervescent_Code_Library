#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
using namespace std;

template <typename T> class Queue {
private:
  T *arr;
  int Front, Rear;
  int capacity;

public:
  Queue(int size = 1000000) {
    capacity = size;
    arr = new T[capacity];
    Front = -1;
    Rear = -1;
  }

  ~Queue() { delete[] arr; }

  void push(T item) {
    if (Rear == capacity - 1) {
      cout << "Queue Overflow" << endl;
    } else {
      if (Front == -1)
        Front = 0;
      Rear++;
      arr[Rear] = item;
    }
  }

  void pop() {
    if (Front == -1 || Front > Rear) {
      cout << "Queue Underflow" << endl;
    } else {
      Front++;
      if (Front > Rear) {
        Front = -1;
        Rear = -1;
      }
    }
  }

  T front() {
    if (Front == -1) {
      cout << "Queue is Empty" << endl;
      return T();
    }
    return arr[Front];
  }

  T rear() {
    if (Rear == -1) {
      cout << "Queue is Empty" << endl;
      return T();
    }
    return arr[Rear];
  }

  bool isEmpty() { return (Front == -1); }

  int size() {
    if (Front == -1)
      return 0;
    return Rear - Front + 1;
  }
};

#endif
