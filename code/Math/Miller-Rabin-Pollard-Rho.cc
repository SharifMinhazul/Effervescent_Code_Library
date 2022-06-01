ll powmod(ll a, ll p, ll m) {///(a^p % m)
  ll result = 1;
  a %= m;
  while (p) {
    if (p & 1)
      result = (vll)result * a % m;
    a = (vll)a * a % m;
    p >>= 1;
  }
  return result;
}
bool check_composite(ll n, ll a, ll d, int s) {
  ll x = powmod(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int r = 1; r < s; r++) {
    x = (vll)x * x % n;
    if (x == n - 1)
      return false;
  }
  return true;
}
bool MillerRabin(ll n) {
  if (n < 2) return false;
  int r = 0;
  ll d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }
  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (check_composite(n, a, d, r))
      return false;
  }
  return true;
}
ll mult(ll a, ll b, ll mod) {
  return (vll)a * b % mod;
}
ll f(ll x, ll c, ll mod) {
  return (mult(x, x, mod) + c) % mod;
}
ll rho(ll n) {
  if (n % 2 == 0) return 2;
  ll x = myrand() % n + 1, y = x, c = myrand() % n + 1, g = 1;
  while (g == 1) {
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(y, c, n);
    g = __gcd(abs(x - y), n);
  }
  return g;
}
set<ll>prime;
void prime_factorization(ll n) {
  if (n == 1) return;
  if (MillerRabin(n)) {
    prime.insert(n);
    return;
  }
  ll x = n;
  while (x == n) x = rho(n);
  prime_factorization(x);
  prime_factorization(n / x);
}
//call prime_factorization(n) for prime factors.
//call MillerRabin(n) to check if prime.
