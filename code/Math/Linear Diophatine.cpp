int extended_gcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0){x = 1;y = 0;return a;}
  ll x1, y1;
  ll d = extended_gcd(b, a % b, x1, y1);
  x = y1;y = x1 - y1 * (a / b);
  return d;
}
/*x'=x+(k*B/g),y'=y-(k*A/g);infinite soln
if A=B=0,C must equal 0 and any x,y is solution;
if A|B=0,(x,y)=(C/A,k)|(k,C/B)*/
bool LDE(ll A,ll B,ll C,ll &x,ll &y){
  int g=gcd(A,B);
  if(C%g!=0)return false;
  int a=A/g,b=B/g,c=C/g;
  extended_gcd(a,b,x,y);//ax+by=1
  if(g<0){a*=-1;b*=-1;c*=-1;}//Ensure gcd(a,b)=1
  x*=c;y*=c;//ax+by=c
  return true;//Solution Exists
}
