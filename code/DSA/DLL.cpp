#include <bits/stdc++.h>
using namespace std;

struct node {
  char val;
  node *prev, *next;
  node(char val) : val(val), prev(nullptr), next(nullptr) {};
};

class dll {
public:
  node *head, *tail;
  node *cur;

  dll() : head(nullptr), tail(nullptr), cur(nullptr) {};

  void print() {
    node *tmp = head;
    while (tmp) {
      cout << tmp->val;
      tmp = tmp->next;
    }
    cout << endl;
  }

  void insertAfter(char val) {
    node *nw = new node(val);
    if (cur == nullptr) {
      nw->next = head;
      if (head)
        head->prev = nw;
      head = nw;
      if (!tail)
        tail = nw;
    } else {
      nw->next = cur->next;
      nw->prev = cur;
      if (cur->next)
        cur->next->prev = nw;
      else
        tail = nw;
      cur->next = nw;
    }
    cur = nw;
  }

  void deleteBefore() {
    if (cur == nullptr)
      return;
    node *toDelete = cur;
    cur = cur->prev;

    if (toDelete->prev)
      toDelete->prev->next = toDelete->next;
    else
      head = toDelete->next;

    if (toDelete->next)
      toDelete->next->prev = toDelete->prev;
    else
      tail = toDelete->prev;

    delete toDelete;
  }

  void moveLeft() {
    if (cur != nullptr)
      cur = cur->prev;
  }

  void moveRight() {
    if (cur == nullptr) {
      if (head)
        cur = head;
    } else if (cur->next != nullptr) {
      cur = cur->next;
    }
  }
};

int main() {
  dll p;

  while (true) {
    string s;
    cin >> s;

    if (s == "TYPE") {
      char c;
      cin >> c;
      p.insertAfter(c);
    } else if (s == "BACKSPACE") {
      p.deleteBefore();
    } else if (s == "LEFT") {
      p.moveLeft();
    } else if (s == "RIGHT") {
      p.moveRight();
    } else if (s == "DONE") {
      p.print();
      return 0;
    }
  }
}
