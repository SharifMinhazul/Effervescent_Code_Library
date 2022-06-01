ll bigsum(ll a, ll b, ll m) {
  if (b == 0) return 0;
  ll sum; a %= m;
  if (b & 1) {
    sum = bigsum((a * a) % m, (b - 1) / 2, m);
    sum = (sum + (a * sum) % m) % m;
    sum = (1 + (a * sum) % m) % m;
  } else {
    sum = bigsum((a * a) % m, b / 2, m);
    sum = (sum + (a * sum) % m) % m;
  }
  return sum;
} 
