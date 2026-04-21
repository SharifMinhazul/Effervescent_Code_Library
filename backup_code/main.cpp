#include "queue.cpp"
#include "stack.cpp"
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "/home/prantor/Coding/CP/debug.hpp"
#else
#define debug(x)
#define error(...)
#endif

#define int long long
const int mod = 1e9 + 7; // 998244353;
#define all(x) (x).begin(), (x).end()
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  Queue<int> q(2 * n);
  for (int i = 1; i <= n; i++) {
    q.push(i);
  }
  while (q.size() > 1) {
    q.pop();
    int tmp = q.front();
    q.pop();
    q.push(tmp);
  }

  cout << q.front() << endl;
  return 0;
}
