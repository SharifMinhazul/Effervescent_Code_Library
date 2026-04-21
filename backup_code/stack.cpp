#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
using namespace std;

template <typename T> class Stack {
private:
  T *arr;
  int Top;
  int capacity;

public:
  Stack(int size = 1000000) {
    capacity = size;
    arr = new T[capacity];
    Top = -1;
  }

  ~Stack() { delete[] arr; }

  void push(T item) {
    if (Top == capacity - 1)
      cout << "Stack Overflow" << endl;
    else
      arr[++Top] = item;
  }

  void pop() {
    if (Top == -1)
      cout << "Stack Underflow" << endl;
    else
      --Top;
  }

  bool isEmpty() { return Top == -1; }

  T top() {
    if (isEmpty()) {
      cout << "Stack is Empty" << endl;
      return T();
    }
    return arr[Top];
  }

  int size() { return Top + 1; }
};

#endif
